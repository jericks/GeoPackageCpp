#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <any>
#include "Geometry.hpp"


namespace geopackage {

    class Feature {

        private:

            std::optional<int> id;

            std::unique_ptr<Geometry> geometry;

            std::map<std::string, std::any> attributes;

        public:

            Feature(std::unique_ptr<Geometry> geom, std::map<std::string, std::any> attr);

            Feature(int id, std::unique_ptr<Geometry> geom, std::map<std::string, std::any> attr);

            Feature(Feature const &other);    

            Geometry* getGeometry() const;

            std::optional<int> getId() const;

            std::map<std::string, std::any> getAttributes() const;

            Feature& setAttribute(std::string name, std::any value); 

            Feature& setGeometry(std::unique_ptr<Geometry> geometry); 

    };

    std::ostream& operator << (std::ostream& os, const Feature& feature);

}