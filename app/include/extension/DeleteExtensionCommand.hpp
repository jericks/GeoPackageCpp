#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteExtensionOptions {
    public:
        std::string fileName;
        std::string name;
};

class DeleteExtensionCommand : public Command {

    public:

        DeleteExtensionCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteExtensionOptions options;

};