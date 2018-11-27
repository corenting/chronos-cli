#pragma once

#include <string>
#include <vector>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/filestream.h>

using namespace web::http;
using namespace web::http::client;
using namespace Concurrency::streams;

class HttpRequest {

public:
    static http_response MakeRequest(std::string url);
};
