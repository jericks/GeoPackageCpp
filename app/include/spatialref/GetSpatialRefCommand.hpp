#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetSpatialRefOptions {
    public:
        std::string fileName;
        int srsId;
        bool all = false;
};

class GetSpatialRefCommand : public Command {

    public:

        GetSpatialRefCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetSpatialRefOptions options;

};