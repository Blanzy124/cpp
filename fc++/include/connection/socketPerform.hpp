#ifndef WEB_SOCKET
#define WEB_SOCKET
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iostream>

namespace beast = boost::beast;         
namespace http = beast::http;           
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
using tcp = net::ip::tcp;

class Web_socket{
 protected:
	std::string &host;
	std::string &port;

	net::io_context ioc;	
	ssl::context ctx{ssl::context::tls_client};

	tcp::resolver resolver{ioc};	
	std::shared_ptr<websocket::stream<beast::ssl_stream<tcp::socket>>> ws;

 public:
 	explicit Web_socket(std::string &host, std::string &port);
	~Web_socket();

  //METHODS
	void socket_connection(std::string &from, std::string &to, std::string &JWT, std::string &target);

	void start_ws();
	void reset_socket();


};

#endif