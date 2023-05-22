#include "feature/RandomFeaturesCommand.hpp"

RandomFeaturesCommand::RandomFeaturesCommand(CLI::App* app): Command ("random-features") {
    CLI::App* cmd = app->add_subcommand("random-features", "Create random features");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-l", options.layerName, "Layer")->required();
    cmd->add_option("-n", options.numberOfFeatures, "Number of Features")->required();
}

void RandomFeaturesCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addContent(geopackage::Content{
        options.layerName, 
        geopackage::DataType::FEATURES, 
        options.layerName, 
        options.layerName, 
        "2022-01-29T18:38:34.649Z", 
        geopackage::Bounds{-180,-90,180,90}, 4326
    });
    gpkg.addGeometryColumn(geopackage::GeometryColumn{
        options.layerName, 
        "geometry", 
        geopackage::GeometryType::POINT, 
        4326, 
        geopackage::Dimension::Two
    });
    geopackage::Schema schema{
        options.layerName,
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String}
        }
    };
    gpkg.createFeatureTable(schema);

    geopackage::Bounds bounds = geopackage::Bounds {-180,-90,180,90};
    double width = abs(bounds.getMinX()) + abs(bounds.getMaxX());
    double height = abs(bounds.getMinY()) + abs(bounds.getMaxY());

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(0, 1);

    for (int i = 0; i < options.numberOfFeatures; i++) {
        std::unique_ptr<geopackage::Geometry> pt = std::make_unique<geopackage::Point>(
            bounds.getMinX() + (distr(eng) * width),
            bounds.getMinY() + (distr(eng) * height)
        );
        std::map<std::string, std::any> props {{"name", i}};
        const geopackage::Feature feature = {std::move(pt), props};
        gpkg.addFeature(options.layerName, feature);
    }
}