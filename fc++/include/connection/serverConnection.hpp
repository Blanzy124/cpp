#ifndef SERVER_CONNECTION_HPP

#include "connection/httpPerform.hpp"
#include "connection/targets.hpp"
#include <connection/socketPerform.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <mutex>

inline std::mutex mtx;

class server_connection{
 protected:

 std::shared_ptr<Connection> perform;

 std::shared_ptr<Web_socket> socket_perform;
 
 public:
 
  explicit server_connection();
  ~server_connection();
  //GETTERS

  
  //METHODS
 
		//HTTPS
  void perform_simple_GET();

  void login(std::string userName, std::string &userPassword);

  void JWT_refresh(std::string cookieId);


		//WEB SOCKET
  void simple_web_socket(std::string from, std::string to, std::string JWT);
};
#endif