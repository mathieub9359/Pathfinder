#ifndef PATHALGO_H
#define PATHALGO_H

#include <utility>
#include <vector>

#include "Square.hpp"
#include "SquareType.hpp"

class PathAlgo {
public:
    PathAlgo(std::vector<std::vector<Square>> newSquareGrid);
    
    virtual std::pair<int, int> nextStepTraversal() = 0;
    bool isFinishedAlgo();

    std::vector<std::pair<int, int>> getPathPositionArray();

    std::pair<int, int> findStartPos();

protected:
    std::pair<int, int> findEndPos();

    std::vector<std::vector<Square>> squareGrid_;
    std::pair<int, int> endPos_;
    bool isFinished_;
};

#endif // PATHALGO_H