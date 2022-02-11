#include <iostream>
#include <string>
#include <cassert>

#include <sstream>

#include "collector.h"

using namespace std;

const size_t MAX_COURIER_NAME_LENGTH  = 50;
const size_t MAX_PRODUCT_NAME_LENGTH  = 50;
const size_t MAX_ADDRESS_LENGTH  = 50;
const size_t MAX_ORDER_NUMBER  = 5000;
const size_t MAX_COST_OF_DELIVERY  = 3000;

class Order : public ICollectable
{
    uint16_t _order_number;
    string   _courier_name;
    string   _product_name;
    string   _address;
    uint16_t _cost_of_delivery;

protected:
    bool invariant() const
    {
        return _order_number <= MAX_ORDER_NUMBER
            && _cost_of_delivery <= MAX_COST_OF_DELIVERY
            && !_courier_name.empty() && _courier_name.size() <= MAX_COURIER_NAME_LENGTH
            && !_product_name.empty() && _product_name.size() <= MAX_PRODUCT_NAME_LENGTH
            && !_address.empty() && _address.size() <= MAX_ADDRESS_LENGTH;
    }

public:
    Order() = delete;
    Order(const Order & p) = delete;

    Order & operator = (const Order & p) = delete;

    Order(const string & product_name, const string & courier_name, const string & address, uint16_t order_number, uint16_t cost_of_delivery)
        : _product_name(product_name), _courier_name(courier_name), _address(address), _order_number(order_number), _cost_of_delivery(cost_of_delivery)
    {
        assert(invariant());
    }

    const string & getProductName() const { return _product_name; }
    const string & getCourierName() const { return _courier_name; }
    const string & getAddress() const { return _address; }
    uint16_t       getOrderNumber() const { return _order_number; }
    uint16_t       getCostOfDelivery() const { return _cost_of_delivery; }

    virtual bool   write(ostream& os) override
    {
        writeString(os, _product_name);
        writeString(os, _courier_name);
        writeString(os, _address);
        writeNumber(os, _order_number);
        writeNumber(os, _cost_of_delivery);

        return os.good();
    }
};

class ItemCollector: public ACollector
{
public:

    virtual shared_ptr<ICollectable> read(istream& is) override
    {
        string   product_name = readString(is, MAX_PRODUCT_NAME_LENGTH);
        string   courier_name = readString(is, MAX_COURIER_NAME_LENGTH);
        string   address = readString(is, MAX_ADDRESS_LENGTH);
        uint16_t order_number = readNumber<uint16_t>(is);
        uint16_t cost_of_delivery = readNumber<uint16_t>(is);

        return make_shared<Order>(product_name, courier_name, address, order_number, cost_of_delivery);
    }
};

bool performCommand(const vector<string> & args, ItemCollector & col)
{
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load")
    {
        string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.loadCollection(filename))
        {
            cerr << "Ошибка при загрузке файла '" << filename << "'" << endl;
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!col.saveCollection(filename))
        {
            cerr << "Ошибка при сохранении файла '" << filename << "'" << endl;
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            cerr << "Некорректное количество аргументов команды clean" << endl;
            return false;
        }

        col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 6)
        {
            cerr << "Некорректное количество аргументов команды add" << endl;
            return false;
        }

        col.addItem(make_shared<Order>(args[1].c_str(), args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5])));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            cerr << "Некорректное количество аргументов команды remove" << endl;
            return false;
        }

        col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 7)
        {
            cerr << "Некорректное количество аргументов команды update" << endl;
            return false;
        }

        col.updateItem(stoul(args[1]), make_shared<Order>(args[2].c_str(), args[3].c_str(), args[4].c_str(), stoul(args[5]), stoul(args[6])));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            cerr << "Некорректное количество аргументов команды view" << endl;
            return false;
        }

        size_t count = 0;
        for(size_t i=0; i < col.getSize(); ++i)
        {
            const Order & item = static_cast<Order &>(*col.getItem(i));

            if (!col.isRemoved(i))
            {
                cout << "[" << i << "] "
                        << item.getProductName() << " "
                        << item.getCourierName() << " "
                        << item.getAddress() << " "
                        << item.getOrderNumber() << " "
                        << item.getCostOfDelivery() << endl;
                count ++;
            }
        }

        cout << "Количество элементов в коллекции: " << count << endl;

        return true;
    }

    cerr << "Недопустимая команда '" << args[0] << "'" << endl;
    return false;
}

int main(int , char **)
{
    ItemCollector col;

    for (string line; getline(cin, line); )
    {
        if (line.empty())
            break;

        istringstream  iss(line);
        vector<string> args;

        for(string str; iss.good();)
        {
            iss >> str;
            args.emplace_back(str);
        }

        if (!performCommand(args, col))
            return 1;
    }

    cout << "Выполнение завершено успешно" << endl;
    return 0;
}