//Flags: -std=c++17 -Wall -Wextra -fsanitize=adress -fsanitize=undefined 

#include <iostream>
#include <string_view>
#include <deque>

#ifndef NDEBUG
    #define LOG( smth ) smth
#else
    #define LOG( smth ) if (0) smth
#endif

class Food {
public:
    Food(const size_t& current_x, const size_t& current_y, const size_t& current_buff
                    , const size_t& current_period)
        : buff(current_buff)
        , period(current_period) {
            p.x = current_x;
            p.y = current_y;
            LOG(std::cout << "$ Created food object\n");
    }
    
    ~Food(){
        LOG(std::cout << "$ Food object destructed\n");
    }    

    Food(const Food& other)
        : p(other.p)
        , buff(other.buff)
        , period(other.period) {
        LOG(std::cout << "$ Copied food object\n");            
    }

    Food(Food&& other)
        : buff(other.buff)
        , period(other.period) {
        p = std::move(other.p);
        LOG(std::cout << "$ Moved food object\n");        
    }

    Food& operator=(const Food& other) {
        if (&other == this){
            return *this;
        }

        p      = other.p;
        buff   = other.buff;
        period = other.period;

        LOG(std::cout << "$ Copy-assigment food object\n");
        return *this;
    }

    Food& operator=(Food&& other) {
        if (&other == this) {
            return *this;
        }

        buff   = other.buff;
        period = other.period;
        p      = std::move(other.p);

        LOG(std::cout << "$ Move-assigment food object\n");
        return *this;
    }

    [[nodiscard]] size_t getBuff() const {
        return buff;
    }

    [[nodiscard]] size_t getPeriod() const {
        return period;
    }

    [[nodiscard]] size_t getX() const {
        return p.x;
    }
    
    [[nodiscard]] size_t getY() const {
        return p.y;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Food& food);

private:
    struct Position {
        size_t x;
        size_t y;
    } p;

    size_t buff;
    size_t period;
};

std::ostream& operator<<(std::ostream& stream, const Food& food) {
    stream << "Food\n" << "Position: x: " << food.p.x << " y: " << food.p.y << "\nBuff: "
            << food.buff << "\nPeriod: " << food.period << '\n';
    return stream;
}

int main() {
    std::cout << "  Testing constructor\n";

    Food fastFood(1, 1, 100, 100);
    std::cout << fastFood << '\n';

    std::cout << "  Testing copy-constructor\n";

    Food fastClone = fastFood;
    std::cout << fastClone << '\n';

    std::cout << "  Testing move-constructor\n";

    Food fastNewClone = std::move(fastClone);
    std::cout << fastNewClone << '\n';

    return 0;
}
