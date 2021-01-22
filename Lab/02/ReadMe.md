<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ИВТ-б-о-202(1)<br>
Емельянович Карина Руслановна<br>
направления подготовки 09.03.01 "Информатика и вычислительная техника"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2021</p>
<hr>
<h2> Цель работы </h2>
<p> 1. Получить представления о структуре post-запроса;<br>
2. Изучить webhooks как метод взаимодействия web-приложений;<br>
<h2> Постановка задачи </h2>
<p>1.Разработайте и зарегистрируйте навык для Алисы на сервисе ЯндексюДиалоги;<br>

2.В качестве backend-a для навыка реализуйте приложение на языке С++ выполняющее следующие функции:<br>

 &emsp; 1.Составление продуктовой корзины:<br>
- Добавление продукта в корзину;<br>
- Удаление продукта из корзины;<br>
- Очистка корзины;<br>
- Вывод списка товаров в корзине;<br>
- Подсчёт стоимости товаров в корзине.<br>

&emsp;2.Вывод справочной информации по навыку;<br>

&emsp;3.Регистрацию webhook-ов сторонних сервисов;<br>

&emsp;4.Отправку данных на сторонние сервисы.

3.В качестве стороннего сервиса реализуйте приложение на языке Python выполняющее следующие функции:

&emsp;1.Ожидание данных о покупке;

&emsp;2.Сохранение поступивших данных в excel-документ.
<h2> Выполнение работы </h2>
<p> 1. Для начала создала навык на сранице Яндекс.Диалоги. Данный навык будет уметь добавлять в виртульную корзину продукты с ценной, которые пользователь называет или записывает в диалоге с Алисой.
<p align="center"> <img src="./Image/01.png"> </p>  
<p align="center"> Рисунок 1 - Навык для Алисы <br><br>
<p>2.Создала навык Алисы, помогающий составить список покпок. Для получения цены я воспользовалась функцией от Яндекс, которая сама может считывать цифры в тексте.Команда "Добавить в корзину" добавляет в корзину товар и его цену,"Товары в корзине" выводит что в корзине на данный момент, "Сумма" подсчитывает и выводит суммарную стоимость всех товаров в этой сессии.
<p align="center"> <img src="./Image/02.png"> </p>  
<p align="center"> Рисунок 2 - Демонстрация работы навыка <br><br>
<p>Демонстрация работы функционала Помощь
<p align="center"> <img src="./Image/03.png"> </p>  
<p align="center"> Рисунок 3 -Демонстрация работы навыка

<p>3.Создала серверное приложение, генерирующее сайт с вебхуками посредством post- и get-запросов. Сервер "слушает" запросы, приходящие на localhost порт 1234 и генерирует страницу со списком вебхуков, которые кешируются в json-файл. При получении post-запроса ( отправляется при нажатии на кнопку Принять или Удалить) сервер смотрит, какой запос пришёл  и удаляет вебхук/добавляет новый.


<p align="center"> <img src="./Image/04.png"> </p>  
<p align="center"> Рисунок 4 - Скриншот страницы управления webhook-ами с добавленным webhook-ом клиентского приложения
<p>4.Полный исходный код серверного приложения
<details>
<summary>Исходный код </summary>

