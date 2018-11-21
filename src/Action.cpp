
#include "../include/Action.h"
#include "../include/Restaurant.h"
extern Restaurant* backup;

/* ------------------ constructors -------------------- */


    BaseAction::BaseAction():errorMsg("Error: "),status() {return;}

            /* ------------------- functions ---------------------- */


    ActionStatus BaseAction::getStatus() const {
        return status;
    }

    void BaseAction::complete() {
        status=COMPLETED;
    }

    void BaseAction::error(std::string errorMsg) {
        status=ERROR;
        this->errorMsg=this->errorMsg+errorMsg;
        std::cout<<this->errorMsg<<std::endl;
    }

    std::string BaseAction::getErrorMsg() const {
        return this->errorMsg;
    }
     BaseAction* BaseAction::clone(){return nullptr;}

     std::string BaseAction::getStatusByString(const ActionStatus status) const {
        if(status==COMPLETED)
            return "Completed";
        if(status==PENDING)
            return "Pending";
        if(status==ERROR)
            return getErrorMsg();
        return "";
    }
    BaseAction::~BaseAction() {}



            /* -------------------  inheritance ---------------------- */



//Open Table

    //constractor
    OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList),log() {}

    //destractor
    OpenTable::~OpenTable() {

        customers.clear();
        for (int i = 0; i <(signed)customers.size() ; ++i) {
            customers[i]=nullptr;

        }
    }

    //copy constractor
    OpenTable::OpenTable(const OpenTable &other):tableId(other.tableId),customers(other.customers),log(other.log){}



    void OpenTable::act(Restaurant &restaurant) {
        Table *table = restaurant.getTable(tableId);
        log = "open ";
        log = log + (std::to_string(tableId) + " ");
        for (auto c:customers) {
            log = log + (c->getName() + "," + c->toString() + " ");
        }
        if (table == nullptr or table->getCapacity() < (signed) customers.size() or table->isOpen()) {
            error("Table does not exist or is already open");
            for (auto c :customers) {
                delete (c); }

            customers.clear();
        }
        else {
            table->openTable();
            for (int i = 0; i < (signed) customers.size(); i++) {
                table->addCustomer(customers[i]);
            }
            complete();
        }

        log = log + getStatusByString(getStatus());
        }



    std::string OpenTable::toString() const {
        return log;
    }
    OpenTable*  OpenTable::clone() {
        return new OpenTable(*this);
    }



//Order
    Order::Order(int id):tableId(id) {}
    void Order::act(Restaurant &restaurant) {
        Table* table = restaurant.getTable(tableId);
        if(table== nullptr)
            error("Table does not exist or is not open");
        else if(!table->isOpen())
            error("Table does not exist or is not open");
        else {
            table->order(restaurant.getMenu());
            complete();
        }
    }

    std::string Order::toString() const {
        std::string log = "order ";
        log.append(std::to_string(tableId)+" ");
        log.append(getStatusByString(getStatus()));
        return log;
    }
    Order*  Order::clone() {
        return new Order(*this);
    }

    Order::~Order() =default;

//move Customer
    MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTable(src),dstTable(dst),id(customerId) {}

    void MoveCustomer::act(Restaurant &restaurant) {
        Table* tablesrc = restaurant.getTable(srcTable);
        Table* tabledst = restaurant.getTable(dstTable);
        if(tabledst== nullptr or tablesrc== nullptr or !tablesrc->isOpen() or !tabledst->isOpen() or  tablesrc->getCustomer(id)== nullptr or tabledst->getCapacity()==(signed)tabledst->getCustomers().size())
            error("Cannot move customer");
        else{

            std::vector<OrderPair> tableSrcOrderstmp;
            for(auto c: tablesrc->getOrders()) {
                OrderPair temp = OrderPair(c.first, c.second);
                if (c.first != id)
                    tableSrcOrderstmp.push_back(temp);
                else {
                    tabledst->getOrders().push_back(temp);
                    }
                }
            tabledst->addCustomer(tablesrc->getCustomer(id));
            tablesrc->getOrders().clear();
            tablesrc->removeCustomer(id);
            for (auto c:tableSrcOrderstmp){
                tablesrc->getOrders().push_back(c); }
            if(tablesrc->getCustomers().size()==0)
                tablesrc->closeTable();
            complete();
        }
    }

    std::string MoveCustomer::toString() const {
        std::string log = "move ";
        log.append(std::to_string(srcTable)+" ");
        log.append(std::to_string(dstTable)+" ");
        log.append(std::to_string(id)+" ");
        log.append(getStatusByString(getStatus()));
        return log;
    }
    MoveCustomer*  MoveCustomer::clone() {
        return new MoveCustomer(*this);
    }
    MoveCustomer::~MoveCustomer() =default;


