#include "PathWindow.hpp"

#include <QDebug>

#include <iostream>

PathWindow::PathWindow(QWidget *parent) : QWidget(parent) {
    QWidget *centralWidget = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QWidget *gridContainer = new QWidget;
    gridLayout_ = new QGridLayout(gridContainer);

    std::vector<std::vector<Square>> squareGrid = getGridFromName("8x8 Maze");

    traversalAlgorithm = std::make_unique<BfsPath>(squareGrid);
    currentFramePos = traversalAlgorithm->findStartPos();

    fillFrameGrid(squareGrid);

    gridContainer->setFixedSize(400, 400);

    mainLayout->addWidget(gridContainer);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignTop);

    nextButton_ = new QPushButton("Next", centralWidget);
    nextButton_->setFixedSize(150, 50);
    connect(nextButton_, &QPushButton::clicked, this, &PathWindow::handleNextButtonClick);
    buttonLayout->addWidget(nextButton_);

    skipButton_ = new QPushButton("Skip", centralWidget);
    skipButton_->setFixedSize(150, 50);
    connect(skipButton_, &QPushButton::clicked, this, &PathWindow::handleSkipButtonClick);
    buttonLayout->addWidget(skipButton_);

    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}

void PathWindow::recreateGrid(std::string selectedMaze, std::string selectedAlgo) {
    std::vector<std::vector<Square>> squareGrid = getGridFromName(selectedMaze);

    if(selectedAlgo == "BFS") {
        traversalAlgorithm = std::make_unique<BfsPath>(squareGrid);
    }
    
    else if(selectedAlgo == "DFS") {
        traversalAlgorithm = std::make_unique<DfsPath>(squareGrid);
    }

    // else {
    //     traversalAlgorithm = std::make_unique<BfsPath>(squareGrid);
    // }

    clearFrameGrid();
    fillFrameGrid(squareGrid);

    currentFramePos = traversalAlgorithm->findStartPos();
    nextButton_->setEnabled(true);
    skipButton_->setEnabled(true);

    // Adjusting the gridContainer size based on rows and columns (keeps square size and gap size between squares constant)
    gridLayout_->parentWidget()->setFixedSize(50 * frameGrid_[0].size(), 50 * frameGrid_.size());
}

void PathWindow::fillFrameGrid(std::vector<std::vector<Square>> squareGrid) {
    frameGrid_.resize(squareGrid.size(), std::vector<QFrame*>(squareGrid[0].size(), 0));

    for (int row = 0; row < squareGrid.size(); ++row) {
        for (int col = 0; col < squareGrid[0].size(); ++col) {
            frameGrid_[row][col] = new QFrame;
            QFrame* frame = frameGrid_[row][col];

            setFrameColor({row, col}, getSquareColor(squareGrid[row][col].getType()));
            frame->setAutoFillBackground(true);

            // why is this even an attribute wtf? maybe for the grid positioning nvm... idk...
            gridLayout_->addWidget(frame, row, col);
        }
    }
}


void PathWindow::clearFrameGrid() {
    for (int row = 0; row < frameGrid_.size(); ++row) {
        for (int col = 0; col < frameGrid_[0].size(); ++col) {
            gridLayout_->removeWidget(gridLayout_->itemAtPosition(row, col)->widget());

            delete frameGrid_[row][col];
            frameGrid_[row][col] = nullptr;
        }
    }

    frameGrid_.clear();
}

std::vector<std::vector<Square>> PathWindow::getGridFromName(std::string gridName) {
    std::vector<std::vector<Square>> squareGrid;
    
    if(gridName == "8x8 Maze") {
        squareGrid = {
            {{StartSquare, {0,0}}, {FreeSquare, {0,1}}, {FreeSquare, {0,2}}, {Wall, {0,3}}, {FreeSquare, {0,4}}, {Wall, {0,5}}, {FreeSquare, {0,6}}, {EndSquare, {0,7}}},
            {{Wall, {1,0}}, {Wall, {1,1}}, {FreeSquare, {1,2}}, {Wall, {1,3}}, {Wall, {1,4}}, {FreeSquare, {1,5}}, {Wall, {1,6}}, {FreeSquare, {1,7}}},
            {{FreeSquare, {2,0}}, {FreeSquare, {2,1}}, {FreeSquare, {2,2}}, {Wall, {2,3}}, {Wall, {2,4}}, {Wall, {2,5}}, {FreeSquare, {2,6}}, {FreeSquare, {2,7}}},
            {{Wall, {3,0}}, {Wall, {3,1}}, {FreeSquare, {3,2}}, {FreeSquare, {3,3}}, {FreeSquare, {3,4}}, {FreeSquare, {3,5}}, {FreeSquare, {3,6}}, {Wall, {3,7}}},
            {{FreeSquare, {4,0}}, {FreeSquare, {4,1}}, {Wall, {4,2}}, {Wall, {4,3}}, {Wall, {4,4}}, {FreeSquare, {4,5}}, {FreeSquare, {4,6}}, {Wall, {4,7}}},
            {{FreeSquare, {5,0}}, {FreeSquare, {5,1}}, {FreeSquare, {5,2}}, {FreeSquare, {5,3}}, {FreeSquare, {5,4}}, {FreeSquare, {5,5}}, {FreeSquare, {5,6}}, {FreeSquare, {5,7}}},
            {{Wall, {6,0}}, {Wall, {6,1}}, {Wall, {6,2}}, {FreeSquare, {6,3}}, {Wall, {6,4}}, {Wall, {6,5}}, {Wall, {6,6}}, {Wall, {6,7}}},
            {{Wall, {7,0}}, {Wall, {7,1}}, {FreeSquare, {7,2}}, {FreeSquare, {7,3}}, {Wall, {7,4}}, {Wall, {7,5}}, {Wall, {7,6}}, {Wall, {7,7}}},
        };
    }
    else if(gridName == "12x12 Maze") {
        squareGrid = {
            {{FreeSquare, {0,0}}, {FreeSquare, {0,1}}, {FreeSquare, {0,2}}, {Wall, {0,3}}, {FreeSquare, {0,4}}, {Wall, {0,5}}, {FreeSquare, {0,6}}, {FreeSquare, {0,7}}, {Wall, {0,8}}, {FreeSquare, {0,9}}, {Wall, {0,10}}, {Wall, {0,11}}},
            {{FreeSquare, {1,0}}, {Wall, {1,1}}, {FreeSquare, {1,2}}, {Wall, {1,3}}, {Wall, {1,4}}, {FreeSquare, {1,5}}, {Wall, {1,6}}, {FreeSquare, {1,7}}, {FreeSquare, {1,8}}, {Wall, {1,9}}, {Wall, {1,10}}, {FreeSquare, {1,11}}},
            {{FreeSquare, {2,0}}, {FreeSquare, {2,1}}, {FreeSquare, {2,2}}, {Wall, {2,3}}, {Wall, {2,4}}, {Wall, {2,5}}, {FreeSquare, {2,6}}, {FreeSquare, {2,7}}, {Wall, {2,8}}, {FreeSquare, {2,9}}, {Wall, {2,10}}, {FreeSquare, {2,11}}},
            {{Wall, {3,0}}, {Wall, {3,1}}, {FreeSquare, {3,2}}, {FreeSquare, {3,3}}, {FreeSquare, {3,4}}, {FreeSquare, {3,5}}, {FreeSquare, {3,6}}, {Wall, {3,7}}, {FreeSquare, {3,8}}, {FreeSquare, {3,9}}, {FreeSquare, {3,10}}, {Wall, {3,11}}},
            {{FreeSquare, {4,0}}, {FreeSquare, {4,1}}, {Wall, {4,2}}, {FreeSquare, {4,3}}, {StartSquare, {4,4}}, {FreeSquare, {4,5}}, {Wall, {4,6}}, {Wall, {4,7}}, {Wall, {4,8}}, {FreeSquare, {4,9}}, {Wall, {4,10}}, {Wall, {4,11}}},
            {{FreeSquare, {5,0}}, {FreeSquare, {5,1}}, {FreeSquare, {5,2}}, {FreeSquare, {5,3}}, {FreeSquare, {5,4}}, {FreeSquare, {5,5}}, {FreeSquare, {5,6}}, {FreeSquare, {5,7}}, {FreeSquare, {5,8}}, {FreeSquare, {5,9}}, {Wall, {5,10}}, {FreeSquare, {5,11}}},
            {{Wall, {6,0}}, {FreeSquare, {6,1}}, {FreeSquare, {6,2}}, {FreeSquare, {6,3}}, {Wall, {6,4}}, {FreeSquare, {6,5}}, {Wall, {6,6}}, {FreeSquare, {6,7}}, {Wall, {6,8}}, {Wall, {6,9}}, {FreeSquare, {6,10}}, {Wall, {6,11}}},
            {{Wall, {7,0}}, {FreeSquare, {7,1}}, {Wall, {7,2}}, {FreeSquare, {7,3}}, {FreeSquare, {7,4}}, {FreeSquare, {7,5}}, {Wall, {7,6}}, {Wall, {7,7}}, {FreeSquare, {7,8}}, {FreeSquare, {7,9}}, {Wall, {7,10}}, {Wall, {7,11}}},
            {{FreeSquare, {8,0}}, {Wall, {8,1}}, {EndSquare, {8,2}}, {FreeSquare, {8,3}}, {FreeSquare, {8,4}}, {FreeSquare, {8,5}}, {FreeSquare, {8,6}}, {FreeSquare, {8,7}}, {FreeSquare, {8,8}}, {FreeSquare, {8,9}}, {Wall, {8,10}}, {FreeSquare, {8,11}}},
            {{FreeSquare, {9,0}}, {FreeSquare, {9,1}}, {Wall, {9,2}}, {FreeSquare, {9,3}}, {Wall, {9,4}}, {FreeSquare, {9,5}}, {Wall, {9,6}}, {FreeSquare, {9,7}}, {Wall, {9,8}}, {FreeSquare, {9,9}}, {FreeSquare, {9,10}}, {Wall, {9,11}}},
            {{FreeSquare, {10,0}}, {FreeSquare, {10,1}}, {FreeSquare, {10,2}}, {FreeSquare, {10,3}}, {FreeSquare, {10,4}}, {FreeSquare, {10,5}}, {FreeSquare, {10,6}}, {Wall, {10,7}}, {FreeSquare, {10,8}}, {Wall, {10,9}}, {FreeSquare, {10,10}}, {Wall, {10,11}}},
            {{Wall, {11,0}}, {Wall, {11,1}}, {Wall, {11,2}}, {FreeSquare, {11,3}}, {Wall, {11,4}}, {Wall, {11,5}}, {Wall, {11,6}}, {Wall, {11,7}}, {Wall, {11,8}}, {Wall, {11,9}}, {Wall, {11,10}}, {Wall, {11,11}}}
        };
    }
    else if(gridName == "3x5 Maze") {
        squareGrid = {
            {{StartSquare, {0,0}}, {FreeSquare, {0,1}}, {FreeSquare, {0,2}}, {FreeSquare, {0,3}}, {FreeSquare, {0,4}}}, 
            {{Wall, {1,0}}, {Wall, {1,1}}, {FreeSquare, {1,2}}, {Wall, {1,3}}, {FreeSquare, {1,4}}},
            {{EndSquare, {2,0}}, {FreeSquare, {2,1}}, {FreeSquare, {2,2}}, {FreeSquare, {2,3}}, {FreeSquare, {2,4}}}
        };
    }

    return squareGrid;
}



