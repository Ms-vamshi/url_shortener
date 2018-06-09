#ifndef CROW_SERVER_INCLUDED
#define CROW_SERVER_INCLUDED

#include "crow.h"
#include "server.hpp"

namespace shortener {

class Shortener;

class CrowServer : public Server
{
public:
    CrowServer(Shortener& shortener);

    void setup() override;
    void run() override;

private:
    Shortener& shortener_;
    crow::SimpleApp app;

    crow::response handle_front_page(const crow::request& request);
    crow::response handle_redirect(std::string_view tag);
};

}

#endif

