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
        std::string userName;
        std::string cookieId;
        std::string JWT;


    public:
        explicit User_session();

        ~User_session();

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



};

