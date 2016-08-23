#include "sort.h"


const char *sort_order[] = {"asc", "desc"};
const char *sort_mode[] = {"min", "max", "sum", "avg", "median"};

Sort::Sort(const std::string fieldName)
{
    m_sort = Json::Value(fieldName);
}

Sort::Sort(const std::string fieldName, SortOrder order)
{
    m_sort = Json::Value(Json::objectValue);
    m_sort[fieldName] = sort_order[order];
}

Sort::Sort(const std::string fieldName, SortOrder order, SortMode mode)
{
    m_sort = Json::Value(Json::objectValue);
    m_sort[fieldName] = Json::Value(Json::objectValue);
    m_sort[fieldName]["order"] = sort_order[order];
    m_sort[fieldName]["mode"] = sort_mode[mode];

}

Json::Value Sort::toJson() const
{
    return m_sort;
}
