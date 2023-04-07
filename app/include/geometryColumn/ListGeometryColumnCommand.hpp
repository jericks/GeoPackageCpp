#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class ListGeometryColumnOptions {
    public:
        std::string fileName;
};

class ListGeometryColumnCommand : public Command {

    public:

        ListGeometryColumnCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListGeometryColumnOptions options;

};