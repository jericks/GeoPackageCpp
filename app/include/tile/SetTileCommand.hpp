#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class SetTileOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoom;
        int column;
        int row;
        std::string inputFileName;
};

class SetTileCommand : public Command {

    public:

        SetTileCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        SetTileOptions options;

};