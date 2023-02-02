#pragma once

#include <iostream>

namespace geopackage {

    class SpatialRef {

        private:

            std::string srsName;
            int srsId;
            std::string organization;
            int organizationCoordSysId;
            std::string definition;
            std::string description;
                
        public:

            SpatialRef(std::string srsName, int srsId, std::string organization, int organizationCoordSysId, std::string definition, std::string description);

            std::string getSrsName() const;

            int getSrsId() const;

            std::string getOrganization() const;

            int getOrganizationCoordSysId() const;

            std::string getDefinition() const;

            std::string getDescription() const;

            static SpatialRef create4326();

            static SpatialRef create3857();
            

    };

    std::ostream& operator << (std::ostream& os, const SpatialRef& spatialRef);

}