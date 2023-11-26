#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateIndexOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class CreateIndexCommand : public Command {

    public:

        CreateIndexCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateIndexOptions options;

};