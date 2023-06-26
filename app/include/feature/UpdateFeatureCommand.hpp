#pragma once

#include <map>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "WKTReader.hpp"
#include "GeoPackage.hpp"

class UpdateFeatureOptions {
    public:
        std::string fileName;
        std::string layerName;
        int id;
        std::string geometry;
        std::vector<std::pair<std::string, std::string>> values;
};

class UpdateFeatureCommand : public Command {

    public:

        UpdateFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        UpdateFeatureOptions options;

};