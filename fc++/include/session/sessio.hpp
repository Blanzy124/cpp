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
        std::string userName;
        std::string cookieId;
        std::string JWT;


    public:
        explicit user_sesion();

        ~user_sesion();

        void showtest();

        //SETTERS
        void set_userName(std::string userName_);
        void set_cookieId(std::string cookieId_);
        void set_JWT(std::string JWT_);

        //GETTERS
        std::string get_userName();
        std::string get_cookieId();
        std::string get_JWT();




        //METHODS
        std::string user_login(string userName, string userPassword);



};

