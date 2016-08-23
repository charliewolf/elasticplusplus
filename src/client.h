#ifndef ESCLIENT_H
#define ESCLIENT_H

#include <exception>
#include <iostream>
#include "search.h"
#include "results.h"

class SearchException : public std::exception
{
private:
    int m_status;
    std::string m_body;
public:
    SearchException(const int status_code, const std::string error) : std::exception()
    {
        m_status = status_code;
        m_body = error;
    }
    virtual const char * what() const throw ()
    {
        return "Search Exception!";
    }
    int status()
    {
        return m_status;
    }
    std::string body()
    {
        return m_body;
    }
};


class ESClient
{
public:
    ESClient(std::string url);
    Results search(std::string index, std::string doc_type, Json::Value body);
    Results search(std::string index, std::string doc_type, Search body);
    Results search(std::string index, Search body);
    Results search(Search body);
    void create(std::string index, std::string doc_type, Json::Value body);
    void create(std::string index, std::string doc_type, std::string id, Json::Value body);
    void deleteDocument(std::string index, std::string doc_type, std::string id);
    void deleteDocument(std::string index, std::string doc_type, std::string id, std::string routing);
    Result get(std::string index, std::string doc_type, std::string id);
    Result get(std::string index, std::string doc_type, std::string id, std::string routing);


private:
    std::string m_url;
};

#endif // ESCLIENT_H
