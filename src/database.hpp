#ifndef DATABASE_INCLUDED
#define DATABASE_INCLUDED

#include <optional>
#include <string>
#include <string_view>

namespace shortener {

class Database
{
public:
    virtual ~Database() = default;

    virtual void insert(std::string_view tag, std::string_view url) = 0;
    virtual std::optional<std::string> lookup(std::string_view tag) const = 0;
};

}

#endif
