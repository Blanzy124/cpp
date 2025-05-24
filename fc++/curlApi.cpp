#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "funtionality.cpp"

using namespace std;
using std::cout;
using std::cin;

using json = nlohmann::json;


int options;

int main(){
  string url = "https://localhost:8443";
  connection apiReq = connection(url, false);
  

  do
  {
    cout << "White your selection 'request test (1)', 'get las request (2)', 'close(0)': \n";
    cin >> options;

    switch (options)
    {
    case 1:{
      cout << apiReq.GETDataRequest() << endl;
      break;
    }
    case 2:
      cout << apiReq.GETLastDataReques() << endl;
      break;
    case 0: 
      options = 0;
    default:
      break;
    }
  } while (options != 0);
  
  
  curl_global_cleanup();

  return 0;
  
}