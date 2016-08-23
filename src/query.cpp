#include "query.h"

Query::Query(Json::Value value)
{
    m_query = value;
}

Query operator+(Query lhs, const Query& rhs)
{
    BoolQuery bq;
    bq.must(lhs, rhs);
    return bq;

}
Query operator|(Query lhs, const Query& rhs)
{
    BoolQuery bq;
    bq.should(lhs, rhs);
    return bq;

}
Query operator&(Query lhs, const Query& rhs)
{
    return lhs + rhs;
}

Json::Value Query::toJson() const
{
    return m_query;
}

BoolQuery::BoolQuery() : Query(Json::Value(Json::objectValue))
{
    m_query["bool"] = Json::Value(Json::objectValue);
    m_query["bool"]["must"] = Json::Value(Json::arrayValue);
    m_query["bool"]["must_not"] = Json::Value(Json::arrayValue);
    m_query["bool"]["should"] = Json::Value(Json::arrayValue);
    m_query["bool"]["filter"] = Json::Value(Json::arrayValue);
};





void MatchQuery::setOperator(std::string matchOperator)
{

    m_query["match"][m_fieldName]["operator"] = matchOperator;
}



MatchAllQuery::MatchAllQuery() : Query(Json::Value(Json::objectValue))
{
    m_query["match_all"] = Json::Value(Json::objectValue);
}




QueryString::QueryString(std::string query) : Query(Json::Value(Json::objectValue))
{
    m_query[m_name]["query"] = query;
}
// TODO: This code is way too repetitive.
QueryString::QueryString(std::string query, std::vector<std::string> fields) : Query(Json::Value(Json::objectValue))
{
    m_query[m_name]["query"] = query;
    if (fields.size() > 0) {
        m_query[m_name]["fields"] = Json::Value(Json::arrayValue);
        for (std::string itr : fields) {
            m_query[m_name]["fields"].append(itr);
        }
    }
}

QueryString::QueryString(std::string query, std::vector<std::string> fields, std::string analyzer) : Query(Json::Value(Json::objectValue))
{
    m_query[m_name]["query"] = query;
    if (fields.size() > 0) {
        m_query[m_name]["fields"] = Json::Value(Json::arrayValue);
        for (std::string itr : fields) {
            m_query[m_name]["fields"].append(itr);
        }
    }
    m_query[m_name]["analyzer"] = analyzer;
}



