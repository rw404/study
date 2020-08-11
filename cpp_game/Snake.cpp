//FLAGS: -std=c++17 -Wall -Wextra -fsanitize=address -fsanitize=undefined
#include <iostream>
#include <string_view>
#include <deque>

#ifndef NDEBUG
    #define LOG( smth ) smth
#else
    #define LOG( smth ) if (0) smth
#endif

class Snake {
public:
    struct Fragment {
        int x;
        int y;
        Fragment(const int& x, const int& y)
                : x(x), y(y) {}
    };
    typedef Fragment fragment_t;

    Snake(const std::string_view& name, const std::string_view& color)
            : name(name), color(color) {
        body.emplace_back(0, 0);
        LOG(std::cout << "$ Created snake " << name << '\n');
    }

    ~Snake() {
        LOG(std::cout << "$ Snake " << name << " destructed\n");
    }

    Snake(const Snake& other)
        : name(other.name)
        , color(other.color)
        , body(other.body) {
        LOG(std::cout << "$ Copied snake\n");
    }

    Snake(Snake&& other)
            : name(other.name)
            , color(other.color) {
        body = std::move(other.body);
        LOG(std::cout << "$ Moved snake\n");
    }

    Snake& operator=(const Snake& other) {
        if (&other == this) {
            return *this;
        }

        name = other.name;
        color = other.color;
        body = other.body;

        LOG(std::cout << "$ Copy-assigned snake\n");
        return *this;
    }

    Snake& operator=(Snake&& other) {
        if (&other == this) {
            return *this;
        }

        name = other.name;
        color = other.color;
        body = std::move(other.body);

        LOG(std::cout << "$ Move-assigned snake\n");
        return *this;
    }

    void acquireFragment(const Fragment& fragment) {
        body.emplace_back(fragment);
        LOG(std::cout << "$ Length of " << name << " increased by 1 and now is " << body.size() << '\n');
    }

    void loseTail() {
        if (!body.empty()) {
            body.pop_back();
            LOG(std::cout << "$ Length of " << name << " decreased by 1 and now is " << body.size() << '\n');
        } else {
            LOG(std::cout << "$ Length of " << name << " is 0 and didn't changed\n");
        }
    }

    [[nodiscard]] std::string_view getName() const {
        return name;
    }

    [[nodiscard]] std::string_view getColor() const {
        return color;
    }

    [[nodiscard]] size_t getLength() const {
        return body.size();
    }

    friend std::ostream& operator<<(std::ostream& stream, const Snake& snake);

private:
    std::string_view name;
    std::string_view color;
    std::deque<fragment_t> body;
};

std::ostream& operator<<(std::ostream& stream, const Snake& snake) {
    stream << "Snake " << snake.name << " (color: " << snake.color << ")\n";
    for (const auto& fragment : snake.body) {
        stream << "{" << fragment.x << ", " << fragment.y << "}__";
    }
    if (!snake.body.size()) {
        stream << "no fragments";
    }
    return stream;
}

int main() {
    //-------------------------------------
    std::cout << "  Testing constructor\n";

    Snake snakeGosha("Gosha", "#123123");
    std::cout << snakeGosha << '\n';
    //-------------------------------------
    std::cout << "  Testing copy-constructor\n";

    Snake snakeClone = snakeGosha;
    std::cout << snakeClone << '\n';
    //-------------------------------------
    std::cout << "  Testing move-constructor\n";

    Snake snakeNewClone = std::move(snakeClone);
    std::cout << snakeNewClone << '\n';
    //-------------------------------------
    std::cout << "  Testing length acquisition\n";

    snakeGosha.acquireFragment(Snake::Fragment(1, 2));
    std::cout << snakeGosha << '\n';

    std::cout << "Check clone state: \n" << snakeNewClone << '\n';
    //-------------------------------------
    std::cout << "  Test loss of length\n";

    snakeNewClone.loseTail();
    std::cout << snakeNewClone << '\n';
    //-------------------------------------

    return 0;
}
