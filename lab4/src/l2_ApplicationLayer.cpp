#include "hw/l2_ApplicationLayer.h"

using namespace std;

bool Application::performCommand(const vector<string> & args)
{
    if (args.empty())
        return false;

    if (args[0] == "l" || args[0] == "load")
    {
        string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!_col.loadCollection(filename))
        {
            _out.Output("Ошибка при загрузке файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "s" || args[0] == "save")
    {
        string filename = (args.size() == 1) ? "hw.data" : args[1];

        if (!_col.saveCollection(filename))
        {
            _out.Output("Ошибка при сохранении файла '" + filename + "'");
            return false;
        }

        return true;
    }

    if (args[0] == "c" || args[0] == "clean")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды clean");
            return false;
        }

        _col.clean();

        return true;
    }

    if (args[0] == "a" || args[0] == "add")
    {
        if (args.size() != 11)
        {
            _out.Output("Некорректное количество аргументов команды add");
            return false;
        }
        _col.addItem(make_shared<Order>(args[1].c_str(), args[2].c_str(), stoul(args[3]), stoul(args[4]), args[5].c_str(), stoul(args[6]), stoul(args[7]), stoul(args[8]), args[9].c_str(), args[10].c_str()));
        return true;
    }

    if (args[0] == "r" || args[0] == "remove")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды remove");
            return false;
        }

        _col.removeItem(stoul(args[1]));
        return true;
    }

    if (args[0] == "u" || args[0] == "update")
    {
        if (args.size() != 12)
        {
            _out.Output("Некорректное количество аргументов команды update");
            return false;
        }
      
        _col.updateItem(stoul(args[1]), make_shared<Order>(args[2].c_str(), args[3].c_str(), stoul(args[4]), stoul(args[5]), args[6].c_str(), stoul(args[7]), stoul(args[8]), stoul(args[9]), args[10].c_str(), args[11].c_str()));
        return true;
    }

    if (args[0] == "v" || args[0] == "view")
    {
        if (args.size() != 1)
        {
            _out.Output("Некорректное количество аргументов команды view");
            return false;
        }

        size_t count = 0;
        for(size_t i=0; i < _col.getSize(); ++i)
        {
            const Order & item = static_cast<Order &>(*_col.getItem(i));

            if (!_col.isRemoved(i))
            {
                _out.Output("[" + to_string(i) + "] "
                        + item.getProductName() + " "
                        + item.getCourierName() + " "
                        + to_string(item.getOrderNumber()) + " "
                        + to_string(item.getCostOfDelivery()) + " "
                        + item.getAddress().getStreet() + " "
                        + to_string(item.getAddress().getHouse()) + " "
                        + to_string(item.getAddress().getFlat()) + " "
                        + to_string(item.getAddress().getFloor()));
                count ++;
            }
        }

        _out.Output("Количество элементов в коллекции: " + to_string(count));
        return true;
    }

    if (args[0] == "vr" || args[0] == "viewReport")
    {
        if (args.size() != 2)
        {
            _out.Output("Некорректное количество аргументов команды viewReport");
            return false;
        }
        _out.Output("Отчет по курьеру " + args[1]);
        for(size_t i=0; i < _col.getSize(); ++i)
        {
            const Order & item = static_cast<Order &>(*_col.getItem(i));
            if (item.getCourierName() == args[1] && item.getStatusPaid() != "not_paid" && item.getStatusDelivered() == "not_delivered") {
                _out.Output("   Товар №" + to_string(item.getOrderNumber()) + " " + item.getProductName() + " Адрес: Улица: " + item.getAddress().getStreet() + " Дом: " + to_string(item.getAddress().getHouse()) + " Квартира: " + to_string(item.getAddress().getFlat()) + " Этаж: " + to_string(item.getAddress().getFloor()));
            }
        }
        return true;
    }

    _out.Output("Недопустимая команда '" + args[0] + "'");
    return false;
}
