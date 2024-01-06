#include "Square.hpp"

Square::Square(SquareType newType, std::pair<int, int> newPos) {
    type_ = newType;
    position_ = newPos;
    parentPosition_ = std::make_pair(-1, -1);
}

SquareType Square::getType() {
    return type_;
}

std::pair<int, int> Square::getPos() {
    return position_;
}

std::pair<int, int> Square::getParentPos() {
    return parentPosition_;
}

void Square::setParentPos(std::pair<int, int> newParentPos) {
    parentPosition_ = newParentPos;
}

void Square::setVisited() {
    isVisited_ = true;
}

bool Square::getVisited() {
    return isVisited_;
}
