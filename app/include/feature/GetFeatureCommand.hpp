#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetFeatureOptions {
    public:
        std::string fileName;
        std::string tableName;
        int id;
};

class GetFeatureCommand : public Command {

    public:

        GetFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetFeatureOptions options;

};