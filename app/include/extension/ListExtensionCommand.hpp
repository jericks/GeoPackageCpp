#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class ListExtensionOptions {
    public:
        std::string fileName;
};

class ListExtensionCommand : public Command {

    public:

        ListExtensionCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListExtensionOptions options;

};