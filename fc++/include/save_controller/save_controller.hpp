#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <thread>

#include <nlohmann/json.hpp>

#include <session/session.hpp>

using json = nlohmann::json;


class Save_controller{
    protected:
        //GLOBAL SESSION
        User_session session;

    public:
        Save_controller();
        ~Save_controller();

        void target_discrimination_save(std::string target_,std::string response_json_);

};

