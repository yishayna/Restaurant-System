#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
	// Constructor
    Customer(std::string c_name, int c_id);

	// Destructor
	virtual ~Customer();

	// Copy Constructor
     Customer(const Customer &other);


    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
    virtual  Customer* clone()=0;
private:
    const std::string name;
    const int id;
protected:
	std::vector<Dish> typeList(const std::vector<Dish> &menu, DishType type);

	};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(std::string name, int id);
	VegetarianCustomer(const VegetarianCustomer &other);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    ~VegetarianCustomer();
private:
	void makeOrderList(const std::vector<Dish> &menu);
	int orderCounter;
	std::vector<int> orderList;
    VegetarianCustomer* clone();


};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
	CheapCustomer(const CheapCustomer &other);
	std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
	~CheapCustomer();
private:
	int orderCounter;
	std::vector<int> orderList;
	void makeOrderList(const std::vector<Dish> &menu);
	CheapCustomer* clone();

};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(std::string name, int id);
	SpicyCustomer(const SpicyCustomer &other);
	std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
	~SpicyCustomer();
private:
	int orderCounter;
	std::vector<int> orderList;
	void makeOrderList(const std::vector<Dish> &menu);
    SpicyCustomer* clone();


};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(std::string name, int id);
	AlchoholicCustomer(const AlchoholicCustomer &other);
	std::vector<int> order(const std::vector<Dish> &menu);
	~AlchoholicCustomer();
    std::string toString() const;
private:
	int orderCounter;
	std::vector<int> orderList;
	void makeOrderList(const std::vector<Dish> &menu);
    AlchoholicCustomer* clone();

};


#endif