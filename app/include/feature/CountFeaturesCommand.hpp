#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class CountFeaturesOptions {
    public:
        std::string fileName;
        std::string layerName;
};

class CountFeaturesCommand : public Command {

    public:

        CountFeaturesCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CountFeaturesOptions options;

};