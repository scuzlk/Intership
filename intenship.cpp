#include "CurlWrapper.h"

int main(void)
{
    Wrapp wrapp ;
    std::string response = wrapp.request_data();
    std::vector<Wrapp::Data> data = wrapp.parse_data(response);
    wrapp.print_data(data);
    return 0;
}