#include "certificades.hpp"
#include "httpPerform.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
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
  const char* &host;
  const char* &port;

};