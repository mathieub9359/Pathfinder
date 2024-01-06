#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QPalette>
#include <QStackedWidget>
#include <QComboBox>

#include "PathWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("PathFinder");

    QVBoxLayout mainLayout(&mainWindow);

    QComboBox* mazeDropdownMenu = new QComboBox(&mainWindow);
    mazeDropdownMenu->addItem("8x8 Maze");
    mazeDropdownMenu->addItem("12x12 Maze");
    mazeDropdownMenu->addItem("3x5 Maze");
    mazeDropdownMenu->addItem("Random Maze");
    mainLayout.addWidget(mazeDropdownMenu);

    QComboBox* algoDropdownMenu = new QComboBox(&mainWindow);
    algoDropdownMenu->addItem("BFS");
    algoDropdownMenu->addItem("DFS");
    mainLayout.addWidget(algoDropdownMenu);

    QPushButton* selectionButton = new QPushButton("Go to Selected Maze and Algo", &mainWindow);
    mainLayout.addWidget(selectionButton);

    PathWindow* pathWindow = new PathWindow(&mainWindow);
    mainLayout.addWidget(pathWindow);

    QObject::connect(selectionButton, &QPushButton::clicked, [&mazeDropdownMenu, &algoDropdownMenu, &pathWindow]() {
        QString selectedMaze = mazeDropdownMenu->itemText(mazeDropdownMenu->currentIndex());
        QString selectedAlgo = algoDropdownMenu->itemText(algoDropdownMenu->currentIndex());

        pathWindow->recreateGrid(selectedMaze.toStdString(), selectedAlgo.toStdString());

        qDebug() << "Selected Maze: " << selectedMaze;
        qDebug() << "Selected Algo: " << selectedAlgo;
    });

    mainWindow.show();

    return a.exec();
}
