#include "certificades.hpp"
#include "httpPerform.cpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;


class server_connection : public std::enable_shared_from_this<server_connection>{
    protected:
        //request specs
        const char* &host;
        const char* &port;
        int version = 11;
        //Target must be set in each request
        const char* target; //This can not be give as reference, must be created as a new atribute.
        //performcHTTP GET, must be past to the simple_GET`
        tcp::resolver resolver;
        ssl::context ctx;

        explicit server_connection(const char* &host_, const char* &port_,const char* &target_, net::any_io_executor ex, ssl::context &ctx_) : host(host_), port(port_), target(target_), resolver(ex), ctx(ctx_) {};
        ~server_connection(){};

    public:
        //SETTERS
        void set_target(const char* &target_){
            server_connection::target = target_; //Must be reaset everyTime you make a GET request.
        }

        //METHODS

        void perform_simple_GET(std::string &targer_){
            std::shared_ptr<simple_GET> sget = std::make_shared<simple_GET>(host, port, target, resolver, ctx);

            sget->set_target(target);

        }
        
        
};


int main(){
    std::cout << "Si compilo" << std::endl;
    std::cout << "push test 2" << std::endl;
    std::cout << "push from laptop" << std::endl;

    



    return 0;
}