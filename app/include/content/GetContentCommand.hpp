#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class GetContentOptions {
    public:
        std::string fileName;
        std::string name;
};

class GetContentCommand : public Command {

    public:

        GetContentCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetContentOptions options;

};