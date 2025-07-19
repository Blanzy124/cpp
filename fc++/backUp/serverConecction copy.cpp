#include "common/certificades.hpp"
#include "connection/httpPerform.hpp"
#include "connection/serverConecction.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

inline std::mutex mtx;

class server_connection{
    protected:

        std::string response_json = "";
        //request specs
        const char* &host;
        const char* &port;
        int version = 11;
        //Secure setting
        bool secure = true;
        //Target must be set in each request
        const char* target; //This can not be give as reference, must be created as a new atribute.
        //performcHTTP GET, must be past to the simple_GET`

        //GLOBAL CONFIG
        net::io_context ioc;
            
        ssl::context ctx{ssl::context::tlsv12_client};
        
        
    public:

        //Constructor and destructor
        explicit server_connection(const char* &host_, const char* &port_) : host(host_), port(port_){};
        ~server_connection(){};
        
        
        //SETTERS

        void set_secure(bool secure, ssl::context &ctx)
        {
            if(!secure)
            {
                return ctx.set_verify_mode(ssl::verify_none);
            }
            else{
               
                return ctx.set_verify_mode(ssl::verify_peer);
            }

        }

        void set_target(const char* target_){
            server_connection::target = target_; //Must be reaset everyTime you make a GET request.
        }

        //GETTERS

        std::string get_response_json()
        {
            return response_json;
        }

        //METHODS

        void load_certificates()
        {
            load_root_certificates(ctx);
        }

        void perform_simple_GET(){
            //server_connection::set_secure(secure, ctx); //this set the secure.
            mtx.lock();
            std::make_shared<simple_GET>(host, port, target, version, net::make_strand(ioc), ctx, response_json)->run(); 
            cout << "performed\n";
            ioc.run();
            mtx.unlock();
            ioc.restart();


            return;
        }
        
        
};