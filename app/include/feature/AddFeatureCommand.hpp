#pragma once

#include <map>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "WKTReader.hpp"
#include "GeoPackage.hpp"

class AddFeatureOptions {
    public:
        std::string fileName;
        std::string layerName;
        std::string geometry;
        std::vector<std::pair<std::string, std::string>> values;
};

class AddFeatureCommand : public Command {

    public:

        AddFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        AddFeatureOptions options;

};