#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>

#include "connection/serverConnection.hpp"

#include "config/config.hpp"

//#include "session.cpp"


using namespace std;
using std::cout;

int main()
{

    int option;
    cout <<host<<port<< "\n";
    server_connection server;


    cout << "Type \"0\" to close\n";
    
    
    
    while(option != 0)
    {
        cout<< "Type your option\n";

        std::cin >> option;
        
        switch (option)
        {
            case 0:
            std::exit(0);
            break;
            case 1:
            {
                std::thread t1([&server] () {
                    server.perform_simple_GET();
                }); 
                
                t1.join();
                cout << sizeof(t1) << "   " << sizeof(server) << std::endl;
                cout << server.get_response_json() << "response" << std::endl;
                break;
            }
        default:
            cout << "Comand undefined\n";
            break;
        }

    }



    return 0;
}