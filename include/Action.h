#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

//Forward declaration
class Restaurant;

class BaseAction{
public:
    BaseAction();
    virtual ~BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Restaurant& restaurant)=0;
    virtual std::string toString() const=0;
	virtual BaseAction* clone()=0;

protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
	std::string getStatusByString(const ActionStatus status) const;

private:
    std::string errorMsg;
    ActionStatus status;

};


class OpenTable : public BaseAction {
public:
    OpenTable(int id, std::vector<Customer *> &customersList);
    void act(Restaurant &restaurant);
    std::string toString() const;
	OpenTable* clone();
	~OpenTable();
	OpenTable(const OpenTable &other);
private:
	const int tableId;
	std::vector<Customer *> customers;
	std::string log;
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
	Order* clone();
	~Order();
private:
    const int tableId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Restaurant &restaurant);
    std::string toString() const;
	MoveCustomer* clone();
	~MoveCustomer();

private:
    const int srcTable;
    const int dstTable;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
	Close* clone();
	~Close() override;

private:
    const int tableId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Restaurant &restaurant);
    std::string toString() const;
	CloseAll* clone();
	~CloseAll();

private:
};


class PrintMenu : public BaseAction {
public:
    PrintMenu();
    void act(Restaurant &restaurant);
    std::string toString() const;
	PrintMenu* clone();
	~PrintMenu();
private:
};


class PrintTableStatus : public BaseAction {
public:
    PrintTableStatus(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
	PrintTableStatus* clone();
	~PrintTableStatus();
private:
    const int tableId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Restaurant &restaurant);
    std::string toString() const;
	PrintActionsLog* clone();
	~PrintActionsLog();

private:
};


class BackupRestaurant : public BaseAction {
public:
    BackupRestaurant();
    void act(Restaurant &restaurant);
    std::string toString() const;
	BackupRestaurant* clone();
	~BackupRestaurant();

private:
};


class RestoreResturant : public BaseAction {
public:
    RestoreResturant();
    void act(Restaurant &restaurant);
    std::string toString() const;
	RestoreResturant* clone();
	~RestoreResturant();


};


#endif
