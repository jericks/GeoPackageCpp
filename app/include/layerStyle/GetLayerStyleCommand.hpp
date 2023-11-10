#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class GetLayerStyleOptions {
    public:
        std::string fileName;
        int id;
};

class GetLayerStyleCommand : public Command {

    public:

        GetLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetLayerStyleOptions options;

};