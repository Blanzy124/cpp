#include "common/certificades.hpp"
#include "connection/httpPerform.hpp"
#include "connection/serverConnection.hpp"
#include "connection/targets.hpp"
#include "session/session.hpp"
#include "config/config.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>


server_connection::server_connection() :  perform(std::make_shared<Connection>(host, port))
{
};

server_connection::~server_connection(){};

void server_connection::perform_simple_GET()
{
    std::cout << "perfrim_simple_GET\n";
    perform->simple_GET(Target_to::wellcome);
}




std::string server_connection::login(std::string &userName, std::string &userPassword)
{
    perform->login(userName, userPassword, Target_to::loging);
    return "gola";
}



