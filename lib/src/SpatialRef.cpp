#include "SpatialRef.hpp"

namespace geopackage {

    SpatialRef::SpatialRef(std::string srs_name, int srs_id, std::string org, int org_coord_sys_id, std::string def, std::string descr) :
        srsName(srs_name), srsId(srs_id), organization(org), organizationCoordSysId(org_coord_sys_id), definition(def), description(descr) {}

    std::string SpatialRef::getSrsName() const {
        return srsName;
    }

    int SpatialRef::getSrsId() const {
        return srsId;
    }

    std::string SpatialRef::getOrganization() const {
        return organization;
    }

    int SpatialRef::getOrganizationCoordSysId() const {
        return organizationCoordSysId;
    }

    std::string SpatialRef::getDefinition() const {
        return definition;
    }

    std::string SpatialRef::getDescription() const {
        return description;
    }

    std::ostream& operator << (std::ostream& os, const SpatialRef& s) {
        os << "SPATIAL_REF (srsName = " << s.getSrsName() << ", srsId = " << s.getSrsId() << ")";
        return os;
    }

    SpatialRef SpatialRef::create4326() {
        return SpatialRef{
            "WGS84", 4326, "EPSG", 4326, 
            R"(GEOGCS["WGS 84", DATUM["World Geodetic System 1984", SPHEROID["WGS 84", 6378137.0, 298.257223563, 
            AUTHORITY["EPSG","7030"]], AUTHORITY["EPSG","6326"]], PRIMEM["Greenwich", 0.0, AUTHORITY["EPSG","8901"]], UNIT["degree", 0.017453292519943295], 
            AXIS["Geodetic longitude", EAST], AXIS["Geodetic latitude", NORTH], AUTHORITY["EPSG","4326"]])", 
            "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"
        };
    }

    SpatialRef SpatialRef::create3857() {
        return SpatialRef{
           "epsg:3857", 3857, "EPSG", 3857, 
           R"(PROJCS["WGS 84 / Pseudo-Mercator", GEOGCS["WGS 84", 
                DATUM["World Geodetic System 1984", 
                SPHEROID["WGS 84", 6378137.0, 298.257223563, AUTHORITY["EPSG","7030"]], 
                AUTHORITY["EPSG","6326"]], 
                PRIMEM["Greenwich", 0.0, AUTHORITY["EPSG","8901"]], 
                UNIT["degree", 0.017453292519943295], 
                AXIS["Geodetic longitude", EAST], 
                AXIS["Geodetic latitude", NORTH], 
                AUTHORITY["EPSG","4326"]], 
            PROJECTION["Popular Visualisation Pseudo Mercator", AUTHORITY["EPSG","1024"]], 
            PARAMETER["semi_minor", 6378137.0], 
            PARAMETER["latitude_of_origin", 0.0], 
            PARAMETER["central_meridian", 0.0], 
            PARAMETER["scale_factor", 1.0], 
            PARAMETER["false_easting", 0.0], 
            PARAMETER["false_northing", 0.0], 
            UNIT["m", 1.0], 
            AXIS["Easting", EAST], 
            AXIS["Northing", NORTH], 
            AUTHORITY["EPSG","3857"]])", 
            "Web Mercator"
        };
    }

    
}