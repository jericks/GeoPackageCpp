#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class ListLayerStyleOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class ListLayerStyleCommand : public Command {

    public:

        ListLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListLayerStyleOptions options;

};