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

Create a Feature layer with Random Points.

```bash
% geopackage-cli random-features -f data.gpkg -l points -n 100
```

List spatial references.

```bash
% geopackage-cli spatialref-list -f data.gpkg
```

Get spatial references by SRS ID

```bash
% geopackage-cli spatialref-get -f data.gpkg -s 4326
```

Create a new spatial reference

```bash
geopackage-cli spatialref-create -f data.gpkg -n "EPSG:2927" -s 2927 -o EPSG -i 2927 -c "Washington State Plane South" -d 'PROJCS["NAD83(HARN) / Washington South (ftUS)",GEOGCS["NAD83(HARN)",DATUM["NAD83_High_Accuracy_Reference_Network",SPHEROID["GRS 1980",6378137,298.257222101],TOWGS84[-0.991,1.9072,0.5129,-1.25033E-07,-4.6785E-08,-5.6529E-08,0]],PRIMEM["Greenwich",0,AUTHORITY["EPSG","8901"]],UNIT["degree",0.0174532925199433,AUTHORITY["EPSG","9122"]],AUTHORITY["EPSG","4152"]],PROJECTION["Lambert_Conformal_Conic_2SP"],PARAMETER["latitude_of_origin",45.3333333333333],PARAMETER["central_meridian",-120.5],PARAMETER["standard_parallel_1",47.3333333333333],PARAMETER["standard_parallel_2",45.8333333333333],PARAMETER["false_easting",1640416.667],PARAMETER["false_northing",0],UNIT["US survey foot",0.304800609601219],AXIS["Easting",EAST],AXIS["Northing",NORTH],AUTHORITY["EPSG","2927"]]'
```

Delete spatial references by SRS ID

```bash
% geopackage-cli spatialref-delete -f data.gpkg -s 4326
```