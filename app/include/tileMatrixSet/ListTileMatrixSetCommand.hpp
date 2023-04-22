#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class ListTileMatrixSetOptions {
    public:
        std::string fileName;
};

class ListTileMatrixSetCommand : public Command {

    public:

        ListTileMatrixSetCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListTileMatrixSetOptions options;

};