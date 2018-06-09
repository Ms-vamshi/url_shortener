#ifndef SHORTENER_INCLUDED
#define SHORTENER_INCLUDED

#include <functional>
#include <optional>
#include <string>

namespace shortener {

class Database;

class Shortener
{
public:
    Shortener(Database& database, std::function<std::string ()>&& random_str);

    std::string shorten(std::string_view url);
    std::optional<std::string> lookup(std::string_view tag);

private:
    Database& database_;
    std::function<std::string ()> random_str_;
};

}

#endif

