#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteGeometryColumnOptions {
    public:
        std::string fileName;
        std::string name;
};

class DeleteGeometryColumnCommand : public Command {

    public:

        DeleteGeometryColumnCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteGeometryColumnOptions options;

};