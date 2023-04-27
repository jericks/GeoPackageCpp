#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateTileMatrixOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoomLevel;
        std::string matrixSize;
        std::string tileSize;
        std::string pixelSize;
};

class CreateTileMatrixCommand : public Command {

    public:

        CreateTileMatrixCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateTileMatrixOptions options;

};