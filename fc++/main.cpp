#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>

#include <connection/serverConnection.hpp>




using namespace std;
using std::cout;



int main()
{
    std::cout << "after option\n";

    int option = 999;
    server_connection server;

    User_session session;





    cout << "Type \"0\" to close\n";
    
    std::string userName = "SamuelMedinaBlandon";
    std::string userpassword = "mgee2005";
    
    while(option != 0)
    {
        cout<< "Type your option\n";

        std::cin >> option;
        
        switch (option)
        {
            case 0:
            server.~server_connection();
            std::exit(0);
            break;
            case 1:
            {
                std::thread t1([&server, &userName, &userpassword] () {
                    server.login(userName, userpassword);
                }); 
                t1.join();
                std::cout << sizeof(server) << "\n";

                if(session.error_check_cookieId())
                {
                    std::cout << session.error_get_cookieId() << "\n";
                }
                else
                {
                    std::cout << "cookie ID: " << session.get_cookieId() << "\n";
                }
                break;
            }
            case 2:
            {
                std::thread t1([&server, &session] () {
                    server.JWT_refresh(session.get_cookieId());
                }); 
                t1.join();
                if(session.error_check_JWT())
                {
                    std::cout << session.error_get_JWT() << "\n";
                }
                else
                {
                    std::cout << "JWT : " << session.get_JWT() << "\n";
                }
                break;
            }
        default:
            cout << "Comand undefined\n";
            break;
        }

    }

    server.~server_connection();

    return 0;
}