#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateTileTableOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class CreateTileTableCommand : public Command {

    public:

        CreateTileTableCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateTileTableOptions options;

};