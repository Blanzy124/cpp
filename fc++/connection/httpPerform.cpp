//#include "certificades.hpp"
#include "connection/httpPerform.hpp"
#include "common/certificades.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
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

inline void show_fail(beast::error_code &ec, const char* what)
{
    std::cout << ec.message() << "  " << what << std::endl;
}

simple_GET::simple_GET(std::string  &host_, std::string &port_, std::string  &target_, std::string &response_json_) : 
    host(host_), port(port_), target(target_), response_json(response_json_), resolver(net::make_strand(ioc)), stream(net::make_strand(ioc), ctx), version(11){ cout << "simple_GET created\n"; load_root_certificates(ctx); };

simple_GET::~simple_GET(){std::cout << "[simple_GET] destruido correctamente\n";};


//SETTERS
void simple_GET::set_target(const char* &target_)
{
    target = target_;
    return;
}

//METHODS

void simple_GET::procces_restart()
{
    ioc.restart();
};



void simple_GET::run()
{
    cout << "run\n";

    //Set SNI hostname
    if(!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
    {
        beast::error_code ec(static_cast<int> (::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << std::endl;
        simple_GET::procces_restart();
        return;
    }
            
    stream.set_verify_callback(ssl::host_name_verification(host)); //This set the expected hostname (doamain).

    //This set the GET request message
    req.version(version);
    req.method(http::verb::get);
    req.target(target);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            
    //Look up at the domain name
    ioc.run();
    resolver.async_resolve(host, port, beast::bind_front_handler(&simple_GET::on_resolve, shared_from_this()));


}

void simple_GET::on_resolve(beast::error_code ec, tcp::resolver::results_type result)
{
    cout << "resolve\n";
        if(ec)
    {
        show_fail(ec, "resolve");
        beast::get_lowest_layer(stream).close();
        simple_GET::procces_restart();
        return; 
    };

    //set a time out.
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(10));

    //make the connection on the cloudflare IP address.
    beast::get_lowest_layer(stream).async_connect(result, beast::bind_front_handler(&simple_GET::on_connect, shared_from_this()));
}

void simple_GET::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
    if(ec)
    {
        show_fail(ec, "on_connect");
        beast::get_lowest_layer(stream).close();
        simple_GET::procces_restart();
        return;
    }
    //Perform de handshake
    stream.async_handshake(ssl::stream_base::client, beast::bind_front_handler(&simple_GET::on_handshake, shared_from_this()));
}

void simple_GET::on_handshake(beast::error_code ec)
{
    if(ec)
    {
        show_fail(ec, "handshake");
        beast::get_lowest_layer(stream).close();
        simple_GET::procces_restart();
        return; 
    }

    beast::get_lowest_layer(stream ).expires_after(std::chrono::seconds(15));

    // This send the http resquest to the server (if the handshyake was succes)
    http::async_write(stream, req, beast::bind_front_handler(&simple_GET::on_write, shared_from_this())); 
}

void simple_GET::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec)
    {
        show_fail(ec, "write");
        beast::get_lowest_layer(stream).close();
        simple_GET::procces_restart();
        return; 
    }
    
    //Receive the response from the server (host)
    http::async_read(stream, buffer, res, beast::bind_front_handler(&simple_GET::on_read, shared_from_this()));
}

void simple_GET::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec)
    {
        show_fail(ec, "read");
        beast::get_lowest_layer(stream).close();
        simple_GET::procces_restart();
        return;
    }
    response_json = res.body();
    //std::cout << "RESPONSE" << res << std::endl;
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(15));
    buffer.clear();
    //Gracefully close the operation
    stream.async_shutdown(beast::bind_front_handler(&simple_GET::on_shutdown, shared_from_this()));

}

void simple_GET::on_shutdown(beast::error_code ec)
{
    std::cout << "here on shut\n";
    if(ec != net::ssl::error::stream_truncated)
    {
        return show_fail(ec, "shutdown");
        simple_GET::procces_restart();
    }
    beast::get_lowest_layer(stream).close();
    simple_GET::procces_restart();
}   
