#include "../include/Dish.h"

/* ------------------ constructors -------------------- */

                    // Constructor

Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type):id(d_id),name(d_name),price(d_price),type(d_type){}


                    // Destructor -  default destractor beacuse we did not do new in this class
Dish::~Dish() =default;

                    // Copy Constructor
Dish::Dish(const Dish &other):id(other.id),name(other.name),price(other.price),type(other.type) {}


/* ------------------- functions ---------------------- */
int Dish::getId() const {
    return  id;
}

std::string Dish::getName() const {
    return  name;
}

int Dish::getPrice() const {
    return  price;
}
DishType Dish::getType() const {
    return type;

}
std::string Dish::typeTostring(){
    if (type == VEG) {return  "VEG"; }
    else if (type == SPC) { return  "SPC"; }
    else if (type == BVG) { return "BVG"; }
    else if (type == ALC) { return "ALC"; }
    return "";
}

