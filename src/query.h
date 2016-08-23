#ifndef ELASTICPLUSPLUS_QUERY_H
#define ELASTICPLUS_QUERY_H

#include <json/json.h>


class Query
{
protected:
    Json::Value m_query;
    explicit Query(Json::Value value);
public:
    friend Query operator+(Query lhs, const Query& rhs) ;
    friend Query operator|(Query lhs, const Query& rhs) ;
    friend Query operator&(Query lhs, const Query& rhs) ;
    Json::Value toJson() const;
};

class BoolQuery : public Query
{
public:
    explicit BoolQuery();
    template<typename ... Types>
    void must(const Query query, Types ... rest)
    {
        addToList("must", query, rest...);
    };
    template<typename ... Types>
    void must_not(const Query query, Types ... rest)
    {
        addToList("must_not", query, rest...);
    };
    template<typename ... Types>
    void should(const Query query, Types ... rest)
    {
        addToList("should", query, rest...);
    };
    template<typename ... Types>
    void filter(const Query query, Types ... rest)
    {
        addToList("filter", query, rest...);
    };
private:
    void must()
    {
    }
    void should()
    {
    }
    void filter()
    {
    }
    void must_not()
    {
    }
    void addToList(std::string key) {}
    template<typename ... Types>
    void addToList(std::string key, const Query q, Types ... rest)
    {
        Json::Value query(q.toJson());
        m_query["bool"][key].append(query);
        addToList(key, rest...);
    }


};

class TermQuery : public Query
{
public:
    template<typename T>
    explicit TermQuery(std::string key, T value) : Query(Json::Value(Json::objectValue))
    {
        m_query["term"] = Json::Value(Json::objectValue);
        m_query["term"][key] = value;
    }
};
class MatchQuery : public Query
{
public:
    template<typename T>
    explicit MatchQuery(std::string key, T value) : Query(Json::Value(Json::objectValue))
    {
        m_query["match"] = Json::Value(Json::objectValue);
        m_query["match"][key] = Json::Value(Json::objectValue);
        m_query["match"][key]["query"] = value;
        m_fieldName = key;
    }
    void setOperator(std::string);
    explicit MatchQuery(std::string key, std::string value, std::string matchOperator);
private:
    std::string m_fieldName;
};
class MatchAllQuery : public Query
{
public:
    explicit MatchAllQuery();
};

class QueryString : public Query
{
public:
    explicit QueryString(std::string query);
    explicit QueryString(std::string query, std::vector<std::string> fields);
    explicit QueryString(std::string query, std::vector<std::string> fields, std::string analyzer);
private:
    std::string m_name = "query_string";
};

class SimpleQueryString : public QueryString
{
    using QueryString::QueryString;
private:
    std::string m_name = "simple_query_string";
};

#endif
