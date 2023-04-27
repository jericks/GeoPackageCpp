#include "Size.hpp"


namespace geopackage {

    namespace size {

        Size<double> fromDoubleString(std::string str) {
            std::vector<double> numbers;
            std::stringstream numberStream(str);
            while(numberStream.good()) {
                std::string numberStr;
                getline(numberStream, numberStr, ','); 
                numbers.push_back(std::atof(numberStr.c_str()));
            }
            return Size<double>{numbers[0], numbers[1]};
        }

        Size<int> fromIntString(std::string str) {
            std::vector<int> numbers;
            std::stringstream numberStream(str);
            while(numberStream.good()) {
                std::string numberStr;
                getline(numberStream, numberStr, ','); 
                numbers.push_back(std::atoi(numberStr.c_str()));
            }
            return Size<int>{numbers[0], numbers[1]};
        }

    }

}