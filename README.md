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

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
% geopackage-cli create -f data.gpkg
```

**Spatial Reference Commands**

List spatial references.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
% geopackage-cli spatialref-list -f data.gpkg
```

Get spatial references by SRS ID

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -s   | SRS ID                   | Yes      |

```bash
% geopackage-cli spatialref-get -f data.gpkg -s 4326
```

Create a new spatial reference

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | SRS Name                 | Yes      |
| -s   | SRS ID                   | Yes      |
| -o   | Organization Name        | Yes      |
| -i   | Organization ID          | Yes      |
| -c   | Description              | Yes      |
| -d   | Definition               | Yes      |

```bash
geopackage-cli spatialref-create -f data.gpkg -n "EPSG:2927" -s 2927 -o EPSG -i 2927 -c "Washington State Plane South" -d 'PROJCS["NAD83(HARN) / Washington South (ftUS)",GEOGCS["NAD83(HARN)",DATUM["NAD83_High_Accuracy_Reference_Network",SPHEROID["GRS 1980",6378137,298.257222101],TOWGS84[-0.991,1.9072,0.5129,-1.25033E-07,-4.6785E-08,-5.6529E-08,0]],PRIMEM["Greenwich",0,AUTHORITY["EPSG","8901"]],UNIT["degree",0.0174532925199433,AUTHORITY["EPSG","9122"]],AUTHORITY["EPSG","4152"]],PROJECTION["Lambert_Conformal_Conic_2SP"],PARAMETER["latitude_of_origin",45.3333333333333],PARAMETER["central_meridian",-120.5],PARAMETER["standard_parallel_1",47.3333333333333],PARAMETER["standard_parallel_2",45.8333333333333],PARAMETER["false_easting",1640416.667],PARAMETER["false_northing",0],UNIT["US survey foot",0.304800609601219],AXIS["Easting",EAST],AXIS["Northing",NORTH],AUTHORITY["EPSG","2927"]]'
```

Delete spatial references by SRS ID

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -s   | SRS ID                   | Yes      |

```bash
% geopackage-cli spatialref-delete -f data.gpkg -s 4326
```

**Content Commands**

List contents

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
% geopackage-cli content-list -f data.gpkg
```

```
Name: states
Data Type: features
Identifier: states
Description: states
Bounds: BOUNDS (0, 0, 0, 0)
SRS ID: 4326

Name: world
Data Type: tiles
Identifier: world
Description: world
Bounds: BOUNDS (-179.99, -89.99, 179.99, 89.99)
SRS ID: 4326
```

Get contents

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
% geopackage-cli content-get -f data.gpkg -n states
```

```
Name: states
Data Type: features
Identifier: states
Description: states
Bounds: BOUNDS (0, 0, 0, 0)
SRS ID: 4326
```

Delete contents

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
% geopackage-cli content-delete -f data.gpkg -n states
```

Create contents

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |
| -t   | Type (Features or Tiles) | Yes      |
| -d   | Identifier               | Yes      |
| -b   | Bounds                   | Yes      |
| -s   | SRS ID                   | Yes      |

```bash
% geopackage-cli content-create -f data.gpkg -n cities -i cities -t features -d Cities -b "-180,-90,180,90" -s 4326
```

**Geometry Columns Commands**

List Geometry Columns

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
% geopackage-cli geometrycolumn-list -f data.gpkg
```

```
Name: rivers
Column: the_geom
Geometry Type: MultiLineString
SRS ID: 4326
Has Z: false
Has M: false

Name: states
Column: the_geom
Geometry Type: MultiPolygon
SRS ID: 4326
Has Z: false
Has M: false
```

Get a Geometry Column

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
% geopackage-cli geometrycolumn-get -f data.gpkg -n cities
```

```
Name: cities
Column: geom
Geometry Type: Point
SRS ID: 4326
Has Z: false
Has M: false
```

Delete a Geometry Column

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
% geopackage-cli geometrycolumn-delete -f data.gpkg -n cities
```

Create a Geometry Column

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Table Name               | Yes      |
| -c   | Column Name              | Yes      |
| -g   | Geometry Type            | Yes      |
| -s   | SRS ID                   | Yes      |
| -z   | Has Z                    | Yes      |
| -m   | Has M                    | Yes      |

```bash
@ geopackage-cli geometrycolumn-create -f data.gpkg -n cities -c geometry -g Point -s 4326 -z false -m false
```

**Extension**

List Extensions

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
@ geopackage-cli extension-list -f data.gpkg
```

```
Name: line_index
Column Name: index
Extension Name: Line Index
Definition: R-TREE
Scope: read-write

Name: point_index
Column Name: index
Extension Name: Point Index
Definition: R-TREE
Scope: read-write
```

Get an Extension

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
@ geopackage-cli extension-get -f data.gpkg -n "Line Index"
```

```
Name: line_index
Column Name: index
Extension Name: Line Index
Definition: R-TREE
Scope: read-write
```

Delete an Extension

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Name                     | Yes      |

```bash
@ geopackage-cli extension-delete -f data.gpkg -n "Line Index"
```

Create an Extension

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   | Table Name                     | Yes      |
| -e   | Extension Name                 | Yes      |
| -c   | Column Name                    | Yes      |
| -d   | Definition                     | Yes      |
| -s   | Scope (read-write, write-only) | Yes      |

```bash
@ geopackage-cli extension-create -f data.gpkg -e "Line Index" -n "index" -c "r_tree" -d "Spatial Index" -s "read-write"
```

**Tile Matrix Set**

List Tile Matrix Sets

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |

```bash
@ geopackage-cli tilematrixset-list -f data.gpkg
```

```
Name: world
SRS ID: 4326
Bounds: BOUNDS (-179.99, -89.99, 179.99, 89.99)

Name: world_mercator
SRS ID: 3857
Bounds: BOUNDS (-2.00364e+07, -2.00375e+07, 2.00364e+07, 2.00375e+07)
```

Get a Tile Matrix Set

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |

```bash
@ geopackage-cli tilematrixset-get -f data.gpkg -n world
```

```
Name: world
SRS ID: 4326
Bounds: BOUNDS (-179.99, -89.99, 179.99, 89.99)
```

Create a Tile Matrix Set

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |
| -s   |  SRS ID                        | Yes      |
| -b   |  Bounds                        | Yes      |

```bash
@ geopackage-cli tilematrixset-create -f data.gpkg -n world -s 4326 -b -180,-90,180,90 
```

Delete a Tile Matrix Set

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |

```bash
@ geopackage-cli tilematrixset-delete -f data.gpkg -n world
```

**Tile Matrix**

List Tile Matrix entries

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |

```bash
@ geopackage-cli tilematrix-list -f data.gpkg
```

```
Table Name: world
Zoom Level: 0
Matrix Size: SIZE (2, 1)
Tile Size: SIZE (256, 256)
Pixel Size: SIZE (0.703125, 0.703125)

Table Name: world
Zoom Level: 1
Matrix Size: SIZE (4, 2)
Tile Size: SIZE (256, 256)
Pixel Size: SIZE (0.351562, 0.351562)

Table Name: world
Zoom Level: 2
Matrix Size: SIZE (8, 4)
Tile Size: SIZE (256, 256)
Pixel Size: SIZE (0.175781, 0.175781)
```

Get Tile Matrix

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |
| -z   |  Zoom Level                    | Yes      |

```bash
@ geopackage-cli tilematrix-get -f data.gpkg -n world -z 2
```

```
Table Name: world
Zoom Level: 2
Matrix Size: SIZE (8, 4)
Tile Size: SIZE (256, 256)
Pixel Size: SIZE (0.175781, 0.175781)
```

Create a Tile Matrix

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |
| -z   |  Zoom Level                    | Yes      |
| -m   |  Matrix Size                   | Yes      |
| -t   |  Tile Size                     | Yes      |
| -p   |  Pixel Size                    | Yes      |

```bash
@ geopackage-cli tilematrix-create -f data.gpkg -n world -z 2 -m 2,1 -t 256,256 -p 0.703125,0.703125
```

Delete a Tile Matrix

| Flag | Description                    | Required |
| ---- | ------------------------------ | -------- |
| -f   | GeoPackage file name           | Yes      |
| -n   |  Name                          | Yes      |
| -z   |  Zoom Level                    | No       |

By table name and zoom level

```bash
@ geopackage-cli tilematrix-delete -f data.gpkg -n basemap -z 1
```

By table name

```bash
@ geopackage-cli tilematrix-delete -f data.gpkg -n basemap
```

**Tile**

Create a Tile table.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |

```bash
@ geopackage-cli tiletable-create -f data.gpkg -n world
```

