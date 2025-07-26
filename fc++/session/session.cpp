#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>

#include <session/session.hpp>


using namespace std;
using std::cout;

User_session::User_session(){};
User_session::~User_session(){};

std::string User_session::userName = "";
std::string User_session::cookieId = "";
std::string User_session::JWT = "";

std::string User_session::error_login = "";
std::string User_session::error_cookieId = "";
std::string User_session::error_JWT = "";

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


void User_session::error_set_cookieId(std::string err)
{
    error_cookieId = err;
}

void User_session::error_set_JWT(std::string err)
{
    error_JWT = err;
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


std::string User_session::error_get_cookieId()
{
    return error_cookieId;
}

std::string User_session::error_get_JWT()
{
    return error_JWT;
}

//METHODS

bool User_session::error_check_cookieId()
{
    if(error_cookieId.length() > 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool User_session::error_check_JWT()
{
    if(error_JWT.length() > 1)
    {
        return true;
    }
    return false;
}


void User_session::reset_error_cookieId()
{
    error_set_cookieId("");
}

void User_session::reset_error_JWT()
{
    error_set_cookieId("");
}

