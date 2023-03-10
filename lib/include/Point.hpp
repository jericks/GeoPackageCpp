#pragma once

#include <sstream>
#include <math.h>
#include "Geometry.hpp"

namespace geopackage {

    class Point : public Geometry {
        
        private:

            double x;
            double y;
            double m;
            double z;

        public:

            Point(double xCoord, double yCoord);

            Point(double xCoord, double yCoord, double z, double m);

            double getX() const;

            double getY() const;

            double getZ() const;

            double getM() const;

            virtual Dimension getDimension() const override;

            virtual GeometryType getType() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            virtual bool isEmpty() const override;
            
            static Point xy(double x, double y);
            static Point xym(double x, double y, double m);
            static Point xyz(double x, double y, double z);
            static Point xyzm(double x, double y, double z, double m);
            static Point empty();

    };

}