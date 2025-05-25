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
  string JWTurl;
  bool secure;
  string jsonData;

  string cookieId;
  string JWT;

 
public:
 connection(std::string& _url, bool _secure);
 ~connection();

 //setters
 void setJWT();

 //getters

 string GETCookieId();

 string GETJWT();

 string GETLastDataReques();

 string GETDataRequest();

 //methods

  bool jsonVerification(string& JWTv);

  void loginPost();

};

connection::connection(std::string& _url, bool _secure) : url(_url), secure(_secure){};

connection::~connection(){};

bool connection::jsonVerification(string& JWTv){
  try{
    auto j = json::parse(JWTv);
    return j.is_object();
  }catch(json::parse_error& e){
    return false;
  }
};

void connection::setJWT(){
  string JWTurl = url + "/tokens/jwtrefresh";

  CURLcode res;

  string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if(curl){
    json bodyJson = {{ "cookieId", cookieId }};
    string body = bodyJson.dump();

    
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    //headers
    struct curl_slist *headers=NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, JWTurl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      cout << "error en el curl perform set up JWT: " << curl_easy_strerror(res) << endl;
    }
    else{
      if(jsonVerification(readBuffer) == true){
        json resp = json::parse(readBuffer);
  
  
        if(resp.value("ok", false) != true){
          cout << "Error on set JWT: " << resp.value("errorCode", 0) << "    " << resp.value("message", "noErrorMessage") << endl;
        }
      }
      else{
        JWT = readBuffer;
      };
      

    }
    
  }



}



string connection::GETLastDataReques(){ return jsonData; };

string connection::GETCookieId(){ return cookieId; }

string connection::GETJWT(){ return JWT; }

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
}      
      //if(res.)
       //cout << "Response: \n" << readBuffer << endl;
     }

   }

  
  
  
  
  
  
}


