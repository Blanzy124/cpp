#ifndef REQUEST_PARSER
#define REQUEST_PARSER
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

class Parse_to{
    public:
    static std::string login(std::string &userName, std::string &userPassword);
    static std::string JWT_refresh(std::string &cookieId);
	static std::string web_socket_simple_message(std::string &from, std::string &to, std::string &message);
};



#endif