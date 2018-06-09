#include "shortener.hpp"
#include "database.hpp"

namespace shortener {

Shortener::Shortener(Database& database, std::function<std::string ()>&& random_str)
    : database_(database)
    , random_str_(std::move(random_str))
{
}

std::string Shortener::shorten(std::string_view url)
{
    auto tag = random_str_();
    database_.insert(tag, url);
    return tag;
}

std::optional<std::string> Shortener::lookup(std::string_view tag)
{
    return database_.lookup(tag);
}

}
