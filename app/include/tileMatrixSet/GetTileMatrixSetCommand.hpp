#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetTileMatrixSetOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class GetTileMatrixSetCommand : public Command {

    public:

        GetTileMatrixSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetTileMatrixSetOptions options;

};