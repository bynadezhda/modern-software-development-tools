#include "hw/l3_DomainLayer.h"

using namespace std;

bool Order::invariant() const
{
    return _order_number <= MAX_ORDER_NUMBER
            && _cost_of_delivery <= MAX_COST_OF_DELIVERY
            && !_courier_name.empty() && _courier_name.size() <= MAX_COURIER_NAME_LENGTH
            && !_product_name.empty() && _product_name.size() <= MAX_PRODUCT_NAME_LENGTH
            && !_address.empty() && _address.size() <= MAX_ADDRESS_LENGTH;
}

Order::Order(const std::string & product_name, const std::string & courier_name, const std::string & address, uint16_t order_number, uint16_t cost_of_delivery)
        : _product_name(product_name), _courier_name(courier_name), _address(address), _order_number(order_number), _cost_of_delivery(cost_of_delivery)
{
    assert(invariant());
}

const string & Order::getProductName() const { return _product_name; }
const string & Order::getCourierName() const { return _courier_name; }
const string & Order::getAddress() const { return _address; }
uint16_t       Order::getOrderNumber() const { return _order_number; }
uint16_t       Order::getCostOfDelivery() const { return _cost_of_delivery; }

bool Order::write(ostream& os)
{
    writeString(os, _product_name);
    writeString(os, _courier_name);
    writeString(os, _address);
    writeNumber(os, _order_number);
    writeNumber(os, _cost_of_delivery);

    return os.good();
}

shared_ptr<ICollectable> ItemCollector::read(istream& is)
{
    string   product_name = readString(is, MAX_PRODUCT_NAME_LENGTH);
    string   courier_name = readString(is, MAX_COURIER_NAME_LENGTH);
    string   address = readString(is, MAX_ADDRESS_LENGTH);
    uint16_t order_number = readNumber<uint16_t>(is);
    uint16_t cost_of_delivery = readNumber<uint16_t>(is);

    return std::make_shared<Order>(product_name, courier_name, address, order_number, cost_of_delivery);
}
