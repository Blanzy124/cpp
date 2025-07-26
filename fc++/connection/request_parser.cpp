
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include <connection/request_parser.hpp>

std::string Parse_to::login(std::string &userName, std::string &userPassword)
{
    json j_login_body = 
    {
        {"userName", userName},
        {"userPassword", userPassword}
    };

    return j_login_body.dump();
}

std::string Parse_to::JWT_refresh(std::string &cookieId)
{
    json j_JWT_refresh_body = 
    {
        {"cookieId", cookieId}
    };

    return j_JWT_refresh_body.dump();
}



