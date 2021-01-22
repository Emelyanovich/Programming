#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::ifstream file ("d.json");
    json j1;
    file >> j1;

    std::cout << j1.dump(2);

}
