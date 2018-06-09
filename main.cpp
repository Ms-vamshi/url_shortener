#include "src/crow_server.hpp"
#include "src/memory_database.hpp"
#include "src/shortener.hpp"

#include <charconv>
#include <memory>
#include <random>

std::string base36(unsigned long long num)
{
    char buffer[sizeof "3W5E11264SG0G"]; // base36(2^64)
    memset(static_cast<void*>(buffer), 0, std::size(buffer));
    std::to_chars(std::begin(buffer), std::end(buffer), num, 36);
    return std::string(std::begin(buffer), std::end(buffer));
}

int main()
{
    auto seed = [] {
        std::random_device rand;
        return rand();
    }();

    auto random_str = [
        random_engine = std::default_random_engine(seed),
        random_int = std::uniform_int_distribution<unsigned long long>()
    ] () mutable {
        return base36(random_int(random_engine));
    };

    auto database = shortener::MemoryDatabase{};
    auto shortener = shortener::Shortener{database, std::move(random_str)};
    auto server = std::make_unique<shortener::CrowServer>(shortener);
    server->setup();
    server->run();

    return 0;
}
