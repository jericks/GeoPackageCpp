#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetTileMatrixOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoomLevel;
};

class GetTileMatrixCommand : public Command {

    public:

        GetTileMatrixCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetTileMatrixOptions options;

};