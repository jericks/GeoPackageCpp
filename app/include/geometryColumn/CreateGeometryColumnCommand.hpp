#pragma once

#include <random>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GeoPackage.hpp"


class CreateGeometryColumnOptions {
    public:
        std::string fileName;
        std::string tableName;
        std::string columnName;
        std::string geometryType;
        int srsId;
        bool z;
        bool m;
};

class CreateGeometryColumnCommand : public Command {

    public:

        CreateGeometryColumnCommand(CLI::App* app);

        void execute(std::istream& istream, std::ostream& ostream);

    private:

        CreateGeometryColumnOptions options;

};