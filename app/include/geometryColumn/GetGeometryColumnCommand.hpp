#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetGeometryColumnOptions {
    public:
        std::string fileName;
        std::string name;
};

class GetGeometryColumnCommand : public Command {

    public:

        GetGeometryColumnCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetGeometryColumnOptions options;

};