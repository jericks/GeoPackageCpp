#include "feature/ListFeatureCommand.hpp"

ListFeatureCommand::ListFeatureCommand(CLI::App* app): Command ("features") {
    CLI::App* cmd = app->add_subcommand("features", "List Feature from Layer");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, " Name")->required();
}

void ListFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};

    const char quoteChar = '"';
    const char separatorChar = ',';
    const char newLineChar = '\n';

    geopackage::Schema schema = gpkg.getSchema(options.tableName);
    ostream << quoteChar;
    ostream << schema.getGeometryField().getName();
    ostream << quoteChar;
    ostream << separatorChar;
    ostream << quoteChar;
    ostream << schema.getKey();
    ostream << quoteChar;
    for (auto &fld : schema.getFields()) {
        ostream << separatorChar;
        ostream << quoteChar;
        ostream << fld.getName();
        ostream << quoteChar;
    }
    ostream << newLineChar;

    gpkg.features(options.tableName, [&](geopackage::Feature& f) {
        // Geometry
        ostream << quoteChar;
        ostream << f.getGeometry()->wkt();
        ostream << quoteChar;
        // ID
        ostream << separatorChar;
        ostream << quoteChar;
        ostream << f.getId().value();
        ostream << quoteChar;
        // Attributes
        auto attributes = f.getAttributes();
        for(const auto &attribute : attributes) {
            std::string name = attribute.first;
            std::any value = attribute.second;
            ostream << separatorChar;
            ostream << quoteChar;
            if (value.type() == typeid(std::string)) {
                std::string stringValue = std::any_cast<std::string>(value);
                ostream << stringValue;
            } else if (value.type() == typeid(const char*)) {
                std::string stringValue { std::any_cast<const char*>(value) };
                ostream << stringValue;
            } else if (value.type() == typeid(double)) {
                double doubleValue = std::any_cast<double>(value);
                ostream << doubleValue;
            } else if (value.type() == typeid(int)) {
                int intValue = std::any_cast<int>(value);
                ostream << intValue;
            } else if (value.type() == typeid(bool)) {
                bool boolValue = std::any_cast<bool>(value);
                ostream << boolValue;
            } 
            ostream << quoteChar;
        }
        ostream << newLineChar;
    });    
    
}