#include "Point.hpp"

namespace geopackage {

    Point::Point(double xCoord, double yCoord) : x(xCoord), y(yCoord), z(NAN), m(NAN) {}

    Point::Point(double xCoord, double yCoord, double zValue, double mValue) : x(xCoord), y(yCoord), z(zValue), m(mValue) {}

    std::unique_ptr<Geometry> Point::clone() const  {
        return std::make_unique<Point>(x,y);
    }

    double Point::getX() const {
        return x;
    }

    double Point::getY() const {
        return y;
    }

    double Point::getZ() const {
        return z;
    }

    double Point::getM() const {
        return m;
    }

    GeometryType Point::getType() const {
        return GeometryType::POINT;
    }

    Dimension Point::getDimension() const {
        if (!isnan(z) && !isnan(m)) {
            return Dimension::ThreeMeasured;
        } else if (!isnan(z)) {
            return Dimension::Three;
        } else if (!isnan(m)) {
            return Dimension::TwoMeasured;
        } else {
            return Dimension::Two;
        }
    }

    bool Point::isEmpty() const {
        return isnan(x) && isnan(y);
    }

    std::string Point::wkt() const {
        std::stringstream str;
        if (isnan(x) && isnan(y)) {
            str << "POINT EMPTY";
        } else {
            str << "POINT ";
            if (!isnan(z) && !isnan(m)) {
                str << "ZM ";    
            } else if (!isnan(z)) {
                str << "Z ";    
            } else if (!isnan(m)) {
                str << "M ";    
            }
            str << "(";
            str << x << " ";
            str << y;
            if (!isnan(z)) {
                str << " " << z;
            }
            if (!isnan(m)) {
                str << " " << m;
            }
            str << ")";
            
        }
        return str.str();
    }

    Point Point::xy(double x, double y) {
        return Point{x,y};
    }

    Point Point::xym(double x, double y, double m) {
        return Point{x,y,NAN,m};
    }

    Point Point::xyz(double x, double y, double z)  {
        return Point{x,y,z, NAN};
    }

    Point Point::xyzm(double x, double y, double z, double m) {
        return Point{x,y,z,m};
    }

    Point Point::empty() {
        return Point{NAN, NAN};
    }

}