#ifndef MEMORY_DATABASE_INCLUDED
#define MEMORY_DATABASE_INCLUDED

#include "database.hpp"

#include <map>

namespace shortener {

class MemoryDatabase : public Database
{
public:
    MemoryDatabase() = default;

    void insert(std::string_view tag, std::string_view url) override;
    std::optional<std::string> lookup(std::string_view tag) const override;
private:
    std::map<std::string, std::string, std::less<>> database_;
};

}

#endif
