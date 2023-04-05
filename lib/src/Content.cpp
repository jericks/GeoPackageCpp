#include "Content.hpp"

namespace geopackage {

    Content::Content(std::string tableName, DataType dataType, std::string identifier, std::string description, std::string lastChange, Bounds bounds, int srsId) :
        tableName(tableName), dataType(dataType), identifier(identifier), description(description), lastChange(lastChange), bounds(bounds), srsId(srsId) {}

    Content::Content(std::string tableName, DataType dataType, std::string identifier, std::string description, Bounds bounds, int srsId) :
        tableName(tableName), dataType(dataType), identifier(identifier), description(description), lastChange(now()), bounds(bounds), srsId(srsId) {}    

    std::string Content::getTableName() const {
        return tableName;
    }

    DataType Content::getDataType() const {
        return dataType;
    }

    std::string Content::getIdentifier() const {
        return identifier;
    }

    std::string Content::getDescription() const {
        return description;
    }

    std::string Content::getLastChange() const {
        return lastChange;
    }

    Bounds Content::getBounds() const {
        return bounds;
    }

    int Content::getSrsId() const {
        return srsId;
    }

    std::ostream& operator << (std::ostream& os, const Content& e) {
        os << "CONTENT (tableName = " << e.getTableName() << ", dataType = " << datatype::toString(e.getDataType())
            << ", identifier = " << e.getIdentifier()  
            << ", description = " << e.getDescription()  
            << ", lastChange = " << e.getLastChange()  
            << ", bounds = " << e.getBounds()  
            << ", srsId = " << e.getSrsId()  
            << ")";
        return os;
    }

    std::string Content::now() {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        auto timer = system_clock::to_time_t(now);
        std::tm bt = *std::gmtime(&timer);
        std::ostringstream oss;
        oss << std::put_time(&bt, "%Y-%m-%dT%H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count() << "Z";
        return oss.str();
    }

}