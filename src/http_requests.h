#pragma once
#include <string>
#include <vector>

class HttpRequest {

public:
    struct HttpResponse {
        int responseCode;
        std::vector<std::string> headers;
        std::string body;
        bool error;
        std::string errorMsg;
    };
    static HttpRequest::HttpResponse MakeRequest(std::string url, std::string api_token);
};
