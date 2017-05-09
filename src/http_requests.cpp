#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

#include "http_requests.h"
#include "api_token.h"

using boost::asio::ip::tcp;

HttpRequest::HttpResponse HttpRequest::MakeRequest(std::string path) {

    try {
        // Split the url (host and path)
        std::string url_host = "v2.webservices.chronos.epita.net";
        std::string url_path = "/api/v2/" + path;

        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(url_host, "http");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << url_path << " HTTP/1.0\r\n";
        request_stream << "Host: " << url_host << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Auth-Token:" << API_TOKEN << "\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Create the response structure
        HttpResponse httpResponse;

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        response_stream >> httpResponse.responseCode;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            httpResponse.error = true;
            httpResponse.errorMsg = "Invalid response";
            return httpResponse;
        }
        if (httpResponse.responseCode != 200) {
            httpResponse.errorMsg = "Response returned with status code " + std::to_string(httpResponse.responseCode);
            httpResponse.error = true;
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            httpResponse.headers.emplace_back(header);

        // Write whatever content we already have to output.
        std::stringstream ss;
        if (response.size() > 0) {
            ss << &response;
        }

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error))
            ss << &response;
        if (error != boost::asio::error::eof) {
            httpResponse.error = true;
            httpResponse.errorMsg = "System error :" + error.message();
        }
        httpResponse.error = httpResponse.responseCode != 200;
        httpResponse.body = ss.str();
        return httpResponse;
    }
    catch(int e)
    {
        HttpResponse httpResponse;
        httpResponse.error = true;
        httpResponse.errorMsg = "Exception  while downloading";
        return httpResponse;
    }
}
