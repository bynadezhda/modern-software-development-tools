#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"
#include <string>
#include <iostream>

const size_t MAX_COURIER_NAME_LENGTH  = 50;
const size_t MAX_PRODUCT_NAME_LENGTH  = 50;
const size_t MAX_ADDRESS_LENGTH  = 50;
const size_t MAX_ORDER_NUMBER  = 5000;
const size_t MAX_COST_OF_DELIVERY  = 3000;

class Order : public ICollectable
{
    uint16_t _order_number;
    std::string   _courier_name;
    std::string   _product_name;
    std::string   _address;
    uint16_t _cost_of_delivery;

protected:
    bool invariant() const;

public:
    Order() = delete;
    Order(const Order & p) = delete;

    Order & operator = (const Order & p) = delete;

    Order(const std::string & product_name, const std::string & courier_name, const std::string & address, uint16_t order_number, uint16_t cost_of_delivery);

    const std::string & getProductName() const;
    const std::string & getCourierName() const;
    const std::string & getAddress() const;
    uint16_t       getOrderNumber() const;
    uint16_t       getCostOfDelivery() const;

    virtual bool   write(std::ostream& os) override;

};

class ItemCollector: public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H
