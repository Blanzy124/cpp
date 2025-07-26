#ifndef SERVER_CONNECTION_HPP

#include "connection/httpPerform.hpp"
#include "connection/targets.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <mutex>

inline std::mutex mtx;

class server_connection{
 protected:

 std::shared_ptr<Connection> perform;
 
 public:
 
  explicit server_connection();
  ~server_connection();
  //GETTERS

  
  //METHODS
  void perform_simple_GET();

  std::string login(std::string &userName, std::string &userPassword);
  


};
#endif