```c++

#include <iostream>
#include <string>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

using namespace httplib;
using json = nlohmann::json;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
const string replacerfull = "{webhooks_list}";
const string replacerone = "{Webhook URL}";
const string OneWebhookTemplate = u8R"(
<div class="form-row align-items-center">
    <div class="col">
        <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div>)";

ofstream logger("log.txt");

json config;

json config_open()
{
	ifstream config_cache("config.json");
	json config;
	logger << u8"Попытка открыть конфигурационный файл" << endl;
	if (config_cache.is_open())
	{
		config_cache >> config;
		logger << u8"Конфигурационный файл десериализирован" << endl;
	}
	else
	{
		logger << u8"Не удалость открыть конфигурационный файл" << endl;
		config["webhooks"] = json::array();
		logger << u8"Был создан json с пустым массивом" << endl;
	}

	return config;
}

void save_config(json config)
{
	ofstream config_cache("config.json");

	if (config_cache.is_open())
	{
		config_cache << config.dump(4);
		config_cache.close();
		logger << u8"Конфигурационный файл успешно обновлён" << endl;
	}
	else
	{
		logger << u8"Не удалось открыть конфигурационный файл" << endl;
	}
}

string gen_webhook_page()
{
	string webhooks_template, AllWebHooks;
	ifstream webhooks_cache("webhooks_template.html");

	if (webhooks_cache.is_open())
	{
		getline(webhooks_cache, webhooks_template, '\0');
		webhooks_cache.close();
	}
	else
	{
		logger << u8"Не удалось открыть шаблон сайта" << endl;
		return "";
	}

	if (config.empty())
	{
		config = config_open();
	}

	int size = config["webhooks"].size();
	if (size)
	{
		for (int i = 0; i < size; i++)
		{
			string site = config["webhooks"][i];
			string OneWebhook = OneWebhookTemplate;
			OneWebhook.replace(OneWebhook.find(replacerone), replacerone.length(), site);
			OneWebhook.replace(OneWebhook.find(replacerone), replacerone.length(), site);
			AllWebHooks = AllWebHooks + OneWebhook;
		}
		webhooks_template.replace(webhooks_template.find(replacerfull), replacerfull.length(), AllWebHooks);
	}
	else
	{
		webhooks_template.replace(webhooks_template.find(replacerfull), replacerfull.length(), "");
	}
	return webhooks_template;
}

void webhooks_post_resp(const Request& req, Response& res)
{
	if (config.empty())
	{
		config = config_open();
	}

	if (req.has_param("del"))
	{
		string webhook_to_remove = req.get_param_value("del");
		int size = config["webhooks"].size();
		for (int i = 0; i < size; i++)
		{
			string webhook = config["webhooks"][i];
			if (webhook == webhook_to_remove)
			{
				config["webhooks"].erase(config["webhooks"].begin() + i);
				logger << u8"Был удалён вебхук " << webhook << endl;
				break;
			}
		}
	}
	else if (req.has_param("set"))
	{
		string webhook_to_add = req.get_param_value("set");
		if (webhook_to_add == "")
		{
			logger << u8"Получен запрос на добавление пустого вебхука" << endl;
		}
		else
		{
			logger << u8"Получен запрос на добавление вебхука " << webhook_to_add << endl;
			int size = config["webhooks"].size();
			bool existence = false;
			if (size)
			{
				for (int i = 0; i < size; i++)
				{
					string webhook = config["webhooks"][i];
					if (webhook == webhook_to_add)
					{
						logger << u8"Этот вебхук уже существует" << webhook << endl;
						existence = true;
						break;
					}
				}
			}
			if (!existence)
			{
				logger << u8"Был добавлен вебхук " << webhook_to_add << endl;
				config["webhooks"].push_back(webhook_to_add);
			}
		}
	}
	save_config(config);
	string output = gen_webhook_page();
	res.set_content(output, "text/html; charset=UTF-8");
}

void webhooks_page(const Request& req, Response& res)
{
	string output = gen_webhook_page();
	res.set_content(output, "text/html");
}

enum voice_mode
{
	v_silent,
	v_speak
};
enum skill_mode
{
	s_help,
	s_exit
};

json s_list = json::array();

json help_buttons =
{
	{
		{"title", u8"Корзина"},
		{"hide", true}
	},
	{
		{"title", u8"Молчать"},
		{"hide", true}
	},
	{
		{"title", u8"Говорить"},
		{"hide", true}
	},
	{
		{"title", u8"Сумма"},
		{"hide", true}
	},
	{
		{"title", u8"Покупка завершена"},
		{"hide", true}
	},
	{
		{"title", u8"Выход"},
		{"hide", true}
	}
};

json silent_button =
{
	{"title", u8"Молчать"},
	{"hide", true}
};

json speak_button =
{
	{"title", u8"Говорить"},
	{"hide", true}
};

json go_help_button =
{
	{
		{"title", u8"Помощь"},
		{"hide", true}
	}
};

json gen_response(const string& text, const string& tts, const json& buttons, const json* current_session = nullptr, const bool end_session = false)
{
	json resp = {
		{"response", {
			{"buttons", buttons},
			{"end_session", end_session}
		}},
		{"version", "1.0"}
	};
	if (text != "")
	{
		resp["response"]["text"] = text;
	}
	if (current_session != nullptr && (*current_session)["voice_mode"] == v_speak)
	{
		if (tts != "")
		{
			resp["response"]["tts"] = tts;
		}
		resp["response"]["buttons"].push_back(silent_button);
	}
	else if (current_session != nullptr && (*current_session)["voice_mode"] == v_silent)
	{
		resp["response"]["buttons"].push_back(speak_button);
	}
	return resp;
}

void dialog(const Request& req, Response& res)
{
	json request = json::parse(req.body);

	string user_id = request["session"]["application"]["application_id"];
	json resp;
	json* current_session = nullptr;

	for (auto& session : s_list)
	{
		if (session["user_id"] == user_id)
		{
			current_session = &session;
			break;
		}
	}

	string txt, tts;

	if (request["session"]["new"].get<bool>())
	{
		if (current_session == nullptr)
		{
			json session;
			session["user_id"] = user_id;
			session["skill_mode"] = s_exit;
			session["voice_mode"] = v_speak;
			session["korzina"] = json::array();

			s_list.push_back(session);
			current_session = &s_list[s_list.size() - 1];
		}
		else
		{
			(*current_session)["skill_mode"] = s_exit;
			(*current_session)["voice_mode"] = v_speak;
		}
		txt = u8"Приветствую! Я помогу вам с покупками";
		tts = u8"Приветствую! Я помогу вам с покупками";
		json response = gen_response(txt, tts, go_help_button, current_session);
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	if (current_session == nullptr)
	{
		txt = u8"Произошла ошибка";
		tts = u8"Произошла ошибка";
		json response = gen_response(txt, tts, go_help_button, current_session);
		res.set_content(resp.dump(2), "text/json; charset=UTF-8");
		return;
	}

	string command = request["request"]["command"];
	if ((*current_session)["skill_mode"] == s_help)
	{
		if (command == u8"корзина")
		{
			txt = u8R"(Добавляйте товары в корзину командой
				"Добавить в корзину <название товара и цена>",
				удаляйте из корзины командой "Удалить из корзины <название товара>"
				Просматривайте список покупок командой "Список"
				Очищайте корзину командой "Очистить корзину")";
			tts = u8R"(Добавляйте товары в корзину командой
				"Добавить в корзину <название товара и цена>",
				удаляйте из корзины командой "Удалить из корзины <название товара>"
				Просматривайте список покупок командой "Список"
				Очищайте корзину командой "Очистить корзину")";
		}
		else if (command == u8"молчать")
		{
			txt = u8"Отключение голосовой озвучки всех моих сообщений";
			tts = u8"Отключение голосовой озвучки всех моих сообщений";
		}
		else if (command == u8"говорить")
		{
			txt = u8"Включение голосовой озвучки всех моих сообщений";
			tts = u8"Включение голосовой озвучки всех моих сообщений";
		}
		else if (command == u8"сумма")
		{
			txt = u8"Подсчёт и отображение стоимости всех товаров в корзине";
			tts = u8"Подсчёт и отображение стоимости всех товаров в корзине";
		}
		else if (command == u8"покупка завершена")
		{
			txt = u8"Передача данных о покупке для сохранения в эксель и очистка корзины";
			tts = u8"Передача данных о покупке для сохранения в эксель и очистка корзины";
		}
		else if (command == u8"выход")
		{
			txt = u8"Выход из режима помощи";
			tts = u8"Выход из режима помощи";
			(*current_session)["skill_mode"] = s_exit;
		}
		else
		{
			txt = u8"Неизвестная команда";
			tts = u8"Неизвестная команда";
		}

		json response;
		if ((*current_session)["skill_mode"] == s_help)
		{
			response = gen_response(txt, tts, help_buttons, current_session);
		}
		else
		{
			response = gen_response(txt, tts, go_help_button, current_session);
		}
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
	}
	else
	{
		if (command == u8"помощь")
		{
			string txt =
				u8R"(Говорить/молчать - включает/отключает озвучку.
					 Корзина - помощь с покупками. Основной функционал навыка.
					 Покупка завершена - сохранение данных в эксель и очистка корзины.
					 Сумма - подсчёт стоимости всех товаров в корзине.
					 Введите название комманды для более подробного описания
					 Выйти из помощи можно с помощью команды "Выход")";
			string tts =
				u8R"(Говорить/молчать - включает/отключает озвучку.
					 Корзина - помощь с покупками. Основной функционал навыка.
					 Покупка завершена - сохранение данных в эксель и очистка корзины.
					 Сумма - подсчёт стоимости всех товаров в корзине.
					 Введите название комманды для более подробного описания
					 Выйти из помощи можно с помощью команды "Выход")";
			json response = gen_response(txt, tts, help_buttons, current_session);
			(*current_session)["skill_mode"] = s_help;
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"молчать")
		{
			string txt = u8"Молчу, молчу";
			string tts;
			(*current_session)["voice_mode"] = v_silent;
			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"говорить")
		{
			string txt = u8"Хорошо";
			string tts = u8"Хорошо";
			(*current_session)["voice_mode"] = v_speak;
			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"добавить в корзину") == 0)
		{
			size_t size = request["request"]["nlu"]["tokens"].size();
			string txt = u8"Добавлено";
			string tts = u8"Добавлено";
			string item_name;
			int item_price = 0, num_index = 0;
			bool set_price = false;

			for (auto ent : request["request"]["nlu"]["entities"])
			{
				if (ent["type"].get<string>() == "YANDEX.NUMBER")
				{
					num_index = ent["tokens"]["start"];
					int val = ent["value"];
					if (val <= 0)
					{
						txt = u8"Цена всегда больше 0 рублей";
						tts = u8"Цена всегда больше 0 рублей";
					}
					else
					{
						item_price = val;
					}
					set_price = true;
					break;
				}
			}
			if (size == 3)
			{
				txt = u8"Что добавлять?";
				tts = u8"Что добавлять?";
			}
			else if (num_index == 3)
			{
				txt = u8"Укажите название товара";
				tts = u8"Укажите название товара";
			}
			else if (!set_price)
			{
				txt = u8"Укажите цену";
				tts = u8"Укажите цену";
			}
			else
			{
				for (int i = 3; i < num_index; ++i)
				{
					item_name += request["request"]["nlu"]["tokens"][i].get<string>();
					item_name += " ";
				}
				item_name.pop_back();
				json item = {
					{"item",  item_name},
					{"price", item_price}
				};
				(*current_session)["check"].push_back(item);
			}

			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"удалить из корзины") == 0)
		{
			size_t size = request["request"]["nlu"]["tokens"].size();

			string txt;
			string tts;
			string name = "";

			for (int i = 3; i < size; ++i)
			{
				name += request["request"]["nlu"]["tokens"][i].get<string>();
				name += " ";
			}
			bool found = false;
			int	item_index = 0;

			if (name == "")
			{
				txt = u8"Укажите название товара";
				tts = u8"Укажите название товара";
			}
			else
			{
				name.pop_back();
				for (auto& cart_item : (*current_session)["check"])
				{
					if (cart_item["item"].get<string>() == name)
					{
						found = true;
						break;
					}
					++item_index;
				}
				if (!found)
				{
					txt = u8"Товар отсутствует в корзине";
					tts = u8"Товар отсутствует в корзине";
				}
				else
				{
					txt = u8"Товар удалён";
					tts = u8"Товар удалён";
					(*current_session)["check"].erase((*current_session)["check"].begin() + item_index);
				}
			}
			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"очистить корзину")
		{
			string txt = u8"Корзина очищена";
			string tts = u8"Корзина очищена";
			json response = gen_response(txt, tts, go_help_button, current_session);
			(*current_session).erase("check");
			(*current_session)["check"] = json::array();
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"список")
		{
			string txt, tts;
			if ((*current_session)["check"].empty())
			{
				txt = u8"В корзине ничего нет";
				tts = u8"В корзине ничего нет";
			}
			else
			{
				txt = u8"Товары в корзине:";
				for (auto& elem : (*current_session)["check"])
				{
					int price = elem["price"].get<int>();

					txt += "\n"
						+ elem["item"].get<string>()
						+ u8" ценой "
						+ std::to_string(price);

					if (price % 10 == 0)
					{
						txt += u8" рублей,";
					}
					else if (price % 10 == 1)
					{
						txt += u8" рубль,";
					}
					else if (price % 10 < 5 && price % 10 > 0)
					{
						txt += u8" рубля,";
					}
					else
					{
						txt += u8" рублей,";
					}
				}
				txt.pop_back();
				tts = txt;
			}

			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"сумма")
		{
			string txt = "";
			string tts = "";

			size_t size = request["request"]["nlu"]["tokens"].size();
			int sum = 0;
			for (auto& cart_item : (*current_session)["check"])
			{
				sum += cart_item["price"].get<int>();
			}
			txt = u8"В корзине товаров на " + std::to_string(sum);
			tts = u8"В корзине товаров на " + std::to_string(sum);
			if (sum % 10 == 0)
			{
				txt += u8" рублей";
				tts += u8" рублей";
			}
			else if (sum % 10 == 1)
			{
				txt += u8" рубль";
				tts += u8" рубль";
			}
			else if (sum % 10 < 5 && sum % 10 > 0)
			{
				txt += u8" рубля";
				tts += u8" рубля";
			}
			else
			{
				txt += u8" рублей";
				tts += u8" рублей";
			}

			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(resp.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"покупка завершена")
		{
			string txt = u8"Формирую список покупок для сохранения в эксель...";
			string tts = u8"Формирую список покупок для сохранения в эксель...";
			json output, conf;
			output["user_id"] = user_id;
			output["check"] = (*current_session)["check"];
			conf = config_open();

			for (string link : conf["webhooks"])
			{
				int ind = link.find('/', static_cast<string>("https://").size());
				Client cli(link.substr(0, ind).c_str());
				cli.Post(link.substr(ind, -1).c_str(), output.dump(2), "application/json; charset=UTF-8");
			}

			(*current_session).erase("check");
			(*current_session)["check"] = json::array();

			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else
		{
			string txt = u8"Неизвестная команда";
			string tts = u8"Неизвестная команда";

			json response = gen_response(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
	}
}

int main()
{
	Server svr;
	svr.Post("/webhooks", webhooks_post_resp);
	svr.Get("/webhooks", webhooks_page);
	svr.Post("/", dialog);
	logger << u8"Сервер успешно запущен" << endl;
	svr.listen("localhost", 1234);
}

```
</details>
<br>

