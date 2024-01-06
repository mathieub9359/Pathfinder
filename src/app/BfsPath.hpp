#ifndef BFSPATH_H
#define BFSPATH_H

#include "PathAlgo.hpp"

#include <queue>
#include <utility>

class BfsPath : public PathAlgo {
public:
    BfsPath(std::vector<std::vector<Square>> newSquareGrid);

    std::pair<int, int> nextStepTraversal() override;

private:
    void visitNeighbours(const int row, const int col);

    std::queue<Square> squareQueue_;
};

#endif // BFSPATH_H