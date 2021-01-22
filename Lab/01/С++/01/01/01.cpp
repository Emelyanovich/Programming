#include <iostream>
#include "cpp_httplib/httplib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <locale>


using namespace httplib;
using namespace std;
using json = nlohmann::json;

// шаблоны для поиска в файле виджета
string srch1 = "{hourly[i].temp}", srch2 = "{hourly[i].weather[0].icon}", srch3 = "{hourly[i].weather[0].description}";
// кэш данных погоды
json cash;

// Проверяет текущее время, ищет данные на указанное время, обновляет кэш, если надо
json GetData() {
    json rep = json::parse(R"(
        {"temp":0, 
         "description":"", 
         "icon":"" })");

    // Получаем текущее время с сервера времени
    Client srv("http://worldtimeapi.org");
    auto result = srv.Get("/api/timezone/Europe/Simferopol");
    if (!result || (result->status != 200)) {
        cout << "Ошибка сервера времени." << endl;
        if (!result) {
            cout << "res.err=" << result.error() << endl;
        }
        else {
            cout << "srv.err=" << result->status << endl;
        }
        return rep;
    }

    unsigned int current_time = json::parse(result->body)["unixtime"].get<unsigned int>();

    for (short pass = 0; pass <= 2; pass++) {
        if (!cash.is_null()) {
            for (int i = 0; i < cash["hourly"].size(); i++) {
                if (current_time <= cash["hourly"][i]["dt"].get<unsigned int>()) {
                    rep["temp"] = cash["hourly"][i]["temp"];
                    rep["description"] = cash["hourly"][i]["weather"][0]["description"];
                    rep["icon"] = cash["hourly"][i]["weather"][0]["icon"];
                    return rep;
                }
            }
        }
        else if (pass) return rep;

        Client server("http://api.openweathermap.org");
        auto result = server.Get("/data/2.5/onecall?lat=44.9572&lon=34.1108&lang=ru&units=metric&exclude=current,minutely,daily,alerts&appid=b2b3ee6584c212f68d9b1a364c6e963e");
        if ((!result) || (result->status != 200)) {
            cout << "Ошибка сервера погоды." << endl;
            return rep;
        }
        cash = json::parse(result->body);
    }
}

void raw(const Request& req, Response& res) {
    json raw_reply = GetData();
    raw_reply.erase("icon");
    res.set_content(raw_reply.dump(4), "text/plain");
}

void root(const Request& req, Response& res) {
    json root_reply = GetData();
    cout << root_reply.dump() << endl;
    string all_file = "";
    ifstream iframe("iframe.html");   
    if (iframe.is_open() && (root_reply["icon"].get<string>() != "")) {
        getline(iframe, all_file, '\0');
        iframe.close();
        size_t pos1 = all_file.find(srch1), pos2 = all_file.find(srch2), pos3 = all_file.find(srch3);
        if ((pos1 == string::npos) || (pos2 == string::npos) || (pos3 == string::npos)) {
            all_file = "";
        }
        else {
            all_file.replace(pos1, srch1.size(), to_string(root_reply["temp"].get<int>()));
            all_file.replace(pos2, srch2.size(), root_reply["icon"].get<string>());
            all_file.replace(pos3, srch3.size(), root_reply["description"].get<string>());
        }
    }
    res.set_content(all_file, "text/html");
}

int main() {
    setlocale(LC_ALL, "Russian");

    Server server;
    server.Get("/raw", raw);
    server.Get("/", root);

    std::cout << "запуск сервера\n";

    server.listen("localhost", 3000);
    return 0;
}
