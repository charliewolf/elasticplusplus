# ElasticPlusPlus - A high level, type-safe ElasticSearch DSL for C++

## Example
```
#include "search.h"
#include "client.h"
#include <iostream>

int main(int argc, char *argv[])
{
    ESClient client("http://localhost:9200/");
    Search search(MatchQuery("name", "Charlie") + TermQuery("user_id", 11));
    auto results = client.search(search);
    for(auto result : results.hits()){
        std::cout << result.id();
    }
    return 0;
}
```


## Status
### Working
* Query types: bool, match, match_all, term, query_string, simple_query_string
* Sorting
* Pagination

### TODO
* Other query types (e.g. regex)
* Aggregations



