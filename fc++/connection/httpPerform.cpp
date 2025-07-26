
#include <connection/httpPerform.hpp>
#include <common/certificades.hpp>
#include <connection/request_parser.hpp>


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

void Connection::start_stream()
{
    stream = std::make_shared<ssl::stream<beast::tcp_stream>>(net::make_strand(ioc),ctx);
}

Connection::Connection(std::string  &host_, std::string &port_) : 
    host(host_), port(port_), resolver(net::make_strand(ioc)), version(11){ load_root_certificates(ctx); start_stream(); }; //THE RESET_STREAM IS FOR START THE STREAM

Connection::~Connection(){std::cout << "[Connection] destruido correctamente\n";};


//SETTERS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//THIS MUST BE CALLED AFTER EVERY REQUEST, ON SHUTDOWN
void Connection::reset_stream()
{
    if (stream) {
        beast::get_lowest_layer(*stream).close(); // Ensure the socket is closed
        stream.reset(); // Release the stream
    }
    stream = std::make_shared<ssl::stream<beast::tcp_stream>>(net::make_strand(ioc),ctx);
    req = {};
    buffer.clear();
    buffer.consume(buffer.size());
    buffer.shrink_to_fit();
    res.clear();
    res.body().clear();
}

//THIS ON EVERY EXEPTION, ERROR.
void Connection::cancel_operation()
{
    resolver.cancel();
    if (stream) {
        beast::get_lowest_layer(*stream).cancel();
    }
    reset_stream();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//METHODS


//SIMPLE GET
void Connection::simple_GET(std::string &target)
{
    std::cout << "simple_GET\n";

    //Set SNI hostname
    if(!SSL_set_tlsext_host_name(stream->native_handle(), host.c_str()))
    {
        beast::error_code ec(static_cast<int> (::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << std::endl;
        
        return;
    }
            
    stream->set_verify_callback(ssl::host_name_verification(host)); //This set the expected hostname (doamain).

    //This set the GET request message

    req.version(version);
    req.method(http::verb::get);
    req.target(target);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            
    //Look up at the domain name
    resolver.async_resolve(host, port, beast::bind_front_handler(&Connection::on_resolve, shared_from_this()));
    
    ioc.restart();
    ioc.run();
}



//LOGIN
void Connection::login(std::string &userName, std::string &userPassword, std::string &target)
{
    if(!SSL_set_tlsext_host_name(stream->native_handle(), host.c_str()))
    {
        beast::error_code ec(static_cast<int> (::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << std::endl;
        
        return;
    }
            
    stream->set_verify_callback(ssl::host_name_verification(host)); //This set the expected hostname (doamain).

    req.version(version);
    req.method(http::verb::post);
    req.set(http::field::host, host);

    req.set(http::field::content_type, "application/json");

    req.target(target);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    req.body() = Parse_to::login(userName, userPassword);

    req.prepare_payload();
            
    //Look up at the domain name
    resolver.async_resolve(host, port, beast::bind_front_handler(&Connection::on_resolve, shared_from_this()));
    ioc.restart();
    ioc.run();
}



//REFRESH JWT
void Connection::JWT_refresh(std::string &cookieId, std::string &target)//THIS REQUEST DO NOT RETURN A VALID JWT OBJECT, IT RETURNS A STRING WITH ""
{
    if(!SSL_set_tlsext_host_name(stream->native_handle(), host.c_str()))
    {
        beast::error_code ec(static_cast<int> (::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << std::endl;
        
        return;
    }
            
    stream->set_verify_callback(ssl::host_name_verification(host)); //This set the expected hostname (doamain).
    req.version(version);
    req.method(http::verb::post);
    req.set(http::field::host, host);

    req.set(http::field::content_type, "application/json");

    req.target(target);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    req.body() = Parse_to::JWT_refresh(cookieId);

    req.prepare_payload();
            
    //Look up at the domain name
    resolver.async_resolve(host, port, beast::bind_front_handler(&Connection::on_resolve, shared_from_this()));
    ioc.restart();
    ioc.run();
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BOOST BEAST LOGIC
void Connection::on_resolve(beast::error_code ec, tcp::resolver::results_type result)
{
        if(ec)
    {
        show_fail(ec, "resolve");
        cancel_operation();
        
        return; 
    };

    //set a time out.
    beast::get_lowest_layer(*stream).expires_after(std::chrono::seconds(10));

    //make the connection on the cloudflare IP address.
    beast::get_lowest_layer(*stream).async_connect(result, beast::bind_front_handler(&Connection::on_connect, shared_from_this()));
}

void Connection::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
    if(ec)
    {
        show_fail(ec, "on_connect");
        cancel_operation();
        
        return;
    }
    //Perform de handshake
    stream->async_handshake(ssl::stream_base::client, beast::bind_front_handler(&Connection::on_handshake, shared_from_this()));
}

void Connection::on_handshake(beast::error_code ec)
{
    if(ec)
    {
        show_fail(ec, "handshake");
        cancel_operation();
        
        return; 
    }

    beast::get_lowest_layer(*stream).expires_after(std::chrono::seconds(15));

    // This send the http resquest to the server (if the handshyake was succes)
    http::async_write(*stream, req, beast::bind_front_handler(&Connection::on_write, shared_from_this())); 
}

void Connection::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec)
    {
        show_fail(ec, "write");
        cancel_operation();
        
        return; 
    }
    
    //Receive the response from the server (host)
    http::async_read(*stream, buffer, res, beast::bind_front_handler(&Connection::on_read, shared_from_this()));
}

void Connection::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if(ec)
    {
        show_fail(ec, "read");
        cancel_operation();
        
        return;
    }


    std::cout << "RESPONSE" << res.body() << " TARGET " << req.target() << std::endl;

    save_controller.target_discrimination_save(req.target(), res.body());
    
    beast::get_lowest_layer(*stream).expires_after(std::chrono::seconds(15));
    //Gracefully close the operation
    stream->async_shutdown(beast::bind_front_handler(&Connection::on_shutdown, shared_from_this()));

}

void Connection::on_shutdown(beast::error_code ec)
{
    std::cout << "here on shut\n";
    if(ec != net::ssl::error::stream_truncated)
    {
        cancel_operation();
        return show_fail(ec, "shutdown");
    }
    reset_stream();
}   
