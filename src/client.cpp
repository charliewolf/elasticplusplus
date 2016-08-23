#include <cpr/cpr.h>

#include "client.h"

ESClient::ESClient(std::string url)
{
    m_url = url;

}

Results ESClient::search(std::string index, std::string doc_type, Search body)
{
    search(index, doc_type, body.toJson());
}
Results ESClient::search(std::string index, std::string doc_type, Json::Value body)
{
    Json::FastWriter writer;
    std::string rawBody = writer.write(body);
    cpr::Url url;
    if (index.empty() && doc_type.empty()) {
        url = cpr::Url{m_url + "/_search"};
    } else if (doc_type.empty()) {
        url = cpr::Url{m_url + "/" + index + "/_search"};
    } else {
        url = cpr::Url{m_url + "/" + index + "/" + doc_type + "/_search"};
    }
    cpr::Response request = cpr::Post(url, cpr::Body{rawBody}, cpr::Header{{"Content-type", "application/json"}});
    if (request.status_code >= 400) {
        throw SearchException(request.status_code, request.text);
    } else {
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(request.text, root)) {
            throw SearchException(-1, request.text);
        } else {
            return Results(root);
        }
    }
}
Results ESClient::search(Search body)
{
    return search("", "", body);
}
Results ESClient::search(std::string index, Search body)
{
    return search(index, "", body);
}
void ESClient::create(std::string index, std::string doc_type, Json::Value body){
    create(index, doc_type, "", body);
}
void ESClient::create(std::string index, std::string doc_type, std::string id, Json::Value body){
    Json::FastWriter writer;
    std::string rawBody = writer.write(body);
    cpr::Url url;
    if (id.empty()) {
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/_create"};
    } else{
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/" + id + "/_create"};
    }
    cpr::Response request = cpr::Put(url, cpr::Body{rawBody}, cpr::Header{{"Content-type", "application/json"}});
    if (request.status_code >= 400) {
        throw SearchException(request.status_code, request.text);
    }
}
void ESClient::deleteDocument(std::string index, std::string doc_type, std::string id)
{
    deleteDocument(index, doc_type, id, "");
}

void ESClient::deleteDocument(std::string index, std::string doc_type, std::string id, std::string routing)
{
    cpr::Url url;
    if (routing.empty()) {
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/" + id };
    } else{
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/" + id + "?routing=" + routing};
    }
    cpr::Response request = cpr::Delete(url);
    if (request.status_code >= 400) {
        throw SearchException(request.status_code, request.text);
    }
}
Result ESClient::get(std::string index, std::string doc_type, std::string id)
{
   return get(index, doc_type, id, "");
}
Result ESClient::get(std::string index, std::string doc_type, std::string id, std::string routing)
{
    cpr::Url url;
    if (routing.empty()) {
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/" + id };
    } else{
        url = cpr::Url{m_url + "/" + index + "/" + doc_type  + "/" + id + "?routing=" + routing};
    }
    cpr::Response request = cpr::Get(url);
    if (request.status_code >= 400) {
        throw SearchException(request.status_code, request.text);
    }
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(request.text, root)) {
        throw SearchException(-1, request.text);
    } else {
        return Result(root);
    }
}
