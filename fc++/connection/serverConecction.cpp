#include "common/certificades.hpp"
#include "connection/httpPerform.hpp"
#include "connection/serverConecction.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>


server_connection::server_connection(std::string &host_, std::string &port_) : host(host_), port(port_), response_json("")
{
};

server_connection::~server_connection(){};


void server_connection::set_target(const char* target_)
{
    server_connection::target = target_; //Must be reaset everyTime you make a GET request.
};

std::string server_connection::get_response_json()
{
    return response_json;
};

void server_connection::perform_simple_GET()
{
    //mtx.lock();
    auto make = std::make_shared<simple_GET>(host, port, target, response_json); 
    make->run();
    cout << "performed\n";
    //mtx.unlock();
    return;
}




std::string server_connection::login(std::string userName, std::string password)
{
    mtx.lock();
    auto make = std::make_shared<simple_GET>(host, port, target, response_json); 
    make->run();
    cout << "performed\n";
    mtx.unlock();
    return "gola";
}



