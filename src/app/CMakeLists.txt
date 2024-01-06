qt_add_executable(pathfinder
    main.cpp
    PathWindow.cpp
    Square.cpp
    PathAlgo.cpp
    BfsPath.cpp
    DfsPath.cpp
)

target_link_libraries(pathfinder PRIVATE Qt6::Widgets)
