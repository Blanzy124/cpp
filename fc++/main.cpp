#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>

#include "connection/serverConnection.hpp"


//#include "session.cpp"


using namespace std;
using std::cout;

int main()
{

    int option = 999;
    server_connection server;


    cout << "Type \"0\" to close\n";
    
    
    
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
                std::thread t1([&server] () {
                    server.perform_simple_GET();
                }); 
                t1.join();
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