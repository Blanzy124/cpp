#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;
using std::cout;
using std::cin;


CURL* curl;
size_t writeCallback(void* data, size_t size, size_t nmenb, string* output){
  size_t totalSize = size * nmenb;
  output->append((char*)data, totalSize);
  return totalSize;


 }

class connection{
private:
 
protected: 
 std::string url;
 bool secure;
 string jsonData;
 
public:
 connection(std::string& _url, bool _secure);
 ~connection();

 //setters
 

 //getters
 string GETLastDataReques();

 string GETDataRequest();

 //methods
};

connection::connection(std::string& _url, bool _secure) : url(_url), secure(_secure){};

connection::~connection(){};


string connection::GETLastDataReques(){ return jsonData; };


string connection::GETDataRequest(){
  //this make the request

   CURLcode res;
   string readBuffer;

   curl_global_init(CURL_GLOBAL_DEFAULT);
   curl = curl_easy_init();

   if (curl){
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
     curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

     res = curl_easy_perform(curl);
     if (res != CURLE_OK){
       cout << "error en el curl perform: " << curl_easy_strerror(res) << "UR: OBJECT" << url << endl;

     }
     else{
      jsonData = readBuffer;
       //cout << "Response: \n" << readBuffer << endl;
     }

   }


   return readBuffer;
}


