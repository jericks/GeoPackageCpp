#pragma once

#include <iostream>
#include <string>

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

    template<class T>
    std::ostream& operator << (std::ostream& os, const Size<T>& s) {
        os << "SIZE (" << s.getWidth() << ", " << s.getHeight()  << ")";
        return os;
    }

}