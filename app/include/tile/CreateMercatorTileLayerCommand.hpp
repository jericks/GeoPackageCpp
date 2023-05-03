#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateMercatorTileLayerOptions {
    public:
        std::string fileName;
        std::string tableName;
        int tileSize;
        int maxZoomLevel;
};

class CreateMercatorTileLayerCommand : public Command {

    public:

        CreateMercatorTileLayerCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateMercatorTileLayerOptions options;

};