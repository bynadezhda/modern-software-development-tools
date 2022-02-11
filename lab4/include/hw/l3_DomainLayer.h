#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"
#include <string>
#include <iostream>

const size_t MAX_COURIER_NAME_LENGTH  = 50;
const size_t MAX_PRODUCT_NAME_LENGTH  = 50;
const size_t MAX_ADDRESS_LENGTH  = 500;
const size_t MAX_ORDER_NUMBER  = 5000;
const size_t MAX_COST_OF_DELIVERY  = 3000;

class Address {
    std::string _street;
    uint16_t _house;
    uint16_t _flat;
    uint16_t _floor;

protected:
    bool invariant() const;

public:
    Address() = delete;
    Address(const Address & p) = delete;

    Address & operator = (const Address & p) = delete;

    Address(const std::string & street, uint16_t house, uint16_t flat, uint16_t floor);

    const std::string & getStreet() const;
    uint16_t            getHouse() const;
    uint16_t            getFlat() const;
    uint16_t            getFloor() const; 
};

class Order : public ICollectable
{
    uint16_t _order_number;
    std::string   _courier_name;
    std::string   _product_name;
    Address       _address;
    uint16_t _cost_of_delivery;
    std::string   _status_paid;
    std::string   _status_delivered;

protected:
    bool invariant() const;

public:
    Order() = delete;
    Order(const Order & p) = delete;

    Order & operator = (const Order & p) = delete;

    Order(const std::string & product_name, const std::string & courier_name, uint16_t order_number, uint16_t cost_of_delivery, const std::string & street, uint16_t house, uint16_t flat, uint16_t floor, const std::string & status_paid, const std::string & status_delivered);

    const std::string & getProductName() const;
    const std::string & getCourierName() const;
    const Address & getAddress() const;
    uint16_t       getOrderNumber() const;
    uint16_t       getCostOfDelivery() const;
    const std::string & getStatusPaid() const;
    const std::string & getStatusDelivered() const;

    virtual bool   write(std::ostream& os) override;

};

class ItemCollector: public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H
