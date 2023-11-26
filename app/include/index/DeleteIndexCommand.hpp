#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class DeleteIndexOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class DeleteIndexCommand : public Command {

    public:

        DeleteIndexCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteIndexOptions options;

};