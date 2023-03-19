#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class ListSpatialRefOptions {
    public:
        std::string fileName;
};

class ListSpatialRefCommand : public Command {

    public:

        ListSpatialRefCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListSpatialRefOptions options;

};