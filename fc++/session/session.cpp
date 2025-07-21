#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>

#include <session/session.hpp>





using namespace std;
using std::cout;

User_session::User_session(){};
User_session::~User_session(){};

//SETTERS
void User_session::set_userName(std::string userName_)
{
    userName = userName_;
}

void User_session::set_cookieId(std::string cookieId_)
{
    cookieId = cookieId_;
}

void User_session::set_JWT(std::string JWT_)
{
    JWT = JWT_;
}

//GETTERS
std::string User_session::get_userName()
{
    return userName;
}

std::string User_session::get_cookieId()
{
    return cookieId;
}

std::string User_session::get_JWT()
{
    return JWT;
}


