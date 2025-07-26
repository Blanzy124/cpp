#ifndef SESSION_HPP
#define SESSION_HPP
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>



using namespace std;
using std::cout;

class User_session{

    protected:
    
    public:
    
    static std::string userName;
    static std::string cookieId;
    static std::string JWT;
    
    static std::string error_login;
    static std::string error_cookieId;
    static std::string error_JWT;


    explicit User_session();
        ~User_session();

        //SETTERS
        void set_userName(std::string userName_);
        void set_cookieId(std::string cookieId_);
        void set_JWT(std::string JWT_);

        void error_set_cookieId(std::string err);
        void error_set_JWT(std::string err);

        //GETTERS
        std::string get_userName();
        std::string get_cookieId();
        std::string get_JWT();

        std::string error_get_cookieId();
        std::string error_get_JWT();
        
        //METHODS

        bool error_check_cookieId();
        bool error_check_JWT();

        void reset_error_cookieId();
        void reset_error_JWT();







};

#endif