#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
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

int show1(string* input){
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
    return 0;
}

int getLine(string* input){
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
    return 0;
    
}
int main(){

    int l;
    int s;

    string address = "";
    string *p_address = &address;
    std::future<int> in = std::async(std::launch::async, getLine, p_address);
    std::future<int> show = std::async(std::launch::async, show1, p_address);
    l = in.get();
    s = show.get();
    return 0;
}