<p> 5. Полный исходный код клиентского приложения;


<details>
<summary>Исходный код</summary>

 ```python
from flask import Flask, request, jsonify
from datetime import datetime
import openpyxl

Buffer = []

def GetEmptyCell(sheet):
    i = 2
    while sheet[i][0].value != None:
        i += 1
    return i


def ListGenerate(sheet):
    num = GetEmptyCell(sheet)
    for i in range(len(Buffer)):
        for j in range(len(Buffer[i]['check'])):
            sheet[num][0].value = num - 1
            sheet[num][1].value = Buffer[i]['user_id']
            sheet[num][2].value = Buffer[i]['datetime']
            sheet[num][3].value = Buffer[i]['check'][j]['item']
            sheet[num][4].value = Buffer[i]['check'][j]['price']
            num += 1
    del num, i, j
    return sheet


def BufferToExcel():
    global Buffer
    try:
        book = openpyxl.open(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx', read_only=False)
    except:
        book = openpyxl.Workbook()
    sheet = book.active
    if sheet['A1'].value == None:
        sheet['A1'] = 'N'
        sheet['B1'] = 'User ID'
        sheet['C1'] = 'Datetime'
        sheet['D1'] = 'Item'
        sheet['E1'] = 'Prise'
    sheet = ListGenerate(sheet)
    book.save(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx')
    book.close()


def BufferGenerate(data):
    global Buffer
    data['datetime'] = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
    Buffer.append(data)
    if len(Buffer) >= 1000:
        BufferToExcel()
        Buffer = []


app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        data = request.json
        BufferGenerate(data)
        return 'OK'

    elif request.method == 'GET':
        return 'Это GET запрос'
if __name__ == "__main__":
	app.run()

```
</details>
<br>

<p>6. Excel-файл заполненный клиентским приложением.

[Ссылка на excel-файл](Python/data.xslx) со списком покупок

<h2>Вывод </h2>
Были выполнены поставленные задачи, а также достигнута цель данной работы - получила представления о структуре post-запроса, изучила webhooks как метод взаимодействия web-приложений.

Разработка сервера была выполнена с использованием сторонних библиотек: cpp-httplib для работы с http запросами, json для работы с JSON файлами. Python-клиент использует библиотеку flask обработки post-запросов.
