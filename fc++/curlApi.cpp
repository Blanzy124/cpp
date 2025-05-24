#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;
using std::cout;
using std::cin;

using json = nlohmann::json;


int main(){
   CURL *curl = curl_easy_init();
  if(curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, "https://localhost:8443");
    res = curl_easy_perform(curl);
    
    cout << curl_easy_perform() << endl;
    
    
    
    curl_easy_cleanup(curl);
  }
}