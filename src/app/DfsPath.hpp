#ifndef DFSPATH_H
#define DFSPATH_H

#include "PathAlgo.hpp"
#include <stack>

class DfsPath : public PathAlgo {
public:
    DfsPath(std::vector<std::vector<Square>> newSquareGrid);

    std::pair<int, int> nextStepTraversal() override;

private:
    void visitNeighbours(const int row, const int col);

    std::stack<Square> squareStack_;
};

#endif // DFSPATH_H