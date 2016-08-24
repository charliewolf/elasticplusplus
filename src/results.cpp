#include "results.h"
#include <iostream>

Results::Results(Json::Value body)
{
    m_body = body;

    for (auto itr : m_body["hits"]["hits"]) {
        m_hits.push_back(Result(itr));
    }
}

int Results::count()
{
    return m_body["hits"]["total"].asUInt();
}

Json::Value Results::raw(){
    return m_body;
}

std::vector<Result> Results::hits()
{
    return m_hits;
}

Result::Result(const Json::Value body)
{
    m_body = body;
}

std::string Result::doc_type()
{
    return m_body["_type"].asString();
}

std::string Result::index()
{
    return m_body["_index"].asString();
}

std::string Result::id()
{
    return m_body["_id"].asString();
}

Json::Value Result::source()
{
    return m_body["_source"];
}
float Result::score()
{
    return m_body["score"].asFloat();
}
