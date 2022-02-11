<h1 align="center">Создание инварианта</h1>

## Описание задания

Задача №17: "Курьерская служба".

Карточка Order должна содержать следующие данные:

* Номер заказа
* ФИО курьера
* Название товара
* Адрес доставки
* Стоимость доставки

## Цели работы

На примере программы на языке С++:

* изучить объекты с разными видами состояний;
* определить инвариант класса;
* освоить работу с обобщёнными контейнерами стандартной библиотеки С++
* освоить работу с потоками ввода / вывода стандартной библиотеки С++
* освоить использование основных паттернов объектно-ориентированного проектирования
* освоить применение инструментов git и GitLab

## Инвариант класса Person

```cpp
    bool invariant() const
    {
        return _order_number <= MAX_ORDER_NUMBER
            && _cost_of_delivery <= MAX_COST_OF_DELIVERY
            && !_courier_name.empty() && _courier_name.size() <= MAX_COURIER_NAME_LENGTH
            && !_product_name.empty() && _product_name.size() <= MAX_PRODUCT_NAME_LENGTH
            && !_address.empty() && _address.size() <= MAX_ADDRESS_LENGTH;
    }
```

## Выводы

В ходе выполнения домашнего задания изучили ключевые паттерны объектно-ориентированного программирования, объекты с набором разных состояний, особенности обобщенных контейнеров стандартной библиотеки С++.

Также, в ходе выполнения изучили и применили на практике инструменты распределенной системы управления версиями Git и веб-инструмента GitLab. 

Согласно заданию определили инвариант класса, разработали автотесты, приобрели навыки работы со сценариями непрерывной интеграции Continuos Integration, который описан в файле .gitlab-ci.yml. CI автоматизирует процесс интеграции изменений в коде, состоит из этапов компиляции, запуска автотестов и генерации описания классов проекта. 

Для создания документации использовали инструмент автоматической документации кода Doxygen.