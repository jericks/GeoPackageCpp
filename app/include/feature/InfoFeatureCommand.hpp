#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class InfoFeatureOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class InfoFeatureCommand : public Command {

    public:

        InfoFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        InfoFeatureOptions options;

};