#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
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
	tcp::resolver resolver{ioc};	
	websocket::stream<tcp::socket> ws{ioc};

 public:
 	explicit Web_socket(std::string &host, std::string &port);
	~Web_socket();

  //METHODS
	void socket_connection(std::string &JWT, std::string &target);


};