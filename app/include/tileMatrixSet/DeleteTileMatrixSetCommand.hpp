#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteTileMatrixSetOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class DeleteTileMatrixSetCommand : public Command {

    public:

        DeleteTileMatrixSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteTileMatrixSetOptions options;

};