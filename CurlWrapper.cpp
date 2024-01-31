#include "CurlWrapper.h"

Wrapp::Wrapp()
{
	curl = curl_easy_init();
}

Wrapp::~Wrapp()
{
    curl_easy_cleanup(curl);
}

size_t Wrapp::write_call(void* contents, size_t size, size_t nmemb, std::string* userp)
{
	size_t realsize = size * nmemb;
    userp->append((char*)contents, realsize);
	return realsize;
}

std::string Wrapp::request_data()
{
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/users");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_call);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            //измени на cout
            std::cout << "curl_easy_perform() failed: \n" << curl_easy_strerror(res) << std::endl;
    }
    return response;
}

std::vector<Wrapp::Data> Wrapp::parse_data(const std::string& response)
{
    std::stringstream ss;
    ss << response;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    std::vector<Data> data;

    BOOST_FOREACH(boost::property_tree::ptree::value_type & v, pt) {
        Data d;
        d.id = v.second.get<std::string>("id");
        d.name = v.second.get<std::string>("name");
        d.username = v.second.get<std::string>("username");
        d.email = v.second.get<std::string>("email");
        //adress
        boost::property_tree::ptree address = v.second.get_child("address");
        d.street = address.get<std::string>("street");
        d.suite = address.get<std::string>("suite");
        d.zipcode = address.get<std::string>("zipcode");
        //geo
        boost::property_tree::ptree geo = address.get_child("geo");
        d.lat = geo.get<std::string>("lat");
        d.lng = geo.get<std::string>("lng");

        d.phone = v.second.get<std::string>("phone");
        d.website = v.second.get<std::string>("website");
        //company
        boost::property_tree::ptree company = v.second.get_child("company");
        d.comp_name = company.get<std::string>("name");
        d.catchPhrase = company.get<std::string>("catchPhrase");
        d.bs = company.get<std::string>("bs");

        data.push_back(d);
    }
    return data;
}

void Wrapp::print_data(const std::vector<Data>& data)
{
    for (const auto& d : data) {
        std::cout << "id: " << d.id << std::endl;
        std::cout << "name: " << d.name << std::endl;
        std::cout << "username: " << d.username << std::endl;
        std::cout << "email: " << d.email << std::endl;
        //adress
        std::cout << "address: \n  street:" << d.street << std::endl;
        std::cout << "  suite: " << d.suite << std::endl;
        std::cout << "  zipcode: " << d.zipcode << std::endl;
        //geo
        std::cout << "  geo: \n   lat:" << d.lat << std::endl;
        std::cout << "   lng: " << d.lng << std::endl;

        std::cout << "phone: " << d.phone << std::endl;
        std::cout << "website: " << d.website << std::endl;
        //company
        std::cout << "company: \n  name:" << d.comp_name << std::endl;
        std::cout << "  catchPhrase: " << d.catchPhrase << std::endl;
        std::cout << "  bs: " << d.bs << std::endl;
    }

}



