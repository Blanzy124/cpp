#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

#include <connection/socketPerform.hpp>
#include <connection/targets.hpp>

namespace beast = boost::beast;         
namespace http = beast::http;           
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
using tcp = net::ip::tcp;

Web_socket::Web_socket(std::string &host_, std::string &port_) : host(host_),  port(port_) {};

Web_socket::~Web_socket(){};

void Web_socket::socket_connection(std::string &JWT, std::string &target)
{
	try
	{
		auto const results = resolver.resolve(host, port);
		
		auto ep = net::connect(ws.next_layer(), results);
	
		http::fields headers;
		headers.set(http::field::authorization, "Bearer " + JWT);
		ws.set_option(websocket::stream_base::decorator(
			[](websocket::request_type& req)
			{
				req.set(http::field::user_agent,
					std::string(BOOST_BEAST_VERSION_STRING) +
						" websocket-client-coro");
			}));
	
		ws.handshake(host, Target_to::socket_test);

		ws.write(net::buffer(std::string("hola desde cpp")));

		beast::flat_buffer buffer;

		ws.read(buffer);

		ws.close(websocket::close_code::normal);

		std::cout << beast::make_printable(buffer.data()) << std::endl;
		
	}
	catch(std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
        return;
	}
	
}





