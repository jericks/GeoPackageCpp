#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class CreateFeatureLayerOptions {
    public:
        std::string fileName;
        std::string layerName;
        std::string idName;
        std::string geometryName;
        std::string geometryType;
        int srsId;
        std::string dimension;
        std::vector<std::pair<std::string, std::string>> fields;
};

class CreateFeatureLayerCommand : public Command {

    public:

        CreateFeatureLayerCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateFeatureLayerOptions options;

};