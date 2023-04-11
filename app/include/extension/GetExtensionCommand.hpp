#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetExtensionOptions {
    public:
        std::string fileName;
        std::string name;
};

class GetExtensionCommand : public Command {

    public:

        GetExtensionCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetExtensionOptions options;

};