#ifndef SERVER_CONNECTION_HPP

#include "httpPerform.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <mutex>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

inline std::mutex mtx;

class server_connection{
 protected:
 std::string &host;
 std::string &port;
 std::string target;
 std::string response_json;
 
 
 public:
  //static std::string response_json;
 
  explicit server_connection(std::string &host_, std::string &port_);
  ~server_connection();
  void set_secure(bool secure, ssl::context &ctx);
  void set_target(const char* target_);
  
  //GETTERS
  std::string get_response_json();
  
  //METHODS
  void perform_simple_GET();
  std::string login(std::string userName, std::string password);
  


};
#endif