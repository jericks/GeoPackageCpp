#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class InfoTileOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class InfoTileCommand : public Command {

    public:

        InfoTileCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        InfoTileOptions options;

};