#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class ImportTilesOptions {
    public:
        std::string fileName;
        std::string tableName;
        std::string directory;
};

class ImportTilesCommand : public Command {

    public:

        ImportTilesCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ImportTilesOptions options;

};