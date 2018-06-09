#include "database.hpp"
#include "memory_database.hpp"

#include <algorithm>

namespace shortener {

void MemoryDatabase::insert(std::string_view tag, std::string_view url)
{
    database_.emplace(tag, url);
}

std::optional<std::string> MemoryDatabase::lookup(std::string_view tag) const
{
    if (const auto iter = database_.find(tag); iter != database_.end()) {
        return std::make_optional(iter->second);
    }
    return std::nullopt;
}

}