//Close
    Close::Close(int id):tableId (id){}

    void Close::act(Restaurant &restaurant) {
        if(restaurant.getTable(tableId)== nullptr){
            error("Table does not exist or is not open");}
        else if (restaurant.getTable(tableId)->isOpen()){
            std::cout << "Table "+ std::to_string(tableId)+" was closed. Bill "+std::to_string(restaurant.getTable(tableId)->getBill())+"NIS"<<endl;
            restaurant.getTable(tableId)->closeTable();
            complete();}
        else{
            error("Table does not exist or is not open");
        }
    }

    std::string Close::toString() const {
        std::string log = "close ";
        log.append(std::to_string(tableId));

        if(this->getStatus()==ERROR)
          log.append(" Error: Table does not exist or is not open");
        else
          log.append(" Completed");

        return log;
    }

    Close*  Close::clone() {
        return new Close(*this);
    }


    Close::~Close() =default;

//ClostAll
    CloseAll::CloseAll() {}

    void CloseAll::act(Restaurant &restaurant) {
        for(int i=0;i<restaurant.getNumOfTables();i++){
            if(restaurant.getTable(i)->isOpen()) {
                std::cout << "Table " + std::to_string(i) + " was closed. Bill " + std::to_string(restaurant.getTable(i)->getBill()) + "NIS" << endl;
            }
        }
        complete();
    }

    CloseAll *CloseAll::clone() {
        return new CloseAll(*this);
    }
    CloseAll::~CloseAll() =default;


std::string CloseAll::toString() const { return ""; }


//Print Menu
    PrintMenu::PrintMenu() {}

    void PrintMenu::act(Restaurant &restaurant) {
        for(int i=0;i<(signed)restaurant.getMenu().size();i++){
           Dish dish = restaurant.getMenu()[i];
            std::string price  = std::to_string(restaurant.getMenu()[i].getPrice())+"NIS";
            std::cout << dish.getName()+" "+dish.typeTostring()+" "+std::to_string(dish.getPrice())+"NIS" <<endl;
        }
        complete();
    }

    std::string PrintMenu::toString() const { return "menu "+ getStatusByString(getStatus()); }
    PrintMenu*  PrintMenu::clone() {
        return new PrintMenu(*this);
    }
    PrintMenu::~PrintMenu() =default;



//Print Table Status

        // Constructor
    PrintTableStatus::PrintTableStatus(int id):tableId(id) {}
        // Destructor
    PrintTableStatus::~PrintTableStatus() =default;

    void PrintTableStatus::act(Restaurant &restaurant) {

            if(restaurant.getTable(tableId)->isOpen()){
            std::cout << "Table " + std::to_string(tableId) + " status: open" << endl;
            std::cout << "Customers:" << endl;
            for (auto c :restaurant.getTable(tableId)->getCustomers()) {
                std::cout << std::to_string(c->getId()) + " " + c->getName() << endl;
            }
            std::cout << "Orders:" << endl;
            for (int i = 0; i < (signed) restaurant.getTable(tableId)->getOrders().size(); i++) {
                std::string dishname = restaurant.getTable(tableId)->getOrders()[i].second.getName();
                std::string customerid = std::to_string(restaurant.getTable(tableId)->getOrders()[i].first);
                std::string dishprice =
                        std::to_string(restaurant.getTable(tableId)->getOrders()[i].second.getPrice()) + "NIS";
                std::cout << dishname + " " + dishprice + " " + customerid << endl;
            }
            std::cout << "Current Bill: " + std::to_string(restaurant.getTable(tableId)->getBill()) + "NIS" << endl;
             }
        else{
            std::cout <<"Table "+std::to_string(tableId)+" status: closed" <<endl;

        }
        complete();
    }

    std::string PrintTableStatus::toString() const { return "status "+std::to_string(tableId)+" "+getStatusByString(getStatus());   }

    PrintTableStatus*  PrintTableStatus::clone() {
        return new PrintTableStatus(*this);
    }





//Print Action Log
    PrintActionsLog::PrintActionsLog() {}

    void PrintActionsLog::act(Restaurant &restaurant) {
        for(auto c:restaurant.getActionsLog())
            std::cout << c->toString()<<endl;
        complete();
    }

    std::string PrintActionsLog::toString() const { return "log "+ getStatusByString(getStatus());}

    PrintActionsLog*  PrintActionsLog::clone() {
        return new PrintActionsLog(*this);
    }
    PrintActionsLog::~PrintActionsLog()  =default;




//BackUP Restaurant
    BackupRestaurant::BackupRestaurant() {}

    void BackupRestaurant::act(Restaurant &restaurant) {
        if (backup == nullptr) {
            backup = new Restaurant(restaurant);
        }
        else {
            *backup = restaurant;

        }
        complete();
    }

    std::string BackupRestaurant::toString() const {return "backup "+getStatusByString(getStatus()); }

    BackupRestaurant*  BackupRestaurant::clone() {
        return new BackupRestaurant(*this);
    }
    BackupRestaurant::~BackupRestaurant() =default;




//Restore Resturant
    RestoreResturant::RestoreResturant() {

    }

    void RestoreResturant::act(Restaurant &restaurant) {
        if(backup== nullptr){
            error("No backup available");
        }
        else{
            restaurant=*backup;
            complete();
        }
    }

    std::string RestoreResturant::toString() const { return "restore "+ getStatusByString(getStatus());}

    RestoreResturant*  RestoreResturant::clone() {
        return new RestoreResturant(*this);
    }

    RestoreResturant::~RestoreResturant() =default;


