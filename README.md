GeoPackageCpp
=============

A C++ [GeoPackage](https://www.geopackage.org/spec131/index.html) API.

GeoPackageCpp is written in C++ using [SQLiteCPP](https://github.com/SRombauts/SQLiteCpp) and [CLI11](https://github.com/CLIUtils/CLI11).  The [Google Test](https://github.com/google/googletest) library is used to write unit tests.  The project is built
with [CMake](https://cmake.org/) and dependencies are managed with [conan](https://conan.io/).

```cpp
const std::string fileName = "data.gpkg";
geopackage::GeoPackage geopackage { fileName };

std::string name = "basemap";
geopackage.createTileTable(name);
geopackage.addTile(name, geopackage::Tile(0,0,0,"data/tms/0/0/0.jpeg"));
geopackage.addTile(name, geopackage::Tile(1,0,0,"data/tms/1/0/0.jpeg"));
geopackage.addTile(name, geopackage::Tile(1,0,1,"data/tms/1/0/1.jpeg"));
geopackage.addTile(name, geopackage::Tile(1,1,0,"data/tms/1/1/0.jpeg"));
geopackage.addTile(name, geopackage::Tile(1,1,1,"data/tms/1/1/1.jpeg"));

geopackage.tiles(name, 1, [&](geopackage::Tile& t) {
    std::cout << t << "\n";
});
```

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

