#include <cpr/cpr.h>

#include "client.h"

ESClient::ESClient(std::string url)
{
    m_url = url;

}

Results ESClient::search(std::string index, std::string doc_type, Search body)
{
    Json::FastWriter writer;
    std::string rawBody = writer.write(body.toJson());
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
    return search("", "", body);
}
