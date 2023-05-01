#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class GetTileOptions {
    public:
        std::string fileName;
        std::string tableName;
        int zoom;
        int column;
        int row;
        std::string outputFileName;
};

class GetTileCommand : public Command {

    public:

        GetTileCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        GetTileOptions options;

};