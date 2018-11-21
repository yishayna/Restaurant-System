#ifndef DISH_H_
#define DISH_H_

#include <string>
#include <vector>

enum DishType{
    VEG, SPC, BVG, ALC
};

class Dish{
public:

    // Constructor
    Dish(int d_id, std::string d_name, int d_price, DishType d_type);

    // Destructor
    virtual ~Dish();

    // Copy Constructor
    Dish(const Dish &other);


    int getId() const;
    std::string getName() const;
    int getPrice() const;
    DishType getType() const;
    Dish getDish(const std::vector<Dish> &menu,int dish_id);
    std::string typeTostring();
private:
    const int id;
    const std::string name;
    const int price;
    const DishType type;
};


#endif