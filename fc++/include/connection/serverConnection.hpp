#ifndef SERVER_CONNECTION_HPP

#include "connection/httpPerform.hpp"
#include "connection/targets.hpp"
#include <session/session.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <mutex>

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
  ~server_connection(user);
  void set_secure(bool secure, ssl::context &ctx);
  
  //GETTERS
  std::string get_response_json();
  
  //METHODS
  void perform_simple_GET();

  std::string login(std::string userName, std::string userPassword, std::string &cookieId);
  


};
#endif