Create a Geodetic Tile Layer.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -s   | Tile Size (256,512)      | Yes      |
| -z   | Max Zoom Level           | Yes      |

```bash
@ geopackage-cli tile-geodetic-create -f data.gpkg -n world -s 256 -z 12
```

Create a Mercator Tile Layer.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -s   | Tile Size (256,512)      | Yes      |
| -z   | Max Zoom Level           | Yes      |

```bash
@ geopackage-cli tile-mercator-create -f data.gpkg -n world -s 256 -z 19
```

Add or Update a Tile.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -z   | Zoom Level               | Yes      |
| -c   | Column                   | Yes      |
| -r   | Row                      | Yes      |
| -i   | Input file               | Yes      |

```bash
@ geopackage-cli tile-set -f data.gpkg -n world -z 0 -c 0 -r 0 -i 0.jpeg
```

Delete a Tile.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -z   | Zoom Level               | Yes      |
| -c   | Column                   | Yes      |
| -r   | Row                      | Yes      |

```bash
@ geopackage-cli tile-delete -f data.gpkg -n world -z 0 -c 0 -r 0
```

Get a Tile.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -z   | Zoom Level               | Yes      |
| -c   | Column                   | Yes      |
| -r   | Row                      | Yes      |
| -o   | Output file              | Yes      |

```bash
@ geopackage-cli tile-get -f data.gpkg -n world -z 0 -c 0 -r 0 -o 0.jpeg
```

Export Tiles to a Directory

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -d   | Output directory         | Yes      |
| -m   | Image format (jpeg, png) | Yes      |

```bash
@ geopackage-cli tiles-export -f data.gpkg -n world -d world -m jpeg
```

Import Tiles from a Directory

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |
| -d   | Input directory          | Yes      |

```bash
@ geopackage-cli tiles-import -f data.gpkg -n world -d tiles
```

Tile Information

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Tile layer name          | Yes      |

```bash
@ geopackage-cli tile-info -f data.gpkg -n world
```

```
Information
Name: world
Description: world
SRS ID: 4326
Bounds: BOUNDS (-179.99, -89.99, 179.99, 89.99)

Tiles
0 = 2
1 = 8
2 = 32
3 = 128
```

List Tile Layers

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
@ geopackage-cli tile-list -f data.gpkg
```

```
world
tiles
```

**Feature Commands**


Create a Feature layer.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Feature layer name       | Yes      |
| -i   | ID Field Name            | Yes      |
| -c   | Geometry Field Name      | Yes      |
| -g   | Geometry Type            | Yes      |
| -d   | Geometry Dimension       | Yes      |
| -s   | SRS ID                   | Yes      |
| -e   | Field (name and type)    | Yes      |

```bash
% geopackage-cli feature-create -f data.gpkg -n cities -i id -c geom -g point -d 2d -s 4326 -e name string -e population double
```

Create a Feature layer with Random Points.

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -l   | Feature layer name       | Yes      |
| -n   | Number of points         | Yes      |

```bash
% geopackage-cli random-features -f data.gpkg -l points -n 100
```

List all feature layers

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |

```bash
% geopackage-cli feature-list -f data.gpkg
```

```
countries
cities
rivers
```

Count features

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Feature layer name       | Yes      |

```bash
% geopackage-cli feature-count -f data.gpkg -n countries
```

```
10
```

Feature Info

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Feature layer name       | Yes      |

```bash
% geopackage-cli feature-info -f ~/Projects/geoc/src/test/resources/data.gpkg -n rivers
```

```
Information
-----------
Name: rivers
Description: rivers
SRS ID: 4326
Bounds: BOUNDS (0, 0, 0, 0)
# Features: 13

Geometry Column
---------------
Name: the_geom
Type: MultiLineString
Dimension: 2D

Fields
------
Key Field: fid
scalerank Integer
featurecla String
name String
name_alt String
```

Feature Add

| Flag | Description              | Required |
| ---- | ------------------------ | -------- |
| -f   | GeoPackage file name     | Yes      |
| -n   | Feature layer name       | Yes      |
| -g   | Geometry                 | Yes      |
| -v   | Attribute Value          | Yes      |

```bash
% geopackage-cli feature-add -f ~/Projects/geoc/src/test/resources/data.gpkg -n cities -g "POINT(-122.3204, 47.6024)" -v name Seattle -v population 733919
```