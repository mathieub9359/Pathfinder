#include "BfsPath.hpp"

BfsPath::BfsPath(std::vector<std::vector<Square>> newSquareGrid) : PathAlgo(newSquareGrid) {
    std::pair<int, int> startPos = findStartPos();

    squareGrid_[startPos.first][startPos.second].setVisited();
    squareQueue_.push(squareGrid_[startPos.first][startPos.second]);

    // This is because the view already starts with the starting position (green) as the current square
    // so the algo also needs to start at this same point
    nextStepTraversal();
};

void BfsPath::visitNeighbours(const int row, const int col) {
    // Check top
    if(row - 1 >= 0 && squareGrid_[row - 1][col].getType() != Wall && !squareGrid_[row - 1][col].getVisited()) {
        squareGrid_[row - 1][col].setVisited();
        squareGrid_[row - 1][col].setParentPos({row, col});
        squareQueue_.push(squareGrid_[row - 1][col]);
    }

    // Check bottom
    if(row + 1 <= squareGrid_.size() - 1 && squareGrid_[row + 1][col].getType() != Wall && !squareGrid_[row + 1][col].getVisited()) {
        squareGrid_[row + 1][col].setVisited();
        squareGrid_[row + 1][col].setParentPos({row, col});
        squareQueue_.push(squareGrid_[row + 1][col]);
    }

    // Check left
    if(col - 1 >= 0 && squareGrid_[row][col - 1].getType() != Wall && !squareGrid_[row][col - 1].getVisited()) {
        squareGrid_[row][col - 1].setVisited();
        squareGrid_[row][col - 1].setParentPos({row, col});
        squareQueue_.push(squareGrid_[row][col - 1]);
    }

    // Check right
    if(col + 1 <= squareGrid_[0].size() - 1 && squareGrid_[row][col + 1].getType() != Wall && !squareGrid_[row][col + 1].getVisited()) {
        squareGrid_[row][col + 1].setVisited();
        squareGrid_[row][col + 1].setParentPos({row, col});
        squareQueue_.push(squareGrid_[row][col + 1]);
    }
}

std::pair<int, int> BfsPath::nextStepTraversal() {
    if(isFinishedAlgo()) {
        return {-1, -1};
    }

    Square currSquare = squareQueue_.front();
    std::pair<int, int> currCoord = currSquare.getPos();
    int currRow = currCoord.first;
    int currCol = currCoord.second;

    squareQueue_.pop();

    visitNeighbours(currRow, currCol);

    if(endPos_.first == currRow && endPos_.second == currCol) {
        isFinished_ = true;
    }

    return currCoord;
}