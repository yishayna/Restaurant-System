#include <iostream>
#include "../include/Table.h"
#

    /* ------------------ constructors -------------------- */

                 // Constructor

    Table::Table(int t_capacity):capacity(t_capacity), open(false),customersList(),orderList(){
    }

                // Destructor
    Table::~Table() {
        this->closeTable();
        clear();
    }

              // Copy Constructor
    Table::Table(const Table &other) :capacity(0),open(true),   customersList(),orderList(){
        copy(other.capacity,other.open,other.customersList,other.orderList);
    }

            // Move Constructor
    Table::Table(Table &&other) :capacity(0),open(true),   customersList(),orderList(){
        if (this != &other) {
            move(other);
        }
    }

            // Copy Assignment
    Table& Table::operator=(const Table &other) {
        if (this != &other) {
            clear();
            copy(other.capacity, other.open, other.customersList, other.orderList);
        }
        return *this;
    }


            // Move Assignment
    Table& Table::operator=(Table &&other) {
        if (this != &other) {
            clear();
            move(other);
        }
        return *this;
    }

    /* ------------------- functions ---------------------- */
    void Table::clear() {
        for(auto c :customersList){
                delete c;
        }
        for(auto c :orderList){
            delete( &c);
        }
        customersList.clear();
        orderList.clear();
    }


    void Table::copy(int capacity,bool open,std::vector<Customer*> customersList,std::vector<OrderPair> orderList)  {
        this->capacity=capacity;
        this->open=open;
        for (int i = 0; i < (signed )orderList.size(); ++i) {
            Dish dish(orderList[i].second);
            std::pair<int,Dish> pair(orderList[i].first,dish);
            this->orderList.push_back(pair);
            }
        for (int i = 0; i < (signed)customersList.size(); ++i) {
            this->customersList.push_back((customersList[i])-> clone());
            }
    }

    void Table::move(Table &other) {
        this->capacity=other.capacity;
        this->open=other.open;
        orderList=std::move(other.orderList);
        customersList=std::move(other.customersList);
        other.capacity=0;
        other.open= false;
        other.orderList.clear();
        other.customersList.clear();
    }

    int Table::getCapacity() const {
        return  capacity;
    }

    void Table::addCustomer(Customer *customer) {
        customersList.push_back(customer);
    }

    void Table::removeCustomer(int id) {
        for(int i=0; i<(signed)customersList.size(); i++){
            if(customersList[i]->getId()==id){
                customersList.erase(customersList.begin()+i) ; //delete &
                break;
            }
        }
    }

    Customer* Table::getCustomer(int id){
        for(int i=0; i<(signed)customersList.size(); i++){
            if(customersList[i]->getId()==id){
                return  customersList[i] ;
            }
        }
        return nullptr;
    }

    std::vector<Customer*>& Table::getCustomers(){
        return customersList;
    }

    std::vector<OrderPair>& Table::getOrders(){
        return orderList;
    }

    void Table::order(const std::vector<Dish> &menu) {
        if((signed )menu.size()>0){
            for(auto c:customersList) {
                std::vector<int> orderL(c->order(menu));
                for (int j = 0; j < (signed) orderL.size(); ++j) {
                    std::pair<int, Dish> pair(c->getId(), menu[orderL[j]]);
                    orderList.push_back(pair);
                    std::cout << c->getName() + " ordered " + menu[orderL[j]].getName() << std::endl;
                }
            }
        }
    }

    void Table::openTable(){
        this->open=true;
    }

    void Table::closeTable(){
        this->open= false;
        for (auto c:customersList){
            delete c;
            c= nullptr;
        }
        customersList.clear();
        orderList.clear();
    }

    int Table::getBill(){
        int sum=0;
        for (int i = 0; i < (signed)orderList.size(); ++i) {
           sum=sum+orderList[i].second.getPrice();
        }
        return sum;
    }

    bool Table::isOpen(){
        return open;
    }




