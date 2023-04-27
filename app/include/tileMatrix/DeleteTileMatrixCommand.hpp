#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteTileMatrixOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoomLevel;
};

class DeleteTileMatrixCommand : public Command {

    public:

        DeleteTileMatrixCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteTileMatrixOptions options;

};