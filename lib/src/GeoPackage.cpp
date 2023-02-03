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
            db.exec(R"(CREATE TABLE gpkg_extensions (
                table_name TEXT,
                column_name TEXT,
                extension_name TEXT NOT NULL,
                definition TEXT NOT NULL,
                scope TEXT NOT NULL,
                CONSTRAINT ge_tce UNIQUE (table_name, column_name, extension_name)
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

    // Geometry Columns

    // Extension

    void GeoPackage::addExtension(const Extension& extension) {
        try {
            SQLite::Transaction transaction(db);
            SQLite::Statement insert(db, "INSERT INTO gpkg_extensions (table_name, column_name, extension_name, definition, scope) VALUES (?,?,?,?,?)");
            insert.bind(1, extension.getTableName());
            insert.bind(2, extension.getColumnName());
            insert.bind(3, extension.getExtensionName());
            insert.bind(4, extension.getDefinition());
            insert.bind(5, extension.getScope());
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
            update.bind(4, extension.getScope());
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
                return Extension{table_name, column_name, extension_name, definition, scope};
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
                Extension extension{table_name, column_name, extension_name, definition, scope};
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
                "   zoom_level   INTEGER NOT NULL\n" +
                "   tile_column  INTEGER NOT NULL\n" +
                "   tile_row     INTEGER NOT NULL\n" +
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

    // Feature


}
