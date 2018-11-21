#ifndef TABLE_H_
#define TABLE_H_
#include <vector>
#include "Customer.h"
#include "Dish.h"

typedef std::pair<int, Dish> OrderPair;

class Table{
public:

    // Constructor
    Table(int t_capacity);

    // Destructor
    virtual ~Table();

    // Copy Constructor
    Table(const Table &other);

    // Move Constructor
    Table(Table &&other);

    // Copy Assignment
    Table& operator=(const Table &other);

    // Move Assignment
    Table& operator=( Table &&other);

    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)

    void  clear();
    void  copy(int capacity,bool open,std::vector<Customer*> customersList,std::vector<OrderPair> orderList);
    void  move(Table &other);

};


#endif