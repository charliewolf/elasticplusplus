#ifndef ELASTICPLUSPLUS_SORT_H
#define ELASTICPLUSPLUS_SORT_H

#include <json/json.h>

enum SortMode { min, max, sum, avg, median };
enum SortOrder { asc, desc };

class Sort
{
public:
    explicit Sort(const std::string fieldName);
    explicit Sort(const std::string fieldName, SortOrder order);
    explicit Sort(const std::string fieldName, SortOrder order, SortMode mode);
    Json::Value toJson() const;

private:
    Json::Value m_sort;

};


#endif
