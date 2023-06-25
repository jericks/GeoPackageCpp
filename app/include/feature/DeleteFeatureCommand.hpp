#pragma once

#include <map>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"

class DeleteFeatureOptions {
    public:
        std::string fileName;
        std::string layerName;
        int id;
};

class DeleteFeatureCommand : public Command {

    public:

        DeleteFeatureCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteFeatureOptions options;

};