GeoPackageCpp
=============

A C++ [GeoPackage](https://www.geopackage.org/spec131/index.html) API.

GeoPackageCpp is written in C++ using [SQLiteCPP](https://github.com/SRombauts/SQLiteCpp) and [CLI11](https://github.com/CLIUtils/CLI11).  The [Google Test](https://github.com/google/googletest) library is used to write unit tests.  The project is built
with [CMake](https://cmake.org/) and dependencies are managed with [conan](https://conan.io/).

Build
-----

```bash
mkdir build
cd build
conan install ..
cmake -g "Unix Makefiles" .
cmake --build .
ctest --verbose
```

Command line interface
----------------------

List all commands.

```bash
% geopackage-cli list
list
create
```

Get help for a command

```bash
 % geopackage-cli create --help
Create a blank GeoPackage
Usage: app/geopackage-cli create [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f TEXT REQUIRED            File
```

Create an new GeoPackage file.

```bash
% geopackage-cli create -f data.gpkg
```

