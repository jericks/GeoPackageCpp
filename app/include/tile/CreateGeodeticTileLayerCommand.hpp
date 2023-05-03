#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateGeodeticTileLayerOptions {
    public:
        std::string fileName;
        std::string tableName;
        int tileSize;
        int maxZoomLevel;
};

class CreateGeodeticTileLayerCommand : public Command {

    public:

        CreateGeodeticTileLayerCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateGeodeticTileLayerOptions options;

};