#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateTileMatrixSetOptions {
    public:
        std::string fileName;
        std::string tableName;
        int srsId;
        std::string bounds;
};

class CreateTileMatrixSetCommand : public Command {

    public:

        CreateTileMatrixSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateTileMatrixSetOptions options;

};