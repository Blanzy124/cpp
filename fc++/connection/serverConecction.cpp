#include "common/certificades.hpp"
#include "connection/httpPerform.hpp"
#include "connection/serverConecction.hpp"
#include "connection/targets.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>


server_connection::server_connection() : host("blanzynetwork.org"), port("8443"), response_json(""), perform(std::make_shared<Connection>(host, port, response_json))
{
};

server_connection::~server_connection(){};

std::string server_connection::get_response_json()
{
    return response_json;
};

void server_connection::perform_simple_GET()
{
    perform->simple_GET(target_to.wellcome);
}




std::string server_connection::login(std::string userName, std::string password)
{
    mtx.lock();
    auto make = std::make_shared<Connection>(host, port, response_json); 
    make->simple_GET("/");
    cout << "performed\n";
    mtx.unlock();
    return "gola";
}



