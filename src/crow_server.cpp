#include "crow_server.hpp"
#include "shortener.hpp"

namespace {

constexpr auto front_page = 
R"(<!DOCTYPE html>
<html>
<body>

<h2>C++ URL shortener</h2>

<form action="/">
  URL:<br>
  <input type="text" name="url" value="https://">
  <input type="submit" value="Submit">
</form> 

</body>
</html>)";

}

namespace shortener {

CrowServer::CrowServer(Shortener& shortener)
    : shortener_(shortener)
{
}

void CrowServer::setup()
{
    CROW_ROUTE(app, "/")
        .name("frontpage")
        .methods("GET"_method)
    ([this] (const crow::request& request) {
         return handle_front_page(request);
    });

    CROW_ROUTE(app, "/<string>")
        .name("redirect")
        .methods("GET"_method)
    ([this] (std::string_view tag) {
         return handle_redirect(std::move(tag));
    });
}

void CrowServer::run()
{
    app.port(8080)
        // .multithreaded()
        .run();
}

crow::response CrowServer::handle_front_page(const crow::request& request)
{
    if (auto url = request.url_params.get("url"); url != nullptr) {
        try {
            constexpr auto root = "localhost:8080/";
            auto short_url = shortener_.shorten(url);
            return crow::response(200, "<a href=\"/" + short_url + "\">" + root + short_url + "</a>");
        } catch (const std::runtime_error&) {
            return crow::response(400);
        }
        return crow::response(500);
    }
    return crow::response(200, front_page);
}

crow::response CrowServer::handle_redirect(std::string_view tag)
{
    if (const auto url = shortener_.lookup(tag); url) {
        crow::response response(302);
        response.set_header("Location", *url);
        return response;
    }
    return crow::response(404);
}

}
