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

CURL* curl;
size_t writeCallback(void* data, size_t size, size_t nmenb, string* output){
  size_t totalSize = size * nmenb;
  output->append((char*)data, totalSize);
  return totalSize;


 }

class connection{
private:
 
protected: 
  string userName = "cpp";
  string userPassword = "cpp2005";
  
  string url;

  string loginUrl;
  bool secure;
  string jsonData;

  string cookieId;
  string JWT;

 
public:
 connection(std::string& _url, bool _secure);
 ~connection();

 //setters
 

 //getters

 string GETCookieId();

 string GETJWT();

 string GETLastDataReques();

 string GETDataRequest();

 //methods
  void loginPost();
 

};

connection::connection(std::string& _url, bool _secure) : url(_url), secure(_secure){};

connection::~connection(){};


string connection::GETLastDataReques(){ return jsonData; };

string connection::GETCookieId(){ return cookieId; }

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

void connection::loginPost(){
  loginUrl = url + "/users/login";

    CURLcode res;
    string readBuffer;

   curl_global_init(CURL_GLOBAL_DEFAULT);
   curl = curl_easy_init();

   if (curl){
    json bodyJson = { {"userName", userName}, {"userPassword", userPassword}};
    string body = bodyJson.dump();
    cout << "Este el json del body: " << body << "bodyJson: " << bodyJson << endl;

     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

     //headers
      struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

      
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, loginUrl.c_str());  
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
     res = curl_easy_perform(curl);
     if (res != CURLE_OK){
       cout << "error en el curl perform: " << curl_easy_strerror(res) << "UR: OBJECT" << url << endl;

     }
     else{
      json res = json::parse(readBuffer);

      if(res.value("ok", false) != true){
        cout << "Error login: " << res.value("errorCode", "noErrorCode") << res.value("message", "noErrorMessage") << endl;

      }
      else{
      cookieId = res["data"].value("cookieId", "");
      if(cookieId == ""){
        cout << "cookieId undefined" << endl;
      }
      cout << "Response: " << res << endl;
}      
      //if(res.)
       //cout << "Response: \n" << readBuffer << endl;
     }

   }

  
  
  
  
  
  
}


