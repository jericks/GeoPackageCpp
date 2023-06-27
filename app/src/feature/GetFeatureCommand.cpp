#include "feature/GetFeatureCommand.hpp"

GetFeatureCommand::GetFeatureCommand(CLI::App* app): Command ("feature-get") {
    CLI::App* cmd = app->add_subcommand("feature-get", "Get Feature from Layer");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, " Name")->required();
    cmd->add_option("-i", options.id, " Feature ID")->required();
}

void GetFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto feature = gpkg.getFeature(options.tableName, options.id);
    if (feature) {
        ostream << "Geometry: " << feature->getGeometry()->wkt() << "\n";
        auto attributes = feature->getAttributes();
        for(const auto &attribute : attributes) {
            std::string name = attribute.first;
            std::any value = attribute.second;
            ostream << name << ": ";
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
            ostream << "\n";
        }
    }
    
}