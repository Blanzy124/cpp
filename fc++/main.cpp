//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <future>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using std::cout;

std::mutex mtx;

void show1(string* input){
    string inputC;
    while (true)
    {
        //std::lock_guard<std::mutex> lock(mtx);
        mtx.lock();
        if(*input != inputC){
            cout << "address: " << &input << endl;
            cout << *input << "salida" << endl;
            inputC = *input;
        }
        mtx.unlock();
    }
    return;
}

void getLine(string* input){
    string inputC = "";
    while (true)
    {
        std::getline(std::cin, inputC);
        mtx.lock();
        //std::lock_guard<std::mutex> lock(mtx);
        if(*input != inputC){
            *input = inputC;
        }
        mtx.unlock();
    }
    return;
    
}
int main(){

    int l;
    int s;
    cout << "hello to multi-thred in and out, esto es con los threads \n";
    string address = "";
    string *p_address = &address;

    std::thread f1(getLine, p_address);
    std::thread s2(show1, p_address);
    f1.join();
    s2.join();
    
    return 0;
}