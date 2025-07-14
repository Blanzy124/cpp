#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>

#include "connection/serverConecction.cpp"
#include "config.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;



using namespace std;
using std::cout;

class user_sesion{

    protected:
        string userName;
        string cookieId;
        string JWT;


    public:
        sserver_connection server();

        explicit user_sesion(){};
        ~user_sesion(){};

        void showtest()
        {
            std::string data{R"({"name": "Samuel", "age": 27})"};
        
            json Doc{json::parse(data)};
        
            std::cout << Doc["name"] << std::endl;
            std::cout << Doc["age"] << std::endl;
        };

        string user_login(string userName, string userPassword)
        {
        }



};

