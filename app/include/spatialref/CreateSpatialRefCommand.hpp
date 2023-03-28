#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateSpatialRefOptions {
    public:
        std::string fileName;
        std::string srsName;
        int srsId;
        std::string organization;
        int organizationCoordSysId;
        std::string definition;
        std::string description;
};

class CreateSpatialRefCommand : public Command {

    public:

        CreateSpatialRefCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateSpatialRefOptions options;

};