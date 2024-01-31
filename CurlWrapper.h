#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <curl/curl.h>
#include <sstream>



class Wrapp {

public:
    
    Wrapp();
    ~Wrapp();

    struct Data {
        std::string id;
        std::string name;
        std::string username;
        std::string email;
        //adress
        std::string street;
        std::string suite;
        std::string city;
        std::string zipcode;
        //geo
        std::string lat;
        std::string lng;

        std::string phone;
        std::string website;
        //company
        std::string comp_name;
        std::string catchPhrase;
        std::string bs;

    };

    static size_t write_call(void* contents, size_t size, size_t nmemb, std::string *userp);
    std::string request_data();
    std::vector<Data> parse_data(const std::string& response);
    void print_data(const std::vector<Data>& data);

private:
    CURL* curl;
    CURLcode res;
    std::string response;
    
    
   
};
