#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class ListFeatureLayersOptions {
    public:
        std::string fileName;
};

class ListFeatureLayersCommand : public Command {

    public:

        ListFeatureLayersCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListFeatureLayersOptions options;

};