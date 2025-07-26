
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include <connection/request_parser.hpp>

std::string Parse_to::login(std::string &userName, std::string &userPassword)
{
    json j_login_body = {
        {"userName", userName},
        {"userPassword", userPassword}
    };

    return j_login_body.dump();
}

