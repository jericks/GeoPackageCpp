#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteSpatialRefOptions {
    public:
        std::string fileName;
        int srsId;
};

class DeleteSpatialRefCommand : public Command {

    public:

        DeleteSpatialRefCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteSpatialRefOptions options;

};