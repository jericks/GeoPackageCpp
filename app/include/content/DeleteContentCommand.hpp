#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteContentOptions {
    public:
        std::string fileName;
        std::string name;
};

class DeleteContentCommand : public Command {

    public:

        DeleteContentCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteContentOptions options;

};