#include "../include/Restaurant.h"


/* ------------------ constructors -------------------- */
                //empty constructor
    Restaurant::Restaurant():open(true),tables(),menu(),actionsLog(),numOfCustumers(0) {}

                //Constructor

    Restaurant::Restaurant(const std::string &configFilePath):open(true),tables(),menu(),actionsLog(),numOfCustumers(0) {
        string line;
        int  action=1;
        int dish_id=0;
        ifstream file (configFilePath.c_str());
        if(file.is_open()) {
            while (getline(file, line)) {  //while there is lines in the file

                if (line[0] != '#') {   //comments should be ignored

                    if (line != "") { //check if it empty line

                        //get the num of tables in Restaurant
                        if (action == 1) {
                            action++;
                        }

                            //get the num of seats in each table
                        else if (action == 2) {

                            while (line.find(",")!= std::string::npos) {
                                //cut the string to get the value of numOfSeats
                                int numOfSeats = stoul(line.substr(0, line.find(",")));
                                //create new table with the number of seats
                                tables.push_back(new Table(numOfSeats));
                                //erasing the line to find next number
                                line.erase(0, line.find(",")+1);
                            }
                            //last table
                            Table *tmp = new Table(stoul(line));
                            tables.push_back(tmp);
                            action++;
                            //get the Menu
                        } else  {
                            string dishName = line.substr(0, line.find(","));
                            line = line.substr(line.find(",") + 1);
                            string dishType = line.substr(0, line.find(","));
                            string dishPrice = line.substr(line.find(",") + 1);
                            // convert from string to DIsh type by enum
                            DishType dType;
                            if (dishType == "VEG") { dType = VEG; }
                            else if (dishType == "SPC") { dType = SPC; }
                            else if (dishType == "BVG") { dType = BVG; }
                            else if (dishType == "ALC") { dType = ALC; }
                            //creating new dish and push it to the menu
                            Dish dish(dish_id, dishName, stoul(dishPrice), dType);
                            menu.push_back(dish);
                            dish_id++;
                            action++;
                        }
                    }
                }
            }
            file.close();
        }
    }

                // Destructor
    Restaurant::~Restaurant() {
        clear();
    }

               // Copy Constructor
    Restaurant::Restaurant(const Restaurant &other) :open(true),tables(),menu(),actionsLog(),numOfCustumers(0){
        copy(other);
    }


            // Copy Assignment
    Restaurant& Restaurant::operator=(const Restaurant &other) {
        if (this != &other) {
            clear();
            copy(other);
        }
        return (*this);
    }

                // Move Constructor
    Restaurant::Restaurant(Restaurant &&other):open(true),tables(),menu(),actionsLog(),numOfCustumers(0) {
        if (this != &other) {
            move(other);
        }
    }


    // Move Assignment
    Restaurant& Restaurant::operator=(Restaurant &&other) {
        if (this != &other) {
            clear();
            move(other);
        }
        return (*this);
    }


/* ------------------- functions ---------------------- */

    void Restaurant::start() {
        this->open = true;
        cout << "Restaurant is now open!" <<endl;
        std::string str;
        std::getline(cin,str);
    while(str!="closeall"){
            std::vector<std::string> input=getInputLine(str);
            std::string firstWord=input[0];

            //open table
            if(firstWord=="open"){
                int table_Id=stoi(input[1]);
                std::vector<Customer*> ans;
                for (int i = 2; i < (signed)input.size(); ++i) {
                    string line= input[i];
                    string customerName = line.substr(0, line.find(","));
                    string customerType = line.substr(line.find(",") + 1);
                    if(customerType=="veg"){
                        VegetarianCustomer* c = new VegetarianCustomer(customerName,numOfCustumers);
                        numOfCustumers++;
                        ans.push_back(c);
                    }
                    else if(customerType=="chp"){
                        CheapCustomer* c = new CheapCustomer(customerName,numOfCustumers);
                        numOfCustumers++;
                        ans.push_back(c);
                    }
                    else if(customerType=="spc"){
                        SpicyCustomer* c= new SpicyCustomer(customerName,numOfCustumers);
                        numOfCustumers++;
                        ans.push_back(c);
                    }
                    else if(customerType=="alc"){
                        AlchoholicCustomer* c=  new AlchoholicCustomer(customerName,numOfCustumers);
                        numOfCustumers++;
                        ans.push_back(c);
                    }
                }

                OpenTable* openT= new OpenTable(table_Id,ans);
                openT->act(*this);
                actionsLog.push_back(openT);
            }
            //order
            else if(firstWord=="order"){
                int table_Id=stoi(input[1]);
                Order* orderC = new Order(table_Id);
                orderC->act(*this);
                actionsLog.push_back(orderC);
            }
            //move
            else if(firstWord=="move"){
                int table_src=stoi(input[1]);
                int table_dst=stoi(input[2]);
                int customer_id=stoi(input[3]);
                MoveCustomer* moveC = new MoveCustomer(table_src,table_dst,customer_id);
                moveC->act(*this);
                actionsLog.push_back(moveC);
            }

                //close
            else if(firstWord=="close"){
                int table_Id=stoi(input[1]);
                Close* closeT= new Close(table_Id);
                closeT->act(*this);
                actionsLog.push_back(closeT);
            }

            //menu
            else if(firstWord=="menu"){
                PrintMenu* menuT= new PrintMenu();
                menuT->act(*this);
                actionsLog.push_back(menuT);
            }
            //status
            else if(firstWord=="status"){
                int table_Id=stoi(input[1]);
                PrintTableStatus* status= new PrintTableStatus(table_Id);
                status->act(*this);
                actionsLog.push_back(status);
            }

            //log
            else if(firstWord=="log") {
                PrintActionsLog *log = new PrintActionsLog();
                log->act(*this);
                actionsLog.push_back(log);

            }

            //backup
            else if(firstWord=="backup"){
                BackupRestaurant* backupre = new BackupRestaurant();
                backupre->act(*this);
                actionsLog.push_back(backupre);
            }

            //restore
            else if(firstWord=="restore"){
                RestoreResturant* restore = new RestoreResturant();
                restore->act(*this);
                actionsLog.push_back(restore);
            }

        std::getline(cin,str);
        input.clear();
    }

    CloseAll* closeall = new CloseAll();
    closeall->act(*this);
    delete closeall;
    this->open = false;
    }




    int Restaurant::getNumOfTables() const {
        return tables.size();
    }

    Table* Restaurant::getTable(int ind) {
        if(getNumOfTables()==0)
            return nullptr;
        if(ind > (signed)(tables.size()-1) or ind <0 ){
            return nullptr;
        }
    return tables[ind];
    }



   const std::vector<BaseAction*>& Restaurant::getActionsLog() const {  // Return a reference to the history of actions
        return actionsLog;
    }

    std::vector<Dish>& Restaurant::getMenu() {
        return menu;

    }


    void Restaurant::clear() {
        for (auto c :tables) {
                delete c;
                c= nullptr;
        }
        for (auto c :actionsLog) {
                delete c;
                c= nullptr;

        }


        menu.clear();
        tables.clear();
        actionsLog.clear();
    }

    void Restaurant::copy(const Restaurant &other) {
        open=other.open;
        numOfCustumers=other.numOfCustumers;
        for(int i=0;i<(signed)other.tables.size();i++){
            Table* tempT = new Table(*other.tables[i]);
            tables.push_back(tempT);
        }
        for(int i=0;i<(signed )other.menu.size();i++){
            Dish tempd= other.menu[i];
            menu.push_back(tempd);
        }
        for(int i=0;i<(signed)other.actionsLog.size();i++){
            actionsLog.push_back(other.actionsLog[i]->clone());
        }
    }

    void Restaurant::move(Restaurant &other){
        open=other.open;
        numOfCustumers=other.numOfCustumers;

        for (auto c :other.menu){
            menu.push_back(c);
        }

        for (auto c :other.tables){
            tables.push_back(c);
        }
        for (auto c :other.actionsLog){
            actionsLog.push_back(c);
        }

        other.open =false;
        other.numOfCustumers=0;
        other.tables.clear();
        other.actionsLog.clear();
        other.menu.clear();
    }

/* -------------------  secondary functions  ---------------------- */


    std::vector<std::string> Restaurant::getInputLine(std::string stream){
        std::vector<string> ans;
        while ((signed)stream.size() > 0) {
            int first = stream.find_first_of(" ");
            string toAdd = stream.substr(0, first);
            ans.push_back(toAdd);
            if ((signed)stream.find_first_of(" ") == -1) {
                break;
            }
            stream = stream.substr(first + 1);
        }
        return ans;
    }


