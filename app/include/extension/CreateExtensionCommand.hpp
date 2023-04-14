#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateExtensionOptions {
    public:
        std::string fileName;
        std::string tableName;
        std::string columnName;
        std::string extensionName;
        std::string definition;
        std::string scope;
};

class CreateExtensionCommand : public Command {

    public:

        CreateExtensionCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateExtensionOptions options;

};