#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace geopackage {

    template<class T>
    class Size {

        private: 

            T width;

            T height;

        public: 

            Size(T w, T h) : width(w), height(h) {}

            T getWidth() const {
                return width;
            }

            T getHeight() const {
                return height;
            }

            

    };

    namespace size {


        Size<double> fromDoubleString(std::string str);

        Size<int> fromIntString(std::string str);
    }

    template<class T>
    std::ostream& operator << (std::ostream& os, const Size<T>& s) {
        os << "SIZE (" << s.getWidth() << ", " << s.getHeight()  << ")";
        return os;
    }

}