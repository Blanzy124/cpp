#include "certificades.hpp"
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
    std::cout << ec.message() << "  " << what << std::endl;}


class simple_GET : public std::enable_shared_from_this<simple_GET>{
    protected:
        //this is the resonces that comes from server
        std::string &response_json;
        //request specs
        const char* &host;
        const char* &port;
        int &version;
        //Target must be set in each request
        const char* &target;
        //performcHTTP GET
        http::request<http::empty_body> req;
        http::response<http::string_body> res;
        tcp::resolver resolver;
        ssl::stream<beast::tcp_stream> stream;
        beast::flat_buffer buffer;
        
        
        public:
        //Constructor and destructor
        explicit simple_GET(const char* &host_, const char* &port_, const char* &target_, int &version_, net::any_io_executor ex, ssl::context &ctx, std::string &response_json_) : host(host_), port(port_), target(target_), version(version_), resolver(ex), stream(ex, ctx), response_json(response_json_){ cout << "hpptPerform build\n";};
        ~simple_GET(){std::cout << "[simple_GET] destruido correctamente\n";};
        
        //SETTERS
        void set_target(const char* &target_)
        {
            simple_GET::target = target_;
        }

        //GETTERS

        //METHODS
        void run()
        {
            //cout<< &response_save <<  "from run RS\n";

            //Set SNI hostname
            if(!SSL_set_tlsext_host_name(stream.native_handle(), host))
            {
                beast::error_code ec(static_cast<int> (::ERR_get_error()), net::error::get_ssl_category());
                std::cerr << ec.message() << std::endl;
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
            resolver.async_resolve(host, port, beast::bind_front_handler(&simple_GET::on_resolve, shared_from_this()));

        }

        void on_resolve(beast::error_code ec, tcp::resolver::results_type result)
        {
            if(ec)
            {
                show_fail(ec, "resolve");
                beast::get_lowest_layer(stream).close();
                return; 
            };

            //set a time out.
            beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(10));

            //make the connection on the cloudflare IP address.
            beast::get_lowest_layer(stream).async_connect(result, beast::bind_front_handler(&simple_GET::on_connect, shared_from_this()));

        }

        void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
        {
            if(ec)
            {
                show_fail(ec, "on_connect");
                beast::get_lowest_layer(stream).close();
                return;
            }
            //Perform de handshake
            stream.async_handshake(ssl::stream_base::client, beast::bind_front_handler(&simple_GET::on_handshake, shared_from_this()));

        }

        void on_handshake(beast::error_code ec)
        {
            if(ec)
            {
                show_fail(ec, "handshake");
                beast::get_lowest_layer(stream).close();
                return; 
            }

            beast::get_lowest_layer(stream ).expires_after(std::chrono::seconds(15));

            // This send the http resquest to the server (if the handshyake was succes)
            http::async_write(stream, req, beast::bind_front_handler(&simple_GET::on_write, shared_from_this())); 
        }

        void on_write(beast::error_code ec, std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if(ec)
            {
                show_fail(ec, "write");
                beast::get_lowest_layer(stream).close();
                return; 
            }
            
            //Receive the response from the server (host)
            http::async_read(stream, buffer, res, beast::bind_front_handler(&simple_GET::on_read, shared_from_this()));


        }

        void on_read(beast::error_code ec, std::size_t bytes_transferred)
        {

            boost::ignore_unused(bytes_transferred);

            if(ec)
            {
                show_fail(ec, "read");
                beast::get_lowest_layer(stream).close();
                return;
            }

            response_json = res.body();

            //std::cout << "RESPONSE" << res << std::endl;

            beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(15));

            buffer.clear();
            cout << "buffer " << sizeof(buffer) << "  " << sizeof(resolver) << "  " << sizeof(stream) << std::endl;

            //Gracefully close the operation
            stream.async_shutdown(beast::bind_front_handler(&simple_GET::on_shutdown, shared_from_this()));
        
        }

        void on_shutdown(beast::error_code ec)
        {
            std::cout << "here on shut\n";

            if(ec != net::ssl::error::stream_truncated)
            {
                return show_fail(ec, "shutdown");
            }
            beast::get_lowest_layer(stream).close();
        }   
    };
