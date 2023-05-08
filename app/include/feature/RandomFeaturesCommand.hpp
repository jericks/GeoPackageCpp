#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class RandomFeaturesOptions {
    public:
        std::string fileName;
        std::string layerName;
        int numberOfFeatures;
};

class RandomFeaturesCommand : public Command {

    public:

        RandomFeaturesCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        RandomFeaturesOptions options;

};