#ifndef Connection_HPP
#define Connection_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>

#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

using std::cout;


inline void show_fail(beast::error_code &ec, const char* what);

class Connection : public std::enable_shared_from_this<Connection>{
    protected:
        //this is the resonces that comes from server
        std::string &response_json;

        //request specs
        std::string &host;
        std::string &port;

        //htto version
        int version;

        //IO CONTEXt
        net::io_context ioc;
        //CONTEXT
        ssl::context ctx{ssl::context::tlsv12_client};

        //Target must be set in each request
        //performcHTTP GET
        http::request<http::empty_body> req;
        http::response<http::string_body> res;
        tcp::resolver resolver;
        std::shared_ptr<ssl::stream<beast::tcp_stream>> stream;
        beast::flat_buffer buffer;
        

    public:
        //Constructor and destructor
        explicit Connection(std::string  &host_, std::string &port_, std::string &response_json_); //net::any_io_executor ex, ssl::context &ctx,
        ~Connection();

        //SETTERS

        //METHODS
        void procces_restart();
        void cancel_operation();

        void simple_GET(std::string &target);
        void login(std::string &userName, std::string &userPassword, std::string &target, std::string &cookieId);
        void reset_stream();

        void on_resolve(beast::error_code ec, tcp::resolver::results_type result);
        void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);
        void on_handshake(beast::error_code ec);
        void on_write(beast::error_code ec, std::size_t bytes_transferred);
        void on_read(beast::error_code ec, std::size_t bytes_transferred);
        void on_shutdown(beast::error_code ec);






};    

#endif

