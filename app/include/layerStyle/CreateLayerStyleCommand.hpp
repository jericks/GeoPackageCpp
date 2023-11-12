#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateLayerStyleOptions {
    public:
        std::string fileName;
        std::string tableCatalog;
        std::string tableSchema;
        std::string tableName;
        std::string geometryColumn;
        std::string styleName;
        std::string styleQML;
        std::string styleSLD;
        bool useAsDefault;
        std::string description;
        std::string owner;
        std::string ui;
};

class CreateLayerStyleCommand : public Command {

    public:

        CreateLayerStyleCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateLayerStyleOptions options;

};