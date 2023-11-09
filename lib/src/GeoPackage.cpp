#include "GeoPackage.hpp"

namespace geopackage {

    GeoPackage::GeoPackage(std::string fileName) : fileName(fileName) ,  db(SQLite::Database(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)) {
        createTables();
    }

    GeoPackage::~GeoPackage() {
    }

    void  GeoPackage::createTables() {
        try {
            SQLite::Transaction transaction(db);
            db.exec("PRAGMA application_id=1196444487;");
            db.exec("PRAGMA user_version=10300");
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_spatial_ref_sys (
                srs_name TEXT NOT NULL,
                srs_id INTEGER PRIMARY KEY,
                organization TEXT NOT NULL,
                organization_coordsys_id INTEGER NOT NULL,
                definition  TEXT NOT NULL,
                description TEXT
            );)");  
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_contents (
                table_name TEXT NOT NULL PRIMARY KEY,
                data_type TEXT NOT NULL,
                identifier TEXT UNIQUE,
                description TEXT DEFAULT '',
                last_change DATETIME NOT NULL DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ','now')),
                min_x DOUBLE,
                min_y DOUBLE,
                max_x DOUBLE,
                max_y DOUBLE,
                srs_id INTEGER,
                CONSTRAINT fk_gc_r_srs_id FOREIGN KEY (srs_id) REFERENCES gpkg_spatial_ref_sys(srs_id)
            );)");
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_geometry_columns (
                table_name TEXT NOT NULL,
                column_name TEXT NOT NULL,
                geometry_type_name TEXT NOT NULL,
                srs_id INTEGER NOT NULL,
                z TINYINT NOT NULL,
                m TINYINT NOT NULL,
                CONSTRAINT pk_geom_cols PRIMARY KEY (table_name, column_name),
                CONSTRAINT uk_gc_table_name UNIQUE (table_name),
                CONSTRAINT fk_gc_tn FOREIGN KEY (table_name) REFERENCES gpkg_contents(table_name),
                CONSTRAINT fk_gc_srs FOREIGN KEY (srs_id) REFERENCES gpkg_spatial_ref_sys (srs_id)
            );)");
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_tile_matrix_set (
                table_name TEXT NOT NULL PRIMARY KEY,
                srs_id INTEGER NOT NULL,
                min_x DOUBLE NOT NULL,
                min_y DOUBLE NOT NULL,
                max_x DOUBLE NOT NULL,
                max_y DOUBLE NOT NULL,
                CONSTRAINT fk_gtms_table_name FOREIGN KEY (table_name) REFERENCES gpkg_contents(table_name),
                CONSTRAINT fk_gtms_srs FOREIGN KEY (srs_id) REFERENCES gpkg_spatial_ref_sys (srs_id)
            );)");
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_tile_matrix (
                table_name TEXT NOT NULL,
                zoom_level INTEGER NOT NULL,
                matrix_width INTEGER NOT NULL,
                matrix_height INTEGER NOT NULL,
                tile_width INTEGER NOT NULL,
                tile_height INTEGER NOT NULL,
                pixel_x_size DOUBLE NOT NULL,
                pixel_y_size DOUBLE NOT NULL,
                CONSTRAINT pk_ttm PRIMARY KEY (table_name, zoom_level),
                CONSTRAINT fk_tmm_table_name FOREIGN KEY (table_name) REFERENCES gpkg_contents(table_name)
            );)");
            db.exec(R"(CREATE TABLE IF NOT EXISTS gpkg_extensions (
                table_name TEXT,
                column_name TEXT,
                extension_name TEXT NOT NULL,
                definition TEXT NOT NULL,
                scope TEXT NOT NULL,
                CONSTRAINT ge_tce UNIQUE (table_name, column_name, extension_name)
            );)");
            db.exec(R"(CREATE TABLE IF NOT EXISTS layer_styles ( 
                id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                f_table_catalog VARCHAR(256),
                f_table_schema VARCHAR(256),
                f_table_name VARCHAR(256),
                f_geometry_column VARCHAR(256),
                styleName VARCHAR(30),
                styleQML TEXT,
                styleSLD TEXT,
                useAsDefault BOOLEAN,
                description VARCHAR,
                owner VARCHAR(30),
                ui VARCHAR(30),
                update_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );)");
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error creating geopackage tables: " << e.what() << std::endl;
        }
    }

    void GeoPackage::deleteTable(std::string name) {
         try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE TABLE IF NOT EXISTS " + name + ";");
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting tile table " << name << ": " << e.what() << std::endl;
        }    
    }

    std::string GeoPackage::getFileName() const {
        return fileName;
    }


    std::ostream& operator << (std::ostream& os, const GeoPackage& g) {
        os << "GEOPACKAGE (" << g.getFileName()  << ")";
        return os;
    }

    // SpatialRef

    void GeoPackage::insertDefaultSpatialRefs() {
        try {
            SQLite::Transaction transaction(db);
            db.exec(R"(INSERT INTO gpkg_spatial_ref_sys ("srs_name", "srs_id", "organization", "organization_coordsys_id", "definition", "description") 
            VALUES ('Undefined cartesian SRS', '-1', 'NONE', '-1', 'undefined', 'undefined cartesian coordinate reference system');)");  
            db.exec(R"(INSERT INTO gpkg_spatial_ref_sys ("srs_name", "srs_id", "organization", "organization_coordsys_id", "definition", "description") 
            VALUES ('Undefined cartesian SRS', '0', 'NONE', '0', 'undefined', 'undefined geographic coordinate reference system');)");  
            db.exec(R"(INSERT INTO gpkg_spatial_ref_sys ("srs_name", "srs_id", "organization", "organization_coordsys_id", "definition", "description") 
            VALUES ('epsg:3857', '3857', 'epsg', '3857', 'PROJCS["WGS 84 / Pseudo-Mercator", GEOGCS["WGS 84", 
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
            AUTHORITY["EPSG","3857"]]', 'epsg:3857');)");  
            db.exec(R"(INSERT INTO gpkg_spatial_ref_sys ("srs_name", "srs_id", "organization", "organization_coordsys_id", "definition", "description") 
            VALUES ('WGS84', '4326', 'EPSG', '4326', 'GEOGCS["WGS 84", DATUM["World Geodetic System 1984", SPHEROID["WGS 84", 6378137.0, 298.257223563, 
            AUTHORITY["EPSG","7030"]], AUTHORITY["EPSG","6326"]], PRIMEM["Greenwich", 0.0, AUTHORITY["EPSG","8901"]], UNIT["degree", 0.017453292519943295], 
            AXIS["Geodetic longitude", EAST], AXIS["Geodetic latitude", NORTH], AUTHORITY["EPSG","4326"]]', 
            'longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid');)");  
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error inserting default SpatialRefs: " << e.what() << std::endl;
        }
    }

    void GeoPackage::addSpatialRef(const SpatialRef& s) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_spatial_ref_sys (srs_name, srs_id, organization, organization_coordsys_id, definition, description) VALUES (?,?,?,?,?,?)");
            insert.bind(1, s.getSrsName());
            insert.bind(2, s.getSrsId());
            insert.bind(3, s.getOrganization());
            insert.bind(4, s.getOrganizationCoordSysId());
            insert.bind(5, s.getDefinition());
            insert.bind(6, s.getDescription());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a SpatialRef: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateSpatialRef(const SpatialRef& s) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_spatial_ref_sys SET srs_name = ?, organization = ?, organization_coordsys_id = ?, definition = ?, description = ? WHERE srs_id = ?");
            update.bind(1, s.getSrsName());
            update.bind(2, s.getOrganization());
            update.bind(3, s.getOrganizationCoordSysId());
            update.bind(4, s.getDefinition());
            update.bind(5, s.getDescription());
            update.bind(6, s.getSrsId());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a SpatialRef: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setSpatialRef(const SpatialRef& s) {
        auto spatialRef = getSpatialRef(s.getSrsId());
        if (spatialRef) {
            updateSpatialRef(s);
        } else {
            addSpatialRef(s);
        }
    }

    void GeoPackage::deleteSpatialRef(const SpatialRef& s) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM gpkg_spatial_ref_sys WHERE srs_id = ?");
            insert.bind(1, s.getSrsId());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a SpatialRef: " << e.what() << std::endl;
        }    
    }

    std::optional<SpatialRef> GeoPackage::getSpatialRef(int srsId) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT srs_name, srs_id, organization, organization_coordsys_id, definition, description FROM gpkg_spatial_ref_sys WHERE srs_id = ?");
            query.bind(1, srsId);
            if (query.executeStep()) {
                std::string srs_name = query.getColumn(0).getString();
                int srs_id = query.getColumn(1).getInt();
                std::string organization = query.getColumn(2).getString();
                int organization_coordsys_id = query.getColumn(3).getInt();
                std::string definition = query.getColumn(4).getString();
                std::string description = query.getColumn(5).getString();
                return SpatialRef{srs_name, srs_id, organization, organization_coordsys_id, definition, description};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a SpatialRef: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::spatialRefs(std::function<void(SpatialRef& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT srs_name, srs_id, organization, organization_coordsys_id, definition, description FROM gpkg_spatial_ref_sys");
            while (query.executeStep()) {
                std::string srs_name = query.getColumn(0).getString();
                int srs_id = query.getColumn(1).getInt();
                std::string organization = query.getColumn(2).getString();
                int organization_coordsys_id = query.getColumn(3).getInt();
                std::string definition = query.getColumn(4).getString();
                std::string description = query.getColumn(5).getString();
                SpatialRef statialRef{srs_name, srs_id, organization, organization_coordsys_id, definition, description};
                func(statialRef);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting SpatialRefs: " << e.what() << std::endl;
        }    
    }

    // Content

    void GeoPackage::addContent(const Content& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_contents (table_name, data_type, identifier, description, last_change, min_x, min_y, max_x, max_y, srs_id) VALUES (?,?,?,?,?,?,?,?,?,?)");
            insert.bind(1, extension.getTableName());
            insert.bind(2, datatype::toString(extension.getDataType()));
            insert.bind(3, extension.getIdentifier());
            insert.bind(4, extension.getDescription());
            insert.bind(5, extension.getLastChange());
            insert.bind(6, extension.getBounds().getMinX());
            insert.bind(7, extension.getBounds().getMinY());
            insert.bind(8, extension.getBounds().getMaxX());
            insert.bind(9, extension.getBounds().getMaxY());
            insert.bind(10, extension.getSrsId());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a Content " << extension << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateContent(const Content& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_contents SET data_type = ?, identifier = ?, description = ?, last_change = ?, min_x = ?, min_y = ?, max_x = ?, max_y = ?, srs_id = ? WHERE table_name = ?");
            update.bind(1, datatype::toString(extension.getDataType()));
            update.bind(2, extension.getIdentifier());
            update.bind(3, extension.getDescription());
            update.bind(4, extension.getLastChange());
            update.bind(5, extension.getBounds().getMinX());
            update.bind(6, extension.getBounds().getMinY());
            update.bind(7, extension.getBounds().getMaxX());
            update.bind(8, extension.getBounds().getMaxY());
            update.bind(9, extension.getSrsId());
            update.bind(10, extension.getTableName());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a Contents " << extension << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setContent(const Content& e) {
        auto extension = getContent(e.getTableName());
        if (extension) {
            updateContent(e);
        } else {
            addContent(e);
        }
    }

    void GeoPackage::deleteContent(const Content& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE FROM gpkg_contents WHERE table_name = ?");
            statement.bind(1, extension.getTableName());
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a Content: " << e.what() << std::endl;
        }    
    }

    std::optional<Content> GeoPackage::getContent(std::string tableName) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT table_name, data_type, identifier, description, last_change, min_x, min_y, max_x, max_y, srs_id FROM gpkg_contents WHERE table_name = ?");
            query.bind(1, tableName);
            if (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string data_type = query.getColumn(1).getString();
                std::string identifier = query.getColumn(2).getString();
                std::string description = query.getColumn(3).getString();
                std::string last_change = query.getColumn(4).getString();
                double min_x = query.getColumn(5).getDouble();
                double min_y = query.getColumn(6).getDouble();
                double max_x = query.getColumn(7).getDouble();
                double max_y = query.getColumn(8).getDouble();
                int srs_id = query.getColumn(9).getInt();
                return Content{table_name, datatype::getDataType(data_type), identifier, description, last_change, Bounds{min_x, min_y, max_x, max_y}, srs_id};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a Content: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::contents(std::function<void(Content& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, data_type, identifier, description, last_change, min_x, min_y, max_x, max_y, srs_id FROM gpkg_contents ORDER BY table_name");
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string data_type = query.getColumn(1).getString();
                std::string identifier = query.getColumn(2).getString();
                std::string description = query.getColumn(3).getString();
                std::string last_change = query.getColumn(4).getString();
                double min_x = query.getColumn(5).getDouble();
                double min_y = query.getColumn(6).getDouble();
                double max_x = query.getColumn(7).getDouble();
                double max_y = query.getColumn(8).getDouble();
                int srs_id = query.getColumn(9).getInt();
                Content content{table_name, datatype::getDataType(data_type), identifier, description, last_change, Bounds{min_x, min_y, max_x, max_y}, srs_id};
                func(content);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting Contents: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::contents(DataType dataType, std::function<void(Content& e)> func) {
        try {
            std::string type = datatype::toString(dataType);
            SQLite::Statement query(db, "SELECT table_name, data_type, identifier, description, last_change, min_x, min_y, max_x, max_y, srs_id FROM gpkg_contents WHERE data_type = ? ORDER BY table_name");
            query.bind(1, type);
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string data_type = query.getColumn(1).getString();
                std::string identifier = query.getColumn(2).getString();
                std::string description = query.getColumn(3).getString();
                std::string last_change = query.getColumn(4).getString();
                double min_x = query.getColumn(5).getDouble();
                double min_y = query.getColumn(6).getDouble();
                double max_x = query.getColumn(7).getDouble();
                double max_y = query.getColumn(8).getDouble();
                int srs_id = query.getColumn(9).getInt();
                Content content{table_name, datatype::getDataType(data_type), identifier, description, last_change, Bounds{min_x, min_y, max_x, max_y}, srs_id};
                func(content);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting Contents: " << e.what() << std::endl;
        }    
    }

    // Geometry Columns

    void GeoPackage::addGeometryColumn(const GeometryColumn& geometryColumn) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_geometry_columns (table_name, column_name, geometry_type_name, srs_id, z, m) VALUES (?,?,?,?,?,?)");
            insert.bind(1, geometryColumn.getTableName());
            insert.bind(2, geometryColumn.getColumnName());
            insert.bind(3, geometrytype::toString(geometryColumn.getGeometryType()));
            insert.bind(4, geometryColumn.getSrsId());
            insert.bind(5, geometryColumn.hasZ());
            insert.bind(6, geometryColumn.hasM());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a GeometryColumn " << geometryColumn << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateGeometryColumn(const GeometryColumn& geometryColumn) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_geometry_columns SET column_name = ?, geometry_type_name = ?, srs_id = ?, z = ?, m = ? WHERE table_name = ?");
            update.bind(1, geometryColumn.getColumnName());
            update.bind(2, geometrytype::toString(geometryColumn.getGeometryType()));
            update.bind(3, geometryColumn.getSrsId());
            update.bind(4, geometryColumn.hasZ());
            update.bind(5, geometryColumn.hasM());
            update.bind(6, geometryColumn.getTableName());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a GeometryColumns " << geometryColumn << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setGeometryColumn(const GeometryColumn& g) {
        auto extension = getGeometryColumn(g.getTableName());
        if (extension) {
            updateGeometryColumn(g);
        } else {
            addGeometryColumn(g);
        }
    }

    void GeoPackage::deleteGeometryColumn(const GeometryColumn& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE FROM gpkg_geometry_columns WHERE table_name = ?");
            statement.bind(1, extension.getTableName());
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a GeometryColumn: " << e.what() << std::endl;
        }    
    }

    std::optional<GeometryColumn> GeoPackage::getGeometryColumn(std::string tableName) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT table_name, column_name, geometry_type_name, srs_id, z, m FROM gpkg_geometry_columns WHERE table_name = ?");
            query.bind(1, tableName);
            if (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string column_name = query.getColumn(1).getString();
                std::string geometry_type_name = query.getColumn(2).getString();
                int srs_id = query.getColumn(3).getInt();
                bool z = query.getColumn(4).getInt();
                bool m = query.getColumn(5).getInt();
                Dimension dimension = dimension::getDimension(z, m);
                return GeometryColumn{table_name, column_name, geometrytype::getGeometryType(geometry_type_name), srs_id, dimension};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a GeometryColumn: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::geometryColumns(std::function<void(GeometryColumn& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, column_name, geometry_type_name, srs_id, z, m FROM gpkg_geometry_columns ORDER BY table_name, column_name");
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string column_name = query.getColumn(1).getString();
                std::string geometry_type_name = query.getColumn(2).getString();
                int srs_id = query.getColumn(3).getInt();
                bool z = query.getColumn(4).getInt();
                bool m = query.getColumn(5).getInt();
                Dimension dimension = dimension::getDimension(z, m);
                GeometryColumn geometryColumn{table_name, column_name, geometrytype::getGeometryType(geometry_type_name), srs_id, dimension};
                func(geometryColumn);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting GeometryColumns: " << e.what() << std::endl;
        }    
    }

    // Extension

    void GeoPackage::addExtension(const Extension& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_extensions (table_name, column_name, extension_name, definition, scope) VALUES (?,?,?,?,?)");
            insert.bind(1, extension.getTableName());
            insert.bind(2, extension.getColumnName());
            insert.bind(3, extension.getExtensionName());
            insert.bind(4, extension.getDefinition());
            insert.bind(5, scope::toString(extension.getScope()));
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a Extension " << extension << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateExtension(const Extension& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_extensions SET table_name = ?, column_name = ?, definition = ?, scope = ? WHERE extension_name = ?");
            update.bind(1, extension.getTableName());
            update.bind(2, extension.getColumnName());
            update.bind(3, extension.getDefinition());
            update.bind(4, scope::toString(extension.getScope()));
            update.bind(5, extension.getExtensionName());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a Extensions " << extension << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setExtension(const Extension& e) {
        auto extension = getExtension(e.getExtensionName());
        if (extension) {
            updateExtension(e);
        } else {
            addExtension(e);
        }
    }

    void GeoPackage::deleteExtension(const Extension& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE FROM gpkg_extensions WHERE extension_name = ?");
            statement.bind(1, extension.getExtensionName());
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a Extension: " << e.what() << std::endl;
        }    
    }

    std::optional<Extension> GeoPackage::getExtension(std::string extensionName) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT table_name, column_name, extension_name, definition, scope FROM gpkg_extensions WHERE extension_name = ?");
            query.bind(1, extensionName);
            if (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string column_name = query.getColumn(1).getString();
                std::string extension_name = query.getColumn(2).getString();
                std::string definition = query.getColumn(3).getString();
                std::string scope = query.getColumn(4).getString();
                return Extension{table_name, column_name, extension_name, definition, scope::getScope(scope)};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a Extension: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::extensions(std::function<void(Extension& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, column_name, extension_name, definition, scope FROM gpkg_extensions ORDER BY extension_name");
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                std::string column_name = query.getColumn(1).getString();
                std::string extension_name = query.getColumn(2).getString();
                std::string definition = query.getColumn(3).getString();
                std::string scope = query.getColumn(4).getString();
                Extension extension{table_name, column_name, extension_name, definition, scope::getScope(scope)};
                func(extension);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting Extensions: " << e.what() << std::endl;
        }    
    }

    // Tile Matrix Set

    void GeoPackage::addTileMatrixSet(const TileMatrixSet& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_tile_matrix_set (table_name, srs_id, min_x, min_y, max_x, max_y) VALUES (?,?,?,?,?,?)");
            insert.bind(1, t.getTableName());
            insert.bind(2, t.getSrsId());
            insert.bind(3, t.getBounds().getMinX());
            insert.bind(4, t.getBounds().getMinY());
            insert.bind(5, t.getBounds().getMaxX());
            insert.bind(6, t.getBounds().getMaxY());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a TileTatrixSet " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateTileMatrixSet(const TileMatrixSet& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_tile_matrix_set SET srs_id = ?, min_x = ?, min_y = ?, max_x = ?, max_y = ? WHERE table_name = ?");
            update.bind(1, t.getSrsId());
            update.bind(2, t.getBounds().getMinX());
            update.bind(3, t.getBounds().getMinY());
            update.bind(4, t.getBounds().getMaxX());
            update.bind(5, t.getBounds().getMaxY());
            update.bind(6, t.getTableName());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a TileTatrixSet " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setTileMatrixSet(const TileMatrixSet& t) {
        auto tileMatrixSet = getTileMatrixSet(t.getTableName());
        if (tileMatrixSet) {
            updateTileMatrixSet(t);
        } else {
            addTileMatrixSet(t);
        }
    }

    void GeoPackage::deleteTileMatrixSet(const TileMatrixSet& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE FROM gpkg_tile_matrix_set WHERE table_name = ?");
            statement.bind(1, t.getTableName());
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a TileMatrixSet: " << e.what() << std::endl;
        }    
    }

    std::optional<TileMatrixSet> GeoPackage::getTileMatrixSet(std::string tableName) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT table_name, srs_id, min_x, min_y, max_x, max_y FROM gpkg_tile_matrix_set WHERE table_name = ?");
            query.bind(1, tableName);
            if (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                int srs_id = query.getColumn(1).getInt();
                double min_x = query.getColumn(2).getDouble();
                double min_y = query.getColumn(3).getDouble();
                double max_x = query.getColumn(4).getDouble();
                double max_y = query.getColumn(5).getDouble();
                return TileMatrixSet{table_name, srs_id, Bounds{min_x, min_y, max_x, max_y}};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a TileMatrixSet: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::tileMatrixSets(std::function<void(TileMatrixSet& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, srs_id, min_x, min_y, max_x, max_y FROM gpkg_tile_matrix_set ORDER BY table_name");
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                int srs_id = query.getColumn(1).getInt();
                double min_x = query.getColumn(2).getDouble();
                double min_y = query.getColumn(3).getDouble();
                double max_x = query.getColumn(4).getDouble();
                double max_y = query.getColumn(5).getDouble();
                TileMatrixSet tileMatrixSet{table_name, srs_id, Bounds{min_x, min_y, max_x, max_y}};
                func(tileMatrixSet);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting TileMatrixSets: " << e.what() << std::endl;
        }    
    }

    // Tile Matrix

    void GeoPackage::addTileMatrix(const TileMatrix& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_tile_matrix (table_name, zoom_level, matrix_width, matrix_height, tile_width, tile_height, pixel_x_size, pixel_y_size) VALUES (?,?,?,?,?,?,?,?)");
            insert.bind(1, t.getTableName());
            insert.bind(2, t.getZoomLevel());
            insert.bind(3, t.getMatrixSize().getWidth());
            insert.bind(4, t.getMatrixSize().getHeight());
            insert.bind(5, t.getTileSize().getWidth());
            insert.bind(6, t.getTileSize().getHeight());
            insert.bind(7, t.getPixelSize().getWidth());
            insert.bind(8, t.getPixelSize().getHeight());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a TileMatrix " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateTileMatrix(const TileMatrix& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE gpkg_tile_matrix SET matrix_width = ?, matrix_height = ?, tile_width = ?, tile_height = ?, pixel_x_size = ?, pixel_y_size = ? WHERE table_name = ? AND zoom_level = ?");
            update.bind(1, t.getMatrixSize().getWidth());
            update.bind(2, t.getMatrixSize().getHeight());
            update.bind(3, t.getTileSize().getWidth());
            update.bind(4, t.getTileSize().getHeight());
            update.bind(5, t.getPixelSize().getWidth());
            update.bind(6, t.getPixelSize().getHeight());
            update.bind(7, t.getTableName());
            update.bind(8, t.getZoomLevel());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a TileTatrixSet " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setTileMatrix(const TileMatrix& t) {
        auto tileMatrixSet = getTileMatrix(t.getTableName(), t.getZoomLevel());
        if (tileMatrixSet) {
            updateTileMatrix(t);
        } else {
            addTileMatrix(t);
        }
    }

    void GeoPackage::deleteTileMatrix(const TileMatrix& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement statement(db, "DELETE FROM gpkg_tile_matrix WHERE table_name = ? AND zoom_level = ?");
            statement.bind(1, t.getTableName());
            statement.bind(2, t.getZoomLevel());
            statement.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a TileMatrix: " << e.what() << std::endl;
        }    
    }

    std::optional<TileMatrix> GeoPackage::getTileMatrix(std::string tableName, int zoomLevel) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT table_name, zoom_level, matrix_width, matrix_height, tile_width, tile_height, pixel_x_size, pixel_y_size FROM gpkg_tile_matrix WHERE table_name = ? AND zoom_level = ?");
            query.bind(1, tableName);
            query.bind(2, zoomLevel);
            if (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                int zoom_level = query.getColumn(1).getInt();
                int matrix_width = query.getColumn(2).getInt();
                int matrix_height = query.getColumn(3).getInt();
                int tile_width = query.getColumn(4).getInt();
                int tile_height = query.getColumn(5).getInt();
                double pixel_width = query.getColumn(6).getDouble();
                double pixel_height = query.getColumn(7).getDouble();
                return TileMatrix{table_name, zoom_level, Size<int>{matrix_width, matrix_height}, Size<int>{tile_width, tile_height}, Size<double>{pixel_width, pixel_height}};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a TileMatrix: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::tileMatrices(std::string name, std::function<void(TileMatrix& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, zoom_level, matrix_width, matrix_height, tile_width, tile_height, pixel_x_size, pixel_y_size FROM gpkg_tile_matrix WHERE table_name = ? ORDER BY zoom_level");
            query.bind(1, name);
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                int zoom_level = query.getColumn(1).getInt();
                int matrix_width = query.getColumn(2).getInt();
                int matrix_height = query.getColumn(3).getInt();
                int tile_width = query.getColumn(4).getInt();
                int tile_height = query.getColumn(5).getInt();
                double pixel_width = query.getColumn(6).getDouble();
                double pixel_height = query.getColumn(7).getDouble();
                TileMatrix tileMatrix{table_name, zoom_level, Size<int>{matrix_width, matrix_height}, Size<int>{tile_width, tile_height}, Size<double>{pixel_width, pixel_height}};
                func(tileMatrix);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting TileMatrices: " << e.what() << std::endl;
        }    
    }

    void  GeoPackage::tileMatrices(std::function<void(TileMatrix& s)> func) {
        try {
            SQLite::Statement query(db, "SELECT table_name, zoom_level, matrix_width, matrix_height, tile_width, tile_height, pixel_x_size, pixel_y_size FROM gpkg_tile_matrix ORDER BY table_name, zoom_level");
            while (query.executeStep()) {
                std::string table_name = query.getColumn(0).getString();
                int zoom_level = query.getColumn(1).getInt();
                int matrix_width = query.getColumn(2).getInt();
                int matrix_height = query.getColumn(3).getInt();
                int tile_width = query.getColumn(4).getInt();
                int tile_height = query.getColumn(5).getInt();
                double pixel_width = query.getColumn(6).getDouble();
                double pixel_height = query.getColumn(7).getDouble();
                TileMatrix tileMatrix{table_name, zoom_level, Size<int>{matrix_width, matrix_height}, Size<int>{tile_width, tile_height}, Size<double>{pixel_width, pixel_height}};
                func(tileMatrix);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting TileMatrices: " << e.what() << std::endl;
        }    
    }

    // Tile

    void GeoPackage::createTileTable(std::string name) {
         try {
            SQLite::Transaction transaction(db);
            SQLite::Statement create(db, "CREATE TABLE IF NOT EXISTS " + name + " (\n" +
                "   id           INTEGER PRIMARY KEY AUTOINCREMENT,\n" +
                "   zoom_level   INTEGER NOT NULL,\n" +
                "   tile_column  INTEGER NOT NULL,\n" +
                "   tile_row     INTEGER NOT NULL,\n" +
                "   tile_data    BLOB\n" +
                ");"
            );
            create.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error creating tile table " << name << ": " << e.what() << std::endl;
        }    
    }

    int GeoPackage::getMinZoom(std::string name) {
        SQLite::Statement query(db, "select min(zoom_level) as min_zoom_level from " + name);
        query.executeStep();
        return query.getColumn(0).getInt();
    }

    int GeoPackage::getMaxZoom(std::string name) {
        SQLite::Statement query(db, "select max(zoom_level) as max_zoom_level from " + name);
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    int GeoPackage::countTiles(std::string name, int zoom) {
        SQLite::Statement query(db, "select count(*) as tile_count from " + name + " where zoom_level = ?");
        query.bind(1, zoom);
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    int GeoPackage::countTiles(std::string name) {
        SQLite::Statement query(db, "select count(*) as tile_count from " + name);
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    void  GeoPackage::addTile(std::string name, const Tile& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO " + name + " (zoom_level, tile_column, tile_row, tile_data) VALUES (?,?,?,?)");
            insert.bind(1, t.zoom);
            insert.bind(2, t.column);
            insert.bind(3, t.row);
            insert.bind(4, std::data(t.data), t.data.size());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding Tile " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateTile(std::string name, const Tile& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE " + name + " SET tile_data = ? WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            update.bind(1, std::data(t.data), t.data.size());
            update.bind(2, t.zoom);
            update.bind(3, t.column);
            update.bind(4, t.row);
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating Tile " << t << ": " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setTile(std::string name, const Tile& t) {
        auto tile = getTile(name, t.zoom, t.column, t.row);
        if (tile) {
            updateTile(name, t);
        } else {
            addTile(name, t);
        }
    }

    void GeoPackage::deleteTile(std::string name, const Tile& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM " + name + " WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            insert.bind(1, t.zoom);
            insert.bind(2, t.column);
            insert.bind(3, t.row);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting Tile " << t << ": " << e.what() << std::endl;
        }    
    }

    std::optional<Tile> GeoPackage::getTile(std::string name, int z, int c, int r) {
        try {
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, tile_data FROM " + name + " WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
            query.bind(1, z);
            query.bind(2, c);
            query.bind(3, r);
            if (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                return Tile{zoom, column, row, data};
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting tile for " << name << " at " << z << "/" << c << "/" << r << ": " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void  GeoPackage::tiles(std::string name, int zoom, std::function<void(Tile& t)> func) {
        try {
            SQLite::Statement query(db, "SELECT zoom_level, tile_column, tile_row, tile_data FROM " + name + " WHERE zoom_level = ?");
            query.bind(1, zoom);
            while (query.executeStep()) {
                int zoom = query.getColumn(0).getInt();
                int column = query.getColumn(1).getInt();
                int row = query.getColumn(2).getInt();
                auto blobColumn = query.getColumn(3);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<byte> data(bytes, bytes + numberOfBytes);
                Tile tile {zoom, column, row, data};
                func(tile);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting tiles for " << name << " at " << zoom << ": " << e.what() << std::endl;
        }    
    
    }

    void GeoPackage::exportTilesToDirectory(std::string name, std::string format, std::string directory) {
        std::filesystem::path dir = directory;
        std::filesystem::create_directories(dir);
        const int minZoom = getMinZoom(name);
        const int maxZoom = getMaxZoom(name);
        for(int z = minZoom; z <= maxZoom; ++z) {
            std::string zoomDir = directory + "/" + std::to_string(z);
            std::filesystem::create_directories(zoomDir);   
            tiles(name, z, [&](Tile& t) {
               std::string tileDir = zoomDir + "/" + std::to_string(t.column);
               std::filesystem::create_directories(tileDir);
               t.save(tileDir + "/" + std::to_string(t.row) + "." + format);
            });
        } 
    }

    void GeoPackage::loadTilesFromDirectory(std::string name, std::string directory) {
        for (auto& dirEntry: std::filesystem::recursive_directory_iterator(directory)) {
            if (dirEntry.is_regular_file()) {
                std::filesystem::path file = dirEntry.path();
                if (isImage(file.extension())) {
                    int z = std::stoi(file.parent_path().parent_path().stem());
                    int c = std::stoi(file.parent_path().stem());
                    int r = std::stoi(file.filename().stem());
                    const Tile t {z,c,r,std::filesystem::absolute(file)};
                    addTile(name, t);
                }
            }
        }
    }

    bool GeoPackage::isImage(std::string extension) {
        return extension == ".jpeg" || extension == ".jpg" || extension == ".png";
    }

    void GeoPackage::createGlobalGeodeticTileLayer(std::string name, int tileSize, int maxZoomLevel) {
        int srsId = 4326;
        Bounds bounds = Bounds::getGeodeticBounds();
        
        // Spatial Reference
        if (!getSpatialRef(srsId).has_value()) {
            addSpatialRef(SpatialRef{
                "WGS84", 4326, 
                "EPSG", 4326,
                R"(GEOGCS["WGS 84", DATUM["World Geodetic System 1984", SPHEROID["WGS 84", 6378137.0, 298.257223563, AUTHORITY["EPSG","7030"]], AUTHORITY["EPSG","6326"]], PRIMEM["Greenwich", 0.0, AUTHORITY["EPSG","8901"]], UNIT["degree", 0.017453292519943295], AXIS["Geodetic longitude", EAST], AXIS["Geodetic latitude", NORTH], AUTHORITY["EPSG","4326"]])", 
                "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid');)" 
            });
        }

        // Content
        setContent(Content{
            name, DataType::TILES, name, name, bounds, srsId
        });

        // TileMatrixSet
        setTileMatrixSet(TileMatrixSet{ name, srsId, bounds });
        
        // TileMatrix
        for(int z = 0; z < maxZoomLevel; z++) {
            int col = std::pow(2, z + 1);
            int row = std::pow(2, z);
            double res = 0.703125 / std::pow(2, z);
            setTileMatrix(TileMatrix{name, z, Size<int>{col, row}, Size<int>{tileSize, tileSize}, Size<double>{res, res} });
        }

        // Table
        createTileTable(name);
    }

    void GeoPackage::createGlobalMercatorTileLayer(std::string name, int tileSize, int maxZoomLevel) {
        int srsId = 3857;
        Bounds bounds = Bounds::getMercatorBounds();
        
        // Spatial Reference
        if (!getSpatialRef(srsId).has_value()) {
            addSpatialRef(SpatialRef{
                "EPSG:3857", 3857, 
                "EPSG", 3857,
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
                AUTHORITY["EPSG","3857"]]])", 
                "Web Mercator" 
            });
        }

        // Content
        setContent(Content{
            name, DataType::TILES, name, name, bounds, srsId
        });

        // TileMatrixSet
        setTileMatrixSet(TileMatrixSet{ name, srsId, bounds });
        
        // TileMatrix
        for(int z = 0; z < maxZoomLevel; z++) {
            int n = std::pow(2, z);
            double res = 156412.0 / n;
            setTileMatrix(TileMatrix{name, z, Size<int>{n, n}, Size<int>{tileSize, tileSize}, Size<double>{res, res} });
        }

        // Table
        createTileTable(name);
    }

    // Feature

    void GeoPackage::createFeatureTable(const Schema& schema) {
        std::stringstream sql;
        sql << "CREATE TABLE IF NOT EXISTS " << schema.getName() << " (\n";
        sql << "   " << schema.getKey() << " INTEGER PRIMARY KEY AUTOINCREMENT,\n";
        sql << "   " << schema.getGeometryField().getName() << " BLOB";
        for(const auto& fld : schema.getFields()) {
           sql << ",\n   " << fld.getName() << " " << fieldtype::getDatabaseType(fld.getType());
        }
        sql << "\n)\n";
        try {
            SQLite::Statement query(db, sql.str());
            query.exec();
        }
        catch (std::exception& e) {
            std::cout << "Error creating feature table for " << schema << ": " << e.what() << std::endl;
        }
    }

    std::string GeoPackage::now() {
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

    void GeoPackage::createFeatureLayer(const Schema& schema, const Bounds& bounds) {
        addContent(geopackage::Content{
            schema.getName(), 
            geopackage::DataType::FEATURES, 
            schema.getName(), 
            schema.getName(), 
            now(), 
            bounds, 
            schema.getGeometryField().getSrsId()
        });
        addGeometryColumn(geopackage::GeometryColumn{
            schema.getName(), 
            schema.getGeometryField().getName(), 
            schema.getGeometryField().getType(), 
            schema.getGeometryField().getSrsId(), 
            schema.getGeometryField().getDimension()
        });
        createFeatureTable(schema);
    }

    void GeoPackage::addFeature(std::string name, const Feature& feature) {
        std::stringstream sql;
        Geometry* geometry = feature.getGeometry();
        GeoPackageGeometryWriter geometryWriter{};
        std::vector<std::byte> geometryBytes = geometryWriter.write(geometry);
        sql << "INSERT INTO " << name << " (";
        sql << "geometry";
        for(const auto& attribute : feature.getAttributes()) {
           sql << ", ";
           sql << attribute.first;
        }
        sql << ") VALUES (";
        sql << "?";
        for(int i = 0; i < feature.getAttributes().size(); ++i) {
           sql << ", "; 
           sql << "?";
        }
        sql << ")";
        try {
            SQLite::Statement query(db, sql.str());
            query.bind(1, geometryBytes.data(), geometryBytes.size());
            int counter = 2;
            bindFeatureValues(query, feature, counter);
            query.exec();
        }
        catch (std::exception& e) {
            std::cout << "Error adding feature " << feature << " table to " << name << ": " << e.what() << std::endl;
        }
    }

    int GeoPackage::bindFeatureValues(SQLite::Statement& statement, Feature feature, int startIndex) {
        int counter = startIndex;
        for(const auto& attribute : feature.getAttributes()) {
            std::any value = attribute.second;
            bindFeatureValue(statement, value, counter);
            counter++;
        }
        return counter;
    }

    bool GeoPackage::doesTableExist(std::string name) {
        std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + name + "';";
        try {
            SQLite::Statement query(db, sql);
            return query.executeStep();
        }
        catch (std::exception& e) {
            std::cout << "Error checking for table named " << name << ": " << e.what() << std::endl;
        }
        return false;
    }

    Schema GeoPackage::getSchema(std::string name) {

        std::string key = "id";
        std::vector<Field> fields;
        GeometryType geometryType = GeometryType::GEOMETRY;
        std::string geometryName = "geom";
        int srsId = -1;

        std::optional<GeometryColumn> geometryColumn = getGeometryColumn(name);
        if (geometryColumn.has_value()) {
            GeometryColumn gc = geometryColumn.value();
            geometryName = gc.getColumnName();
            geometryType = gc.getGeometryType();
            srsId = gc.getSrsId();
        }

        try {
            SQLite::Statement query(db, "SELECT * FROM pragma_table_info('" + name + "')");
            while (query.executeStep()) {
                std::string name = query.getColumn(1).getString();
                std::string type = query.getColumn(2).getString();
                int primaryKey = query.getColumn(5).getInt();
                if (primaryKey == 1) {
                    key = name;
                } else if (name != geometryName) {
                    fields.push_back(Field{name, fieldtype::getFieldType(type)});
                }
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting fields for " << name << ": " << e.what() << std::endl;
        }

        return Schema{name, key, GeometryField{geometryName, geometryType, srsId}, fields};
    }

    std::vector<std::string> GeoPackage::getColumnNames(std::string table) {
        std::vector<std::string> columnNames;
        try {
            SQLite::Statement query(db, "SELECT * FROM pragma_table_info('" + table + "') ");
            while (query.executeStep()) {
                std::string name = query.getColumn(1).getString();
                columnNames.push_back(name);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting get column names for " << table << ": " << e.what() << std::endl;
        }
        return columnNames;
    }

    std::string GeoPackage::getPrimaryKey(std::string tableName) {
        try {
            SQLite::Statement query(db, "SELECT name FROM PRAGMA_TABLE_INFO('" + tableName + "') WHERE pk = 1");
            bool foundRow = query.executeStep();
            if (foundRow) {
                std::string name = query.getColumn(0).getString();
                return name;
            } else {
                return "id";
            }
        } 
        catch (std::exception& e) {
            std::cout << "Error getting primary key for " << tableName << ": " << e.what() << std::endl;
        }
        return "id";
    }

    std::string GeoPackage::getGeometryColumnName(std::string tableName) {
        std::optional<GeometryColumn> geometryColumn = getGeometryColumn(tableName);
        if (geometryColumn.has_value()) {
            GeometryColumn gc = geometryColumn.value();
            return gc.getColumnName();
        } else {
            return "geometry";
        }
    }

    int GeoPackage::countFeatures(std::string name) {
        SQLite::Statement query(db, "select count(*) as feature_count from " + name);
        query.executeStep();
        return query.getColumn(0).getInt();    
    }

    void GeoPackage::setFeature(std::string name, const Feature& f) {
        if (f.getId().has_value()) {
            auto feature = getFeature(name, f.getId().value());
            if (feature) {
                updateFeature(name, f);
            } else {
                addFeature(name, f);
            }
        } else {
             addFeature(name, f);
        }
    }

    void GeoPackage::updateFeature(std::string name, const Feature& f) {

        std::stringstream sql;

        std::string primaryKey = getPrimaryKey(name);
        std::string geometryColumn = getGeometryColumnName(name);

        Geometry* geometry = f.getGeometry();
        GeoPackageGeometryWriter geometryWriter{};
        std::vector<std::byte> geometryBytes = geometryWriter.write(geometry);

        sql << "UPDATE " << name  << " SET ";
        sql << geometryColumn << " = ?";
        for(const auto& attribute : f.getAttributes()) {
           if (attribute.first != primaryKey) { 
            sql << ", " << attribute.first << " = ?";
           }
        }
        sql << " WHERE " << primaryKey << " =  ? ";

        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, sql.str());
            update.bind(1, geometryBytes.data(), geometryBytes.size());
            int index = bindFeatureValuesForUpdate(update, f, primaryKey, 2);
            update.bind(index, f.getId().value());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating Feature " << f << ": " << e.what() << std::endl;
        }    
    }

    int GeoPackage::bindFeatureValuesForUpdate(SQLite::Statement& statement, Feature feature, std::string primaryKey, int startIndex) {
        int counter = startIndex;
        for(const auto& attribute : feature.getAttributes()) {
            std::string name = attribute.first;
            if (name!= primaryKey) {
                std::any value = attribute.second;
                bindFeatureValue(statement, value, counter);
                counter++;
            }
        }
        return counter;
    }

    void GeoPackage::bindFeatureValue(SQLite::Statement& statement, std::any value, int index) {
        if (value.type() == typeid(std::string)) {
            std::string stringValue = std::any_cast<std::string>(value);
            statement.bind(index, stringValue);
        } else if (value.type() == typeid(const char*)) {
            std::string stringValue { std::any_cast<const char*>(value) };
            statement.bind(index, stringValue);
        } else if (value.type() == typeid(double)) {
            double doubleValue = std::any_cast<double>(value);
            statement.bind(index, doubleValue);
        } else if (value.type() == typeid(int)) {
            int intValue = std::any_cast<int>(value);
            statement.bind(index, intValue);
        } else if (value.type() == typeid(bool)) {
            bool boolValue = std::any_cast<bool>(value);
            statement.bind(index, boolValue);
        } 
    }

    void GeoPackage::deleteFeature(std::string name, const Feature& f) {
        std::string primaryKey = getPrimaryKey(name);
        std::optional<int> id = f.getId();
        if (id.has_value()) {
            try {
                SQLite::Transaction transaction(db);
                SQLite::Statement insert(db, "DELETE FROM " + name + " WHERE " + primaryKey + " = ?");
                insert.bind(1, id.value());
                insert.exec();
                transaction.commit();
            }
            catch (std::exception& e) {
                std::cout << "Error deleting Feature " << f << ": " << e.what() << std::endl;
            }    
        }
    }

    void GeoPackage::deleteAllFeatures(std::string name) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM " + name);
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting all Features from " << name << ": " << e.what() << std::endl;
        }    
    }

     std::optional<Feature> GeoPackage::getFeature(std::string name, int id) {
        std::stringstream sql;
        Schema schema = getSchema(name);
        std::string primaryKey = schema.getKey();
        std::vector<Field> fields = schema.getFields();
        std::map<std::string, FieldType> fieldMap;
        for(const auto& field : fields) {
           fieldMap[field.getName()] = field.getType();
        }
        std::string geometryColumnName = schema.getGeometryField().getName();
        GeoPackageGeometryReader reader;

        sql << "SELECT ";
        sql << primaryKey << ", " << geometryColumnName;
        for(const auto& field : fields) {
            sql << ", " << field.getName();
        }
        sql << " FROM " << name;
        sql << " WHERE " << primaryKey << " =  ? ";   

        try {
            SQLite::Statement query(db, sql.str());
            query.bind(1, id);
            if (query.executeStep()) {
                return getFeature(query, reader, geometryColumnName, primaryKey, fieldMap);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting feature for " << name << " with " << id << ": " << e.what() << std::endl;
        }    
        return std::nullopt;
    }


    Feature GeoPackage::getFeature(SQLite::Statement& query, GeoPackageGeometryReader& reader, std::string geometryColumnName, std::string primaryKey, std::map<std::string, FieldType> fieldMap) {
        int id = -1;
        std::optional<std::unique_ptr<Geometry>> geometry;
        std::map<std::string, std::any> attributes;
        for(int i = 0; i < query.getColumnCount(); ++i) {
            std::string columnName = query.getColumnName(i);
            if (columnName == geometryColumnName) {
                auto blobColumn = query.getColumn(i);
                const byte* bytes = static_cast<const byte*>(blobColumn.getBlob());
                size_t numberOfBytes = blobColumn.getBytes();
                std::vector<std::byte> data;
                for(int i = 0; i<numberOfBytes; i++) {
                    data.push_back(std::byte{bytes[i]});
                }
                geometry = reader.read(data);
            } else if (columnName == primaryKey) {  
                id = query.getColumn(i).getInt();
            } else {
                FieldType fieldType = fieldMap[columnName];
                if (fieldType == FieldType::String) {
                    attributes[columnName] = query.getColumn(i).getString();
                } else if (fieldType == FieldType::Double) {
                    attributes[columnName] = query.getColumn(i).getDouble();
                } else if (fieldType == FieldType::Integer) {
                    attributes[columnName] = query.getColumn(i).getInt();
                } else if (fieldType == FieldType::Boolean) {
                    attributes[columnName] = query.getColumn(i).getInt();
                } else if (fieldType == FieldType::Blob) {
                    attributes[columnName] = query.getColumn(i).getString();
                } else if (fieldType == FieldType::Geometry) {
                    attributes[columnName] = query.getColumn(i).getString();
                }
            }
        }
        return Feature{id, geometry.value()->clone(), attributes};
    }

    void GeoPackage::features(std::string name, std::function<void(Feature& feature)> func) {
        Schema schema = getSchema(name);
        std::string primaryKey = schema.getKey();
        std::vector<Field> fields = schema.getFields();
        std::map<std::string, FieldType> fieldMap;
        for(const auto& field : fields) {
           fieldMap[field.getName()] = field.getType();
        }
        std::string geometryColumnName = schema.getGeometryField().getName();
        GeoPackageGeometryReader reader;

        try {
            SQLite::Statement query(db, "SELECT * FROM " + name);
            while (query.executeStep()) {
                Feature feature = getFeature(query,reader,  geometryColumnName, primaryKey, fieldMap);
                func(feature);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting features for " << name << ": " << e.what() << std::endl;
        }    
    }

    // Layer Styles

    void GeoPackage::addLayerStyle(const LayerStyle& t) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO layer_styles (f_table_catalog, f_table_schema, f_table_name, f_geometry_column, styleName, styleSLD, styleQML, useAsDefault, description, owner, ui) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
            insert.bind(1, t.getTableCatalog());
            insert.bind(2, t.getTableSchema());
            insert.bind(3, t.getTableName());
            insert.bind(4, t.getGeometryColumn());
            insert.bind(5, t.getStyleName());
            insert.bind(6, t.getStyleSLD());
            insert.bind(7, t.getStyleQML());
            insert.bind(8, t.getUseAsDefault());
            insert.bind(9, t.getDescription());
            insert.bind(10, t.getOwner());
            insert.bind(11, t.getUi());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error adding a SpatialRef: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::updateLayerStyle(const LayerStyle& t) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction transaction(db);
            SQLite::Statement update(db, "UPDATE layer_styles SET f_table_catalog = ?, f_table_schema = ?, f_table_name = ?, f_geometry_column = ?, styleName = ?, styleSLD = ?, styleQML = ?, useAsDefault = ?, description = ?, owner = ?, ui = ? WHERE id = ?");
            update.bind(1, t.getTableCatalog());
            update.bind(2, t.getTableSchema());
            update.bind(3, t.getTableName());
            update.bind(4, t.getGeometryColumn());
            update.bind(5, t.getStyleName());
            update.bind(6, t.getStyleSLD());
            update.bind(7, t.getStyleQML());
            update.bind(8, t.getUseAsDefault());
            update.bind(9, t.getDescription());
            update.bind(10, t.getOwner());
            update.bind(11, t.getUi());
            update.bind(12, t.getId());
            update.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error updating a SpatialRef: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::setLayerStyle(const LayerStyle& s) {
        auto layerStyle = getLayerStyle(s.getId());
        if (layerStyle) {
            updateLayerStyle(s);
        } else {
            addLayerStyle(s);
        }
    }

    void GeoPackage::deleteLayerStyle(const LayerStyle& s) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "DELETE FROM layer_styles WHERE id = ?");
            insert.bind(1, s.getId());
            insert.exec();
            transaction.commit();
        }
        catch (std::exception& e) {
            std::cout << "Error deleting a LayerStyle: " << e.what() << std::endl;
        }    
    }

    std::optional<LayerStyle> GeoPackage::getLayerStyle(int id) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT id, f_table_catalog, f_table_schema, f_table_name, f_geometry_column, styleName, styleSLD,styleQML,useAsDefault, description, owner,ui,update_time FROM layer_styles WHERE id = ?");
            query.bind(1, id);
            if (query.executeStep()) {
                int id = query.getColumn(0).getInt();
                std::string tableCatalog = query.getColumn(1).getString();
                std::string tableSchema = query.getColumn(2).getString();
                std::string tableName = query.getColumn(3).getString();
                std::string geometryColumn = query.getColumn(4).getString();
                std::string styleName = query.getColumn(5).getString();
                std::string styleSLD = query.getColumn(6).getString();
                std::string styleQML = query.getColumn(7).getString();
                bool useAsDefault = query.getColumn(8).getInt();
                std::string description = query.getColumn(9).getString();
                std::string owner = query.getColumn(10).getString();
                std::string ui = query.getColumn(11).getString();
                std::string updateTime = query.getColumn(12).getString();
                return LayerStyle{id, tableCatalog, tableSchema, tableName, geometryColumn, styleName, styleQML, styleSLD, useAsDefault, description, owner, ui, updateTime };
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a LayerStyle: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    std::optional<LayerStyle> GeoPackage::getDefaultLayerStyle(std::string name) {
        try {
            SQLite::Database db(fileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement query(db, "SELECT id, f_table_catalog, f_table_schema, f_table_name, f_geometry_column, styleName, styleSLD,styleQML,useAsDefault, description, owner,ui,update_time FROM layer_styles WHERE f_table_name = ? AND useAsDefault = true");
            query.bind(1, name);
            if (query.executeStep()) {
                int id = query.getColumn(0).getInt();
                std::string tableCatalog = query.getColumn(1).getString();
                std::string tableSchema = query.getColumn(2).getString();
                std::string tableName = query.getColumn(3).getString();
                std::string geometryColumn = query.getColumn(4).getString();
                std::string styleName = query.getColumn(5).getString();
                std::string styleSLD = query.getColumn(6).getString();
                std::string styleQML = query.getColumn(7).getString();
                bool useAsDefault = query.getColumn(8).getInt();
                std::string description = query.getColumn(9).getString();
                std::string owner = query.getColumn(10).getString();
                std::string ui = query.getColumn(11).getString();
                std::string updateTime = query.getColumn(12).getString();
                return LayerStyle{id, tableCatalog, tableSchema, tableName, geometryColumn, styleName, styleQML, styleSLD, useAsDefault, description, owner, ui, updateTime };
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting a LayerStyle: " << e.what() << std::endl;
        }    
        return std::nullopt;
    }

    void GeoPackage::layerStyles(std::function<void(LayerStyle& s)> f) {
        try {
            SQLite::Statement query(db, "SELECT id,f_table_catalog, f_table_schema, f_table_name, f_geometry_column, styleName, styleSLD, styleQML, useAsDefault, description, owner, ui, update_time FROM layer_styles");
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt();
                std::string tableCatalog = query.getColumn(1).getString();
                std::string tableSchema = query.getColumn(2).getString();
                std::string tableName = query.getColumn(3).getString();
                std::string geometryColumn = query.getColumn(4).getString();
                std::string styleName = query.getColumn(5).getString();
                std::string styleSLD = query.getColumn(6).getString();
                std::string styleQML = query.getColumn(7).getString();
                bool useAsDefault = query.getColumn(8).getInt();
                std::string description = query.getColumn(9).getString();
                std::string owner = query.getColumn(10).getString();
                std::string ui = query.getColumn(11).getString();
                std::string updateTime = query.getColumn(12).getString();
                LayerStyle layerStyle{id, tableCatalog, tableSchema, tableName, geometryColumn, styleName, styleQML, styleSLD, useAsDefault, description, owner, ui, updateTime };
                f(layerStyle);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting LayerStyles: " << e.what() << std::endl;
        }    
    }

    void GeoPackage::layerStylesForLayer(std::string name, std::function<void(LayerStyle& s)> f) {
        try {
            SQLite::Statement query(db, "SELECT id, f_table_catalog, f_table_schema, f_table_name, f_geometry_column, styleName, styleSLD, styleQML, useAsDefault, description, owner, ui, update_time FROM layer_styles WHERE f_table_name = ?");
            query.bind(1, name);
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt();
                std::string tableCatalog = query.getColumn(1).getString();
                std::string tableSchema = query.getColumn(2).getString();
                std::string tableName = query.getColumn(3).getString();
                std::string geometryColumn = query.getColumn(4).getString();
                std::string styleName = query.getColumn(5).getString();
                std::string styleSLD = query.getColumn(6).getString();
                std::string styleQML = query.getColumn(7).getString();
                bool useAsDefault = query.getColumn(8).getInt();
                std::string description = query.getColumn(9).getString();
                std::string owner = query.getColumn(10).getString();
                std::string ui = query.getColumn(11).getString();
                std::string updateTime = query.getColumn(12).getString();
                LayerStyle layerStyle{id, tableCatalog, tableSchema, tableName, geometryColumn, styleName, styleQML, styleSLD, useAsDefault, description, owner, ui, updateTime };
                f(layerStyle);
            }
        }
        catch (std::exception& e) {
            std::cout << "Error getting LayerStyles: " << e.what() << std::endl;
        }    
    }

}
