#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <vector>

using namespace std;

struct Order
{
    string   courier_name;
    string   product_name;
    string   address;
    uint16_t order_number;
    uint16_t cost_of_delivery;
};

int main()
{
    vector<unique_ptr<Order>> a;

    {
        a.push_back(make_unique<Order>(Order {"Printer", "N.S.Ivanov", "Rusakovskaya,16", 178, 300}));
        a.push_back(make_unique<Order>(Order {"Computer", "M.R.Sidorov", "Bronnaya,8",  1157, 500}));
        a.push_back(make_unique<Order>(Order {"Monitor", "R.I.Karpov", "Spirodonovka,12", 564, 1000}));

    };

    for(const auto &o : a)
        cout << o->courier_name << ' ' <<  o->product_name << ' ' << o->address << ' ' << o->order_number 
        <<' ' << o->cost_of_delivery << endl;

    return 0;
}