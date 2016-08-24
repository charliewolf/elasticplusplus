#ifndef RESULTS_H
#define RESULTS_H

#include "json/json.h"


class Result
{
public:
    explicit Result(const Json::Value body);
    float score();
    Json::Value source();
    std::string index();
    std::string doc_type();
    std::string id();
private:
    Json::Value m_body;
};

class Results
{
public:
    Results(const Json::Value body);
    int count();
    std::vector<Result> hits();
    Json::Value raw();
private:
    Json::Value m_body;
    std::vector<Result> m_hits;
};


#endif // RESULTS_H
