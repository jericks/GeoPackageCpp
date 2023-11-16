#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class ExportLayerStyleOptions {
    public:
        std::string fileName;
        int id;
        std::string styleFileName;
};

class ExportLayerStyleCommand : public Command {

    public:

        ExportLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ExportLayerStyleOptions options;

        bool hasEnding (std::string const &fullString, std::string const &ending);

};