#include "search.h"

Search::Search(Query query)
{
    setQuery(query);
}

void Search::setQuery(const Query query)
{
    m_dsl["query"] = query.toJson();
}

void Search::setFilter(const Query query)
{
    m_dsl["filter"] = query.toJson();
}

void Search::addSort(const Sort sort)
{
    if (m_dsl["sort"].isNull()) {
        m_dsl["sort"] = Json::Value(Json::arrayValue);
    }
    m_dsl["sort"].append(sort.toJson());
}

void Search::setFrom(const int from)
{
    m_dsl["from"] = from;
}

void Search::setSize(const int size)
{
    m_dsl["size"] = size;
}

Json::Value Search::toJson() const
{
    return m_dsl;
}
