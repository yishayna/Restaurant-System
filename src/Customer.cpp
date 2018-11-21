#include <iostream>
#include "../include/Customer.h"

              /* ------------------ constructors -------------------- */


            // Constructor
    Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id) {}

            // Destructor
    Customer::~Customer() {};
            // Copy Constructor
    Customer::Customer(const Customer &other):name(other.name),id(other.id) {}


                /* ------------------- functions ---------------------- */

    int Customer::getId() const { return  id; }

    std::string Customer::getName() const { return name; }

    std::vector<int> Customer::order(const std::vector<Dish> &menu){return {} ;}

    std::string Customer::toString() const {return "";}

    Customer* Customer::clone(){return nullptr;}



                /* -------------------  inheritance ---------------------- */


                                  //***VegetarianCustomer***//
              // Constructor
    VegetarianCustomer::VegetarianCustomer(std::string name, int id):Customer(name,id),orderCounter(0),orderList() {}

             // Destructor
    VegetarianCustomer::~VegetarianCustomer(){
        orderList.clear();
    }
            // Copy Constructor
    VegetarianCustomer::VegetarianCustomer(const VegetarianCustomer &other):Customer(other.getName(),other.getId()),orderCounter(other.orderCounter),orderList(other.orderList) {}



    std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
        if(orderCounter==0){
            VegetarianCustomer::makeOrderList(menu);
            orderCounter++;
        }
        if((signed)orderList.size()<2 ){
            std::vector<int> ans;
            return ans; }

        return orderList;
    }

    void VegetarianCustomer::makeOrderList(const std::vector<Dish> &menu){


        //list of all VegDish
        std::vector<Dish> veg=Customer::typeList(menu,VEG);

        //list of all non-alcoholic beverage
        std::vector<Dish> bvg=Customer::typeList(menu,BVG);
        //add the veg dish with smallest id
        if((signed)veg.size()>0 and (signed)bvg.size()>0)
            orderList.push_back(veg[0].getId());

        //get the most expensive non-alcoholic beverage in the menu
        int maxIndex = 0;
        for (int i = 0; i < (signed)bvg.size(); i++) {
            if (bvg[i].getPrice() > bvg[maxIndex].getPrice()) {
                maxIndex = i;
            }
        }
        orderList.push_back(bvg[maxIndex].getId());

        veg.clear();
        bvg.clear();
    }

    std::string VegetarianCustomer::toString() const {
        return "veg";
    }

    VegetarianCustomer*  VegetarianCustomer::clone(){
        return new VegetarianCustomer(*this);

    }



                                        //***CheapCustomer***//

            // Constructor
    CheapCustomer::CheapCustomer(std::string name, int id) :Customer(name,id),orderCounter(0),orderList(){}
            // Destructor
    CheapCustomer::~CheapCustomer(){
        orderList.clear();
    }
            // Copy Constructor

    CheapCustomer::CheapCustomer(const CheapCustomer &other):Customer(other.getName(),other.getId()),orderCounter(other.orderCounter),orderList(other.orderList) {}

    void CheapCustomer::makeOrderList(const std::vector<Dish> &menu) {
        int minIndex=0;
        for(int i=0; i<(signed)menu.size();i++){
            if(menu[i].getPrice()<menu[minIndex].getPrice()){
                minIndex=i;
            }
        }

        orderList.push_back(menu[minIndex].getId());

    }

    std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {

        std::vector<int> ans;

        if(orderCounter==0){
            CheapCustomer::makeOrderList(menu);
            ans.push_back(orderList[0]);
            orderCounter++;
        }

    return ans;
    }

    std::string CheapCustomer::toString() const { return "chp"; }

    CheapCustomer*  CheapCustomer::clone(){
        return new CheapCustomer(*this);

    }
                            //***SpicyCustomer***//

                //constructor
    SpicyCustomer::SpicyCustomer(std::string name, int id) :Customer(name,id),orderCounter(0),orderList(){}
                //destructor
    SpicyCustomer::~SpicyCustomer(){
        orderList.clear();
    }
                // Copy Constructor
    SpicyCustomer::SpicyCustomer(const SpicyCustomer &other):Customer(other.getName(),other.getId()),orderCounter(other.orderCounter),orderList(other.orderList) {}


    void SpicyCustomer::makeOrderList(const std::vector<Dish> &menu) {


        //list of all spicyDish
        std::vector<Dish> spc = Customer::typeList(menu, SPC);

        //list of all non-alcoholic beverage
        std::vector<Dish> bvg = Customer::typeList(menu, BVG);

        //get the most expensive spicy dish in the menu
        if (spc.size() > 0) {
            int maxIndex = 0;
            for (int i = 0; i < (signed) spc.size(); i++) {
                if (spc[i].getPrice() > spc[maxIndex].getPrice()) {
                    maxIndex = i;
                }
            }
            orderList.push_back(spc[maxIndex].getId());


            // get the cheapest non-alcoholic beverage
            int minIndex = 0;
            for (int i = 0; i < (signed) bvg.size(); i++) {
                if (bvg[i].getPrice() < bvg[minIndex].getPrice()) {
                    minIndex = i;
                }
            }
            orderList.push_back(bvg[minIndex].getId());
        }
    }


    std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
        std::vector<int> ans;
        if (orderCounter == 0) {
            SpicyCustomer::makeOrderList(menu);
        if((signed)orderList.size()>0)
            ans.push_back(orderList[0]);
        }
        else{
            if((signed)orderList.size()>1)
                ans.push_back(orderList[1]);
        }
        orderCounter++;
    return ans;
    }


    std::string SpicyCustomer::toString() const { return "spc"; }

    SpicyCustomer*  SpicyCustomer::clone(){
        return new SpicyCustomer(*this);

    }


                        //***Alcoholic Customer***//
            //constructor
    AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):Customer(name,id),orderCounter(0),orderList() {}
            //destructor
    AlchoholicCustomer::~AlchoholicCustomer(){
            orderList.clear();
        }
          // Copy Constructor
    AlchoholicCustomer::AlchoholicCustomer(const AlchoholicCustomer &other) :Customer(other.getName(),other.getId()),orderCounter(other.orderCounter),orderList(other.orderList) {}
    void AlchoholicCustomer::makeOrderList(const std::vector<Dish> &menu) {
        std::vector<std::pair<int, int>> list;

        for (int k = 0; k < (signed )menu.size(); ++k) {
            if (menu[k].getType() == ALC) {
                std::pair<int,int> p(menu[k].getPrice(),menu[k].getId());
                list.push_back(p);

            }
        }

        //dish id's sorted list by price
        for(int j=0; j<(signed)list.size()-1;j++) {
            for (int i = 0; i < (signed)list.size()-1-j; i++) {
                if (list[i].first > list[i + 1].first) {
                    int first = list[i].first;
                    int second = list[i].second;
                    list[i].first = list[i + 1].first;
                    list[i].second = list[i + 1].second;
                    list[i + 1].first = first;
                    list[i + 1].second = second;
                }
            }
        }

        for (int k = 0; k <(signed )list.size(); ++k) {
            orderList.push_back(list[k].second);
        }
        list.clear();
    }


    std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
        if (orderCounter == 0) {
            AlchoholicCustomer::makeOrderList(menu);
        }
        std::vector<int> ans;
        if (orderCounter < (signed)orderList.size()) {
            ans.push_back(orderList[orderCounter]); }
        orderCounter++;

        return ans;
    }

    std::string AlchoholicCustomer::toString() const { return "alc"; }

    AlchoholicCustomer*  AlchoholicCustomer::clone(){
        return new AlchoholicCustomer(*this);

    }

            /* -------------------  secondary functions  ---------------------- */


            //returns list of all Dish's of specific type
    std::vector<Dish> Customer::typeList(const std::vector<Dish> &menu, DishType type) {
        std::vector<Dish> ans;

                for (int k = 0; k < (signed)menu.size(); ++k) {
            if (menu[k].getType() == type) {
                ans.push_back(menu[k]);
            }
        }
    return  ans;
    }







