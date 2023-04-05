#include "WKTReader.hpp"

namespace geopackage {

    std::unique_ptr<Geometry> WKTReader::read(std::string str) {
        peg::parser parser(R"(
Geometry <- Point / LineString / Polygon / MultiPoint / MultiPointAlt / MultiLineString / MultiPolygon / GeometryCollection

Point <- 'POINT' '(' Coordinate ')'

LineString <- 'LINESTRING' '(' Coordinates ')'

Polygon <- 'POLYGON' '(' CoordinateList ')'

MultiPoint <- 'MULTIPOINT' '(' Coordinates ')'

MultiPointAlt <- 'MULTIPOINT' '(' CoordinateList ')'

MultiLineString <- 'MULTILINESTRING' '(' CoordinateList ')'

MultiPolygon <- 'MULTIPOLYGON' '(' PolygonList ')'

GeometryCollection <- 'GEOMETRYCOLLECTION' '(' Geometry (',' Geometry)* ')'

Coordinate <- Number Number

Coordinates <- Coordinate (',' Coordinate)*

CoordinateList <- '(' Coordinates ')' (',' '(' Coordinates ')')*

PolygonList <- '(' CoordinateList ')' (',' '(' CoordinateList ')')

Number <- < '-'? [0-9]+ ('.' [0-9]+)? >

%whitespace <- [ \t]*
)");

        assert(static_cast<bool>(parser) == true);

        std::unique_ptr<Geometry> geometry;
        std::vector<std::unique_ptr<geopackage::Geometry>> geoms;

        parser["Geometry"] = [&](const peg::SemanticValues &values) {
            if (values.choice() == 0) {
                Point point = std::any_cast<Point>(values[0]);
                geometry = std::make_unique<Point>(point);
                geoms.push_back(geometry->clone());
                return std::any{point};
            } else if (values.choice() == 1) {
                LineString lineString = std::any_cast<LineString>(values[0]);
                geometry = std::make_unique<LineString>(lineString);
                geoms.push_back(geometry->clone());
                return std::any{lineString};
            } else if (values.choice() == 2) {
                Polygon polygon = std::any_cast<Polygon>(values[0]);
                geometry = std::make_unique<Polygon>(polygon);
                return std::any{polygon};
            } else if (values.choice() == 3 || values.choice() == 4) {
                MultiPoint multiPoint = std::any_cast<MultiPoint>(values[0]);
                geometry = std::make_unique<MultiPoint>(multiPoint);
                return std::any{multiPoint};
            } else if (values.choice() == 5) {
                MultiLineString multiLineString = std::any_cast<MultiLineString>(values[0]);
                geometry = std::make_unique<MultiLineString>(multiLineString);
                return std::any{multiLineString};
            } else if (values.choice() == 6) {
                MultiPolygon multiPolygon = std::any_cast<MultiPolygon>(values[0]);
                geometry = std::make_unique<MultiPolygon>(multiPolygon);
                return std::any{multiPolygon};
            } else if (values.choice() == 7) {
                return std::any{};
            }
            return std::any{};
        };

        parser["GeometryCollection"] = [&](const peg::SemanticValues &values) {
            std::vector<std::unique_ptr<geopackage::Geometry>> geometries;
            for(int i = 0; i < values.size(); i++) { 
                if (values[i].type() == typeid(Point)) {
                    geometries.push_back(std::make_unique<Point>(std::any_cast<Point>(values[i])));
                } else if (values[i].type() == typeid(LineString)) {
                    geometries.push_back(std::make_unique<LineString>(std::any_cast<LineString>(values[i])));
                } else if (values[i].type() == typeid(Polygon)) {
                    geometries.push_back(std::make_unique<Polygon>(std::any_cast<Polygon>(values[i])));
                } else if (values[i].type() == typeid(MultiPoint)) {
                    geometries.push_back(std::make_unique<MultiPoint>(std::any_cast<MultiPoint>(values[i])));
                } else if (values[i].type() == typeid(MultiLineString)) {
                    geometries.push_back(std::make_unique<MultiLineString>(std::any_cast<MultiLineString>(values[i])));
                } else if (values[i].type() == typeid(MultiPolygon)) {
                    geometries.push_back(std::make_unique<MultiPolygon>(std::any_cast<MultiPolygon>(values[i])));
                } else /*if (values[i].type() == typeid(GeometryCollection))*/ {
                    geometries.push_back(geometry->clone());
                } 
            }
            GeometryCollection geometryCollection {std::move(geometries)};
            geometry = geometryCollection.clone();
            return std::any{};
        };

        parser["Polygon"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<Point>> pointLists = std::any_cast<std::vector<std::vector<Point>>>(values[0]);
            std::vector<LinearRing> rings;
            for(int i = 0; i < pointLists.size(); i++) {
                LinearRing ring {pointLists[i]};
                rings.push_back(ring);
            }
            Polygon polygon {rings};
            return polygon;
        };

        parser["LineString"] = [](const peg::SemanticValues &values) {
            std::vector<Point> points = std::any_cast<std::vector<Point>>(values[0]);
            LineString lineString {points};
            return lineString;
        };

        parser["MultiLineString"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<Point>> pointLists = std::any_cast<std::vector<std::vector<Point>>>(values[0]);
            std::vector<LineString> lines;
            for(int i = 0; i < pointLists.size(); i++) {
                LineString line {pointLists[i]};
                lines.push_back(line);
            }
            MultiLineString multiLineString {lines};
            return multiLineString;
        };

        parser["Point"] = [](const peg::SemanticValues &values) {
            Point point = std::any_cast<Point>(values[0]);
            return point;
        };

        parser["MultiPoint"] = [](const peg::SemanticValues &values) {
            std::vector<Point> points = std::any_cast<std::vector<Point>>(values[0]);
            MultiPoint multiPoint {points};
            return multiPoint;
        };

        parser["MultiPointAlt"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<Point>> pointLists = std::any_cast<std::vector<std::vector<Point>>>(values[0]);
            std::vector<Point> points;
            for(int i = 0; i < pointLists.size(); i++) {
                Point point {pointLists[i][0]};
                points.push_back(point);
            }
            MultiPoint multiPoint {points};
            return multiPoint;
        };

        parser["MultiPolygon"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<std::vector<Point>>> polygonList = std::any_cast<std::vector<std::vector<std::vector<Point>>>>(values[0]);
            std::vector<Polygon> polygons;
            for(int i = 0; i < polygonList.size(); i++) {
                std::vector<std::vector<Point>> ringsList = polygonList[i];
                std::vector<LinearRing> rings;
                for(int j = 0; j < ringsList.size(); j++) { 
                    LinearRing ring {ringsList[j]};
                    rings.push_back(ring);
                }
                Polygon polygon {rings};
                polygons.push_back(polygon);
            }
            MultiPolygon multiPolygon {polygons};
            return multiPolygon;
        };

        parser["PolygonList"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<std::vector<Point>>> polygons;
            for(int i = 0; i < values.size(); i++) {
                std::vector<std::vector<Point>> rings = std::any_cast<std::vector<std::vector<Point>>>(values[i]);
                polygons.push_back(rings);
            }
            return polygons;
        };

        parser["CoordinateList"] = [](const peg::SemanticValues &values) {
            std::vector<std::vector<Point>> pointLists;
            for(int i = 0; i < values.size(); i++) {
                std::vector<Point> points = std::any_cast<std::vector<Point>>(values[i]);
                pointLists.push_back(points);
            }
            return pointLists;
        };

        parser["Coordinates"] = [](const peg::SemanticValues &values) {
            std::vector<Point> points;
            for(int i = 0; i < values.size(); i++) {
                Point point = std::any_cast<Point>(values[i]);
                points.push_back(point);
            }
            return points;
        };

        parser["Coordinate"] = [](const peg::SemanticValues &values) {
            double x = std::any_cast<double>(values[0]);
            double y = std::any_cast<double>(values[1]);
            Point point {x,y};
            return point;
        };

        parser["Number"] = [](const peg::SemanticValues &values) {
            double number = values.token_to_number<double>();
            return number;
        };

        parser.enable_packrat_parsing();
        parser.parse(str);

        return geometry;
    }

}
