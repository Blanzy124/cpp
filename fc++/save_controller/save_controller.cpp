#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

#include <session/session.hpp>
#include <connection/targets.hpp>
#include <save_controller/save_controller.hpp>

using json = nlohmann::json;

Save_controller::Save_controller(){};
Save_controller::~Save_controller(){};

//HERE COMES ALL THE SAVE MANAGER, ALL DATA THAT NEED TO BE SAVED AN DISCRIMINADE MUST BE SET UP HERE
void Save_controller::target_discrimination_save(std::string target_, std::string response_json_)
{
    if(target_ == Target_to::wellcome)
    {
        try
        {
            json j = json::parse(response_json_);
            std::cout << "It works " << j[0]["message"] << "\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    if(target_ == Target_to::loging)
    {
        try
        {
            session.reset_error_cookieId(); //RESET THE ERROR BEFORE THE NEXT REQUEST

            json j = json::parse(response_json_);

            if(j["ok"] != true)
            {
                session.error_set_cookieId(j["message"]);
                return;
            }
            else
            {
                session.set_cookieId(j["data"]["cookieId"]);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }

    if (target_ == Target_to::JWT_refresh)
    {
        try
        {
            session.reset_error_JWT();

            json j = json::parse(response_json_);

            if(j["ok"] != true)
            {
                session.error_set_JWT(j["message"]);
                return;
            }
        }
        catch(const std::exception& e)
        {
            std::string JWT = response_json_.substr(1, response_json_.size() - 2); //THIS EXTRAC THE STRING WITHOUT THE ""
            session.set_JWT(JWT);
            return;
        }
        
    }
    
}


