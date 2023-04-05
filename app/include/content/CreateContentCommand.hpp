#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateContentOptions {
    public:
        std::string fileName;
        std::string tableName;
        std::string dataType;
        std::string identifier;
        std::string description;
        std::string lastChange;
        std::string bounds;
        int srsId;
};

class CreateContentCommand : public Command {

    public:

        CreateContentCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateContentOptions options;

};