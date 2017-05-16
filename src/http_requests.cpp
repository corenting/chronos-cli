#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <cpr/cpr.h>
#include <sstream>

#include "http_requests.h"
#include "api_token.h"

using boost::asio::ip::tcp;

cpr::Response HttpRequest::MakeRequest(std::string path) {
    // URL
    std::stringstream url_stream;
    url_stream << "http://v2.webservices.chronos.epita.net/api/v2/" << path;

    // Make request
    return cpr::Get(cpr::Url{url_stream.str()}, cpr::Header{{"Auth-Token", API_TOKEN}});
}