Qt::GlobalColor PathWindow::getSquareColor(SquareType squareType) {
    if(squareType == Wall) {
        return Qt::black;
    }
    else if(squareType == FreeSquare) {
        return Qt::gray;
    }
    else if(squareType == StartSquare) {
        return Qt::green;
    }
    else if(squareType == EndSquare) {
        return Qt::red;
    }
    
    return Qt::blue;
}

void PathWindow::setFrameColor(std::pair<int, int> position, Qt::GlobalColor color) {
    QPalette palette = frameGrid_[position.first][position.second]->palette();
    palette.setColor(QPalette::Window, color);
    frameGrid_[position.first][position.second]->setPalette(palette);
}


void PathWindow::handleNextButtonClick() {
    // call an algo method that returns the new current square, put the new curr square as green,
    // and the old curr square as darkGray
    qDebug() << currentFramePos.first << ", " << currentFramePos.second << "\n";

    setFrameColor(currentFramePos, Qt::yellow);

    currentFramePos = traversalAlgorithm->nextStepTraversal();

    qDebug() << currentFramePos;

    setFrameColor(currentFramePos, Qt::green);

    if(traversalAlgorithm->isFinishedAlgo()) {
        nextButton_->setEnabled(false);
        skipButton_->setEnabled(false);

        std::vector<std::pair<int, int>> pathPosArray = traversalAlgorithm->getPathPositionArray();

        for(auto&& framePosition : pathPosArray) {
            setFrameColor(framePosition, Qt::magenta);
        }
    }
}

void PathWindow::handleSkipButtonClick() {
    while(!traversalAlgorithm->isFinishedAlgo()) {
        setFrameColor(currentFramePos, Qt::yellow);
        currentFramePos = traversalAlgorithm->nextStepTraversal();
        setFrameColor(currentFramePos, Qt::green);
    }

    nextButton_->setEnabled(false);
    skipButton_->setEnabled(false);

    std::vector<std::pair<int, int>> pathPosArray = traversalAlgorithm->getPathPositionArray();

    for(auto&& framePosition : pathPosArray) {
        setFrameColor(framePosition, Qt::magenta);
    }
}
