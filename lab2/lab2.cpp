#include <iostream>
#include <string>
#include <chrono>
#include <ctime> 
#include <unistd.h>
//#pragma warning(disable : 4996)

using namespace std;

class changeLog {
public:
    virtual void addChanges(string comment, string courier_name, string product_name, string address, uint16_t order_number, uint16_t cost_of_delivery) = 0;
};


class terminalChangeLog : public changeLog {
public:
    void addChanges(string comment, string courier_name, string product_name, string address, uint16_t order_number, uint16_t cost_of_delivery);
};

void terminalChangeLog::addChanges(string comment, string courier_name, string product_name, string address, uint16_t order_number, uint16_t cost_of_delivery)
{
    //time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    //cout << "Time: " << ctime(&time);
    cout << "Comment: " << comment << '\n';
    cout << "Changed card: ";
    cout << "Courier name: " << courier_name << ", ";
    cout << "Product name: " << product_name << ", ";
    cout << "Address: " << address << ", ";
    cout << "Order number: " << order_number << ", ";
    cout << "Cost of delivery: " << cost_of_delivery << "\n\n";
};

class Order {
    changeLog* log;
    
    string   courier_name;
    string   product_name;
    string   address;
    uint16_t order_number;
    uint16_t cost_of_delivery;

    void setCourierName(string _courier_name) {
        courier_name = _courier_name;
    };
    void setProductName(string _product_name) {
        product_name = _product_name;
    };
    void setAddress(string _address) {
        address = _address;
    };
    void setOrderNumber(uint16_t _order_number) {
        order_number = _order_number;
    };
    void setCostOfDelivery(uint16_t _cost_of_delivery) {
        cost_of_delivery = _cost_of_delivery;
    };

public:
    Order(string _courier_name, string _product_name, string _address, uint16_t _order_number, uint16_t _cost_of_delivery, changeLog* _log)
    {
        log = _log;
        setCourierName(_courier_name);
        setProductName(_product_name);
        setAddress(_address);
        setOrderNumber(_order_number);
        setCostOfDelivery(_cost_of_delivery);
        log->addChanges("Created new order.", courier_name, product_name, address, order_number, cost_of_delivery);
    }

    void changeCourierName(string _courier_name) {
        setCourierName(_courier_name);
        log->addChanges("Changes were made.", courier_name, product_name, address, order_number, cost_of_delivery);
    };
    void changeProductName(string _product_name) {
        setProductName(_product_name);
        log->addChanges("Changes were made.", courier_name, product_name, address, order_number, cost_of_delivery);
    };
    void changeAddress(string _address) {
        setAddress(_address);
        log->addChanges("Changes were made.", courier_name, product_name, address, order_number, cost_of_delivery);
    };
    void changeOrderNumber(uint16_t _order_number) {
        setOrderNumber(_order_number);
        log->addChanges("Changes were made.", courier_name, product_name, address, order_number, cost_of_delivery);
    };
    void changeCostOfDelivery(uint16_t _cost_of_delivery) {
        setCostOfDelivery(_cost_of_delivery);
        log->addChanges("Changes were made.", courier_name, product_name, address, order_number, cost_of_delivery);
    };
};



int main(int argc, char** argv)
{
    Order order1("N.S.Ivanov", "Printer", "Rusakovskaya,16", 178, 300, new terminalChangeLog());
    order1.changeCourierName("M.R.Sidorov");
    order1.changeProductName("Computer");
}