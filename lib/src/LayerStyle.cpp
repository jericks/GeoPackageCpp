#include "LayerStyle.hpp"

namespace geopackage {

    LayerStyle::LayerStyle(
        int id,
        std::string tableCatalog,
        std::string tableSchema,
        std::string tableName,
        std::string geometryColumn,
        std::string styleName,
        std::string styleQML,
        std::string styleSLD,
        bool useAsDefault,
        std::string description,
        std::string owner,
        std::string ui,
        std::string updateTime
    ) : id(id),
        tableCatalog(tableCatalog),
        tableSchema(tableSchema),
        tableName(tableName),
        geometryColumn(geometryColumn),
        styleName(styleName),
        styleQML(styleQML),
        styleSLD(styleSLD),
        useAsDefault(useAsDefault),
        description(description),
        owner(owner),
        ui(ui),
        updateTime(updateTime)
    {}

    LayerStyle::LayerStyle(
        std::string tableCatalog,
        std::string tableSchema,
        std::string tableName,
        std::string geometryColumn,
        std::string styleName,
        std::string styleQML,
        std::string styleSLD,
        bool useAsDefault,
        std::string description,
        std::string owner,
        std::string ui
    ) : tableCatalog(tableCatalog),
        tableSchema(tableSchema),
        tableName(tableName),
        geometryColumn(geometryColumn),
        styleName(styleName),
        styleQML(styleQML),
        styleSLD(styleSLD),
        useAsDefault(useAsDefault),
        description(description),
        owner(owner),
        ui(ui),
        updateTime(now())
    {}

    std::string LayerStyle::now() {
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

    int LayerStyle::getId() const {
        return id;
    }

    std::string LayerStyle::getTableCatalog() const {
        return tableCatalog;
    }

    std::string LayerStyle::getTableSchema() const {
        return tableSchema;
    }

    std::string LayerStyle::getTableName() const {
        return tableName;
    }

    std::string LayerStyle::getGeometryColumn() const {
        return geometryColumn;
    }

    std::string LayerStyle::getStyleName() const {
        return styleName;
    }

    std::string LayerStyle::getStyleQML() const {
        return styleQML;
    }

    std::string LayerStyle::getStyleSLD() const {
        return styleSLD;
    }

    bool LayerStyle::getUseAsDefault() const {
        return useAsDefault;
    }

    std::string LayerStyle::getDescription() const {
        return description;
    }

    std::string LayerStyle::getOwner() const {
        return owner;
    }

    std::string LayerStyle::getUi() const {
        return ui;
    }

    std::string LayerStyle::getUpdateTime() const {
        return updateTime;
    }

     std::ostream& operator << (std::ostream& os, const LayerStyle& ls) {
        os  << "LAYERSTYLE (" 
            << "id = " << ls.getId()
            << ", tableCatalog = " << ls.getTableCatalog()
            << ", tableSchema = " << ls.getTableSchema()
            << ", tableName = " << ls.getTableName()
            << ", geometryColumn = " << ls.getGeometryColumn()
            << ", styleName = " << ls.getStyleName()
            << ", styleQML = " << ls.getStyleQML()
            << ", styleSLD = " << ls.getStyleSLD()
            << ", useAsDefault = " << ls.getUseAsDefault()
            << ", description = " << ls.getDescription()
            << ", owner = " << ls.getOwner()
            << ", ui = " << ls.getUi()
            << ", updateTime = " << ls.getUpdateTime()
                << ")";
        return os;
    }

}