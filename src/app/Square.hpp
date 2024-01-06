#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <utility>

#include "SquareType.hpp"

class Square {
public:
    Square(SquareType newType, std::pair<int, int> newPos);

    SquareType getType();
    std::pair<int, int> getPos();

    std::pair<int, int> getParentPos();
    void setParentPos(std::pair<int, int> newParentPos);

    bool getVisited();
    void setVisited();


private:
    SquareType type_;
    std::pair<int, int> position_;
    std::pair<int, int> parentPosition_;
    bool isVisited_ = false;
};

#endif // SQUARE_H
