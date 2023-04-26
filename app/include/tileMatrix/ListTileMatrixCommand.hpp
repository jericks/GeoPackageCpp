#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class ListTileMatrixOptions {
    public:
        std::string fileName;
        std::string tableName;
};

class ListTileMatrixCommand : public Command {

    public:

        ListTileMatrixCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListTileMatrixOptions options;

};