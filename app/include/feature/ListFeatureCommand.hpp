#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class ListFeatureOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class ListFeatureCommand : public Command {

    public:

        ListFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListFeatureOptions options;
        
};