#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class DeleteTileOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoom;
        int column;
        int row;
};

class DeleteTileCommand : public Command {

    public:

        DeleteTileCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        DeleteTileOptions options;

};