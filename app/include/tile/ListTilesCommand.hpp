#pragma once

#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "GeoPackage.hpp"


class ListTilesOptions {
    public:
        std::string fileName;
};

class ListTilesCommand : public Command {

    public:

        ListTilesCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        ListTilesOptions options;

};