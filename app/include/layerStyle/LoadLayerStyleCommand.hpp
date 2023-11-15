#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class LoadLayerStyleOptions {
    public:
        std::string fileName;
        int id;
        std::string styleFileName;
};

class LoadLayerStyleCommand : public Command {

    public:

        LoadLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        LoadLayerStyleOptions options;

        bool hasEnding (std::string const &fullString, std::string const &ending);

};