#pragma once

#include <map>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"

class DeleteAllFeatureOptions {
    public:
        std::string fileName;
        std::string layerName;
};

class DeleteAllFeatureCommand : public Command {

    public:

        DeleteAllFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteAllFeatureOptions options;

};