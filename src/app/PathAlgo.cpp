#include "PathAlgo.hpp"

PathAlgo::PathAlgo(std::vector<std::vector<Square>> newSquareGrid) {
    squareGrid_ = newSquareGrid;
    endPos_ = findEndPos(); 
    isFinished_ = false;
}

std::vector<std::pair<int, int>> PathAlgo::getPathPositionArray() {
    std::vector<std::pair<int, int>> pathPosArray;

    std::pair<int, int> currentPosition = endPos_;

    do {
        pathPosArray.push_back(currentPosition);
        currentPosition = squareGrid_[currentPosition.first][currentPosition.second].getParentPos();
    }
    while(!(currentPosition.first == -1 && currentPosition.second == -1));

    return pathPosArray;
}

std::pair<int, int> PathAlgo::findStartPos() {
    const int gridRows = squareGrid_.size();
    const int gridCols = squareGrid_[0].size();

    for(int row = 0; row < gridRows; row++) {
        for(int col = 0; col < gridCols; col++) {
            if(squareGrid_[row][col].getType() == StartSquare) {
                return {row, col};
            }
        }
    }

    return {-1, -1};
}

std::pair<int, int> PathAlgo::findEndPos() {
    const int gridRows = squareGrid_.size();
    const int gridCols = squareGrid_[0].size();

    for(int row = 0; row < gridRows; row++) {
        for(int col = 0; col < gridCols; col++) {
            if(squareGrid_[row][col].getType() == EndSquare) {
                return {row, col};
            }
        }
    }

    return {-1, -1};
}

bool PathAlgo::isFinishedAlgo() {
    return isFinished_;
}
