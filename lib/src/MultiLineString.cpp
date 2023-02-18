#include "MultiLineString.hpp"

namespace geopackage {

    MultiLineString::MultiLineString(std::vector<LineString> lns) : lines(lns) { }

    std::unique_ptr<Geometry> MultiLineString::clone() const  {
        return std::make_unique<MultiLineString>(lines);
    }

    GeometryType MultiLineString::getType() const {
        return GeometryType::MULTILINESTRING;
    }

    std::string MultiLineString::wkt() const {
        std::stringstream str;
        str << "MULTILINESTRING ";
        if (std::size(lines) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstLine = true;
            for(auto l : lines) {
                if (firstLine != true) {
                    str << ", ";
                }
                firstLine = false;
                bool firstTime = true;
                str << "(";
                for(auto p : l.getPoints()) {
                    if (firstTime != true) {
                        str << ", ";
                    }
                    firstTime = false;
                    str << p.getX() << " " << p.getY();
                }
                str << ")";
            }
            str <<  ")";
        }
        return str.str();
    }

    std::vector<LineString> MultiLineString::getLineStrings() const {
        return lines;
    }

}