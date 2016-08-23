#ifndef ELASTICPLUSPLUS_SEARCH_H
#define ELASTICPLUSPLUS_SEARCH_H

#include <json/json.h>
#include "query.h"
#include "sort.h"

class Search
{
public:
    explicit Search(const Query query);
    void setQuery(const Query query);
    void setFilter(const Query filter);
    void addSort(const Sort sort);
    void setFrom(const int from);
    void setSize(const int size);
    Json::Value toJson() const;
    template<typename ... Types>
    void addFields(const std::string fieldName, Types ... rest)
    {
        if (m_dsl["fields"].isNull()) {
            m_dsl["fields"] = Json::Value(Json::arrayValue);
        }
        m_dsl["fields"].append(fieldName);
        addFields(rest...);
    }

private:
    Json::Value m_dsl;
    void addFields() {}
};

#endif
