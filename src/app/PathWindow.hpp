#ifndef PATHWINDOW_H
#define PATHWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include <QPalette>
#include <QPushButton>

#include <vector>
#include <memory>

#include "Square.hpp"
#include "SquareType.hpp"
#include "PathAlgo.hpp"
#include "BfsPath.hpp"
#include "DfsPath.hpp"

class PathWindow : public QWidget {
    Q_OBJECT

public:
    PathWindow(QWidget* parent = nullptr);
	~PathWindow() override = default;

    void recreateGrid(std::string selectedMaze, std::string selectedAlgo);

private slots:
    void handleNextButtonClick();
    void handleSkipButtonClick();

private:
    Qt::GlobalColor getSquareColor(SquareType squareType);
    std::vector<std::vector<Square>> getGridFromName(std::string gridName);
    void clearFrameGrid();
    void fillFrameGrid(std::vector<std::vector<Square>> squareGrid);
    void setFrameColor(std::pair<int, int> position, Qt::GlobalColor color);

    QGridLayout* gridLayout_;
    QPushButton* nextButton_;
    QPushButton* skipButton_;

    std::vector<std::vector<QFrame*>> frameGrid_;
    std::unique_ptr<PathAlgo> traversalAlgorithm;
    std::pair<int, int> currentFramePos;
};

#endif // PATHWINDOW_H
