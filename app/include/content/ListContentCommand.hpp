#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"

class ListContentOptions {
    public:
        std::string fileName;
};

class ListContentCommand : public Command {

    public:

        ListContentCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListContentOptions options;

};