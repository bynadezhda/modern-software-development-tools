#include "hw/l3_DomainLayer.h"

using namespace std;

bool Address::invariant() const
{
}

Address::Address(const std::string & street, uint16_t house, uint16_t flat, uint16_t floor) 
    :_street(street), _house(house), _flat(flat), _floor(floor)
{
};

const string & Address::getStreet() const { return _street; }
uint16_t       Address::getHouse() const { return _house; }
uint16_t       Address::getFlat() const { return _flat; }
uint16_t       Address::getFloor() const { return _floor; }

bool Order::invariant() const
{
    return _order_number <= MAX_ORDER_NUMBER
            && _cost_of_delivery <= MAX_COST_OF_DELIVERY
            && !_courier_name.empty() && _courier_name.size() <= MAX_COURIER_NAME_LENGTH
            && !_product_name.empty() && _product_name.size() <= MAX_PRODUCT_NAME_LENGTH;
            //&& !_address.empty() && _address.size() <= MAX_ADDRESS_LENGTH;
}

Order::Order(const std::string & product_name, const std::string & courier_name, uint16_t order_number, uint16_t cost_of_delivery, const std::string & street, uint16_t house, uint16_t flat, uint16_t floor, const std::string & status_paid, const std::string & status_delivered)
        : _product_name(product_name), _courier_name(courier_name), _order_number(order_number), _cost_of_delivery(cost_of_delivery), _status_paid(status_paid), _status_delivered(status_delivered), _address(street, house, flat, floor)
{
    assert(invariant());
}

const string & Order::getProductName() const { return _product_name; }
const string & Order::getCourierName() const { return _courier_name; }
const Address & Order::getAddress() const { return _address; }
uint16_t       Order::getOrderNumber() const { return _order_number; }
uint16_t       Order::getCostOfDelivery() const { return _cost_of_delivery; }
const string & Order::getStatusPaid() const { return _status_paid; }
const string & Order::getStatusDelivered() const { return _status_delivered; }

bool Order::write(ostream& os)
{
    writeString(os, _product_name);
    writeString(os, _courier_name);
    writeNumber(os, _order_number);
    writeNumber(os, _cost_of_delivery);
    writeString(os, _address.getStreet());
    writeNumber(os, _address.getHouse());
    writeNumber(os, _address.getFlat());
    writeNumber(os, _address.getFloor());
    writeString(os, _status_paid);
    writeString(os, _status_delivered);
    return os.good();
}

shared_ptr<ICollectable> ItemCollector::read(istream& is)
{
    string   product_name = readString(is, MAX_PRODUCT_NAME_LENGTH);
    string   courier_name = readString(is, MAX_COURIER_NAME_LENGTH);
    Address  address(readString(is, MAX_ADDRESS_LENGTH), readNumber<uint16_t>(is), readNumber<uint16_t>(is), readNumber<uint16_t>(is));
    uint16_t order_number = readNumber<uint16_t>(is);
    uint16_t cost_of_delivery = readNumber<uint16_t>(is);
    string   status_paid = readString(is, 50);
    string   status_delivered = readString(is, 50);

    return std::make_shared<Order>(product_name, courier_name, order_number, cost_of_delivery, address.getStreet(), address.getHouse(), address.getFlat(), address.getFloor(), status_paid, status_delivered);
}
