# include <iostream>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <string>


struct Weapon {
    uint damage;
    uint critical;
    uint durability;
};

structArmor {
   uint guard;
   uint durability;
};

struct Item;
Item generateItem();

struct Item
{
    enum class ItemType { COIN, RUNE, WEAPON, ARMOR } type;
    union Value { Coin coin; Rune rune; Weapon weapon; Armor armor; } value;

    Item& operator++()
    {
        *this = generateItem();
        return *this;
    }
};

Item GetCoin(uint count);

Item GetRune(Rune::Element element, uint level);
Item GetFireRune(uint level);
Item GetWaterRune(uint level);
Item GetEarthRune(uint level);
Item GetAirRune(uint level);

Item GetWeapon(uint damage, uint critical, uint durability);
Item GetArmor(uint guard, uint durability);

template<class T, class S>
struct Pair
{
    T first;
    S second;
};

std::vector<Pair<Item, double>> chances{
    {GetCoin(1000), 50.0},
    {GetFireRune(1), 6.0},
    {GetWaterRune(1), 13.0},
    {GetEarthRune(1), 7.0},
    {GetAirRune(1), 14.0},
    {GetFireRune(5), 0.6},
    {GetWaterRune(5), 1.3},
    {GetEarthRune(5), 0.7},
    {GetAirRune(5), 1.4},
    {GetFireRune(5), 0.06},
    {GetWaterRune(5), 0.13},
    {GetEarthRune(5), 0.07},
    {GetAirRune(5), 0.14},
    {GetWeapon(100, 0, 100), 1.4},
    {GetWeapon(75, 50, 100), 1.4},
    {GetArmor(50, 100), 2.8},
};

const int precision = 100;
double count_total_chance() {
    double sum = 0;
    for (auto& pair : chances) {
        sum += pair.second;
    }
    return sum * precision;
}

const double total_chance = count_total_chance();

using LootBox = std::vector<Item>;

LootBox generateLootBox();

LootBox& operator<<(LootBox& lootbox, Item& item);

std::ostream& operator<<(std::ostream& out, Item& item);

std::ostream& operator<<(std::ostream& out, LootBox& lootbox);

LootBox& operator<<(LootBox& lootbox, Item item) {
    lootbox.push_back(item);
    return lootbox;
}

Item generateItem() {
    double r = double(rand() % int(total_chance)) / 100;
    double current_sum = 0;

    for (auto& elem : chances) {
        if (current_sum <= r and r < current_sum + elem.second) {
            return elem.first;
        }
        current_sum += elem.second;
    }
    return chances[0].first;
}

LootBox generateLootBox() {
    LootBox box;
    std::srand(std::time(0));

    for (int i = 0; i < 3; ++i) {
        box << generateItem();
    }
    return box;
}


int main() {
    using std::cout;
    using std::cin;
    using std::endl;

    std::string input;
    while (true) {
        cout << "Открыть лутбокс? Yes/No" << endl;

        cin >> input;

        if (input == "Y" or input == "y" or input == "Yes" or input == "yes") {
            auto box = generateLootBox();
            cout << box << endl;
        }
        else if (input == "N" or input == "n" or input == "No" or input == "no") {
            break; // from while
        }
    }
};