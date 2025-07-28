#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iostream>

#include <common/certificades.hpp>
#include <connection/socketPerform.hpp>
#include <connection/targets.hpp>
#include <connection/request_parser.hpp>

namespace beast = boost::beast;         
namespace http = beast::http;           
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
using tcp = net::ip::tcp;

Web_socket::Web_socket(std::string &host_, std::string &port_) : host(host_),  port(port_) {
	ctx.set_verify_mode(ssl::verify_none); load_root_certificates(ctx); start_ws(); };

Web_socket::~Web_socket(){};

void Web_socket::start_ws()
{
	ws = std::make_shared<websocket::stream<beast::ssl_stream<tcp::socket>>>(ioc, ctx);
}

void Web_socket::reset_socket()
{
	if (ws->is_open()) {
    ws->close(websocket::close_code::normal);  // o .none si hubo error
	}
	ws = std::make_shared<websocket::stream<beast::ssl_stream<tcp::socket>>>(ioc, ctx);
	ioc.restart();
}


void Web_socket::socket_connection(std::string &from, std::string &to, std::string &JWT, std::string &target)
{
	try
	{
		reset_socket();

		auto const results = resolver.resolve(host, port);
		
		auto ep = net::connect(get_lowest_layer(*ws), results);
	
		//host += ':' + std::to_string(ep.port()); //BLANZYNETWORK DO NOT REQUIRE THE HOST HEAD WITH PORT (RFC 7230 SECTION 5.4)
		boost::system::error_code ec;
		ws->next_layer().handshake(ssl::stream_base::client, ec);

		if (ec) {
            std::cerr << "SSL Handshake failed: " << ec.message() << std::endl;
            return;
        }

		ws->set_option(websocket::stream_base::decorator(
			[&JWT](websocket::request_type& req)
			{
				req.set(http::field::user_agent,
					std::string(BOOST_BEAST_VERSION_STRING) +
					" websocket-client-coro");
					
					std::cout << req << "\n";
				}));
				
				std::string full_target = Target_to::socket_test + "?token=" + JWT;
		ws->handshake(host, full_target);

		std::string message_test = "hola desde cpp";

		ws->write(net::buffer(Parse_to::web_socket_simple_message(from, to, message_test)));

		beast::flat_buffer buffer;

		//while(true)
		//{
			ws->read(buffer);
	
			std::cout << beast::make_printable(buffer.data()) << std::endl;
	
			buffer.clear();
		//}

		ws->close(websocket::close_code::normal);

		
	}
	catch(std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
        return;
	}
	
}





