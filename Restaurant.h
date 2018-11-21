#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"
#include <fstream>
#include <sstream>
#include "Customer.h"

using namespace std;



class Restaurant{		
public:

    // Constructor
    Restaurant(const std::string &configFilePath);

    // Destructor
    virtual ~Restaurant();

    // Copy Constructor
    Restaurant(const Restaurant &other);

    // Move Constructor
    Restaurant(Restaurant &&other);

    // Copy Assignment
    Restaurant& operator=(const Restaurant &other);

    // Move Assignment
    Restaurant& operator=( Restaurant &&other);

    //empty constructor
	Restaurant();


    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();

    void clear();

private:
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string> getInputLine(std::string stream);
    int numOfCustumers;


    void copy(const Restaurant &other);
    void move(Restaurant &other);
};

#endif