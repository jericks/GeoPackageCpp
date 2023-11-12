#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteLayerStyleOptions {
    public:
        std::string fileName;
        int id;
};

class DeleteLayerStyleCommand : public Command {

    public:

        DeleteLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteLayerStyleOptions options;

};