# Pathfinder

This project is a visualization software for pathfinding algorithms in the context of a maze, with a starting position, an ending position, and walls dispersed throughout. You can see the path the algorithm found, along with the squares the algorithm visited to find that path.

## Features

- **Multiple pre-built mazes**: This project includes multiple different pre-built mazes you can select to see how each algorithm behaves for different mazes. You select these mazes using a dropdown menu.

- **Multiple algorithms**: Users can select from multiple different algorithms for a given maze. These algorithms, so far, include breadth-first search and depth-first search.

## Features to come

- **Random maze**: A random maze is built from a user defined dimension (rows and columns).

- **Custom maze builder**: An option to build your own maze. A user can select the maze's dimensions, and place the walls, the starting position, and the ending position willingly inside this maze.

- **More algorithms**: More algorithms are going to be implemented in the future, such as the greedy BFS algorithm and the A* algorithm.


## Getting Started

### Build

To build the project, follow these steps:

1. Navigate to the "scripts" directory.
2. Run the build script using the following command:

```bash
./build.sh
```

### Run

To run the project, use the following steps:

1. Navigate to the "scripts" directory.
2. Execute the run script:

```bash
./run.sh
```