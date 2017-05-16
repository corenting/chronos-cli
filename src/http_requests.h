#pragma once
#include <string>
#include <vector>
#include <cpr/cpr.h>

class HttpRequest {

public:
    static cpr::Response MakeRequest(std::string url);
};
