#ifndef SERVER_CONNECTION_HPP

#include "httpPerform.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>

#include "connection/targets.hpp"

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
 std::string response_json;
 std::shared_ptr<Connection> perform;

 //MAIN HEADER FILE WHERE ALL TARGETS ARE
 Targets_to target_to;
 
 
 public:
  //static std::string response_json;
 
  explicit server_connection();
  ~server_connection();
  void set_secure(bool secure, ssl::context &ctx);
  
  //GETTERS
  std::string get_response_json();
  
  //METHODS
  void perform_simple_GET();

  std::string login(std::string userName, std::string userPassword, std::string &cookieId);
  


};
#endif