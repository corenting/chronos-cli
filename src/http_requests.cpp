#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <sstream>

#include "http_requests.h"
#include "api_token.h"

http_response HttpRequest::MakeRequest(std::string path) {
    // Make request
    http_client httpClient("http://v2.webservices.chronos.epita.net/api/v2/");

    // Simple GET request
    http_request req(methods::GET);
    req.set_request_uri(path);
    req.headers().add(U("Auth-Token"), API_TOKEN);
    http_response httpResponse = httpClient.request(req).get();

    return httpResponse;
}
