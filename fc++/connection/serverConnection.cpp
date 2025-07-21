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


server_connection::server_connection() : response_json(""), perform(std::make_shared<Connection>(host, port, response_json))
{
};

server_connection::~server_connection(){};

std::string server_connection::get_response_json()
{
    return response_json;
};

void server_connection::perform_simple_GET()
{
    std::cout << &perform << "\n";
    perform->simple_GET(target_to.wellcome);
}




std::string server_connection::login(std::string userName, std::string userPassword, std::string &cookieId)
{
    perform->login(userName, userPassword, target_to.loging, cookieId);
    return "gola";
}



