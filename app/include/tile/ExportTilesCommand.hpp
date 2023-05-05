#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class ExportTilesOptions {
    public:
        std::string fileName;
        std::string tableName;
        std::string directory;
        std::string format;
};

class ExportTilesCommand : public Command {

    public:

        ExportTilesCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ExportTilesOptions options;

};