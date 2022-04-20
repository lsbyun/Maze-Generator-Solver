#include <ics46/factory/DynamicFactory.hpp>
#include "mazeG.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, mazeG, "Proj 1 Maze Generator");

mazeG::mazeG(){
    currentCellX = 0;
    currentCellY = 0;
}

vector<Direction> mazeG::validd(Maze& maze){
    vector<Direction> map;
    //checks to see if the next cell will be out of bounds
    if (currentCellY - 1 >= 0) {
        //checks to see if the next cell has walls in every direction and if it does it records the direction onto the vector
        if (maze.wallExists(currentCellX, currentCellY - 1, Direction::up)){
            if (maze.wallExists(currentCellX, currentCellY - 1, Direction::right)){
                if (maze.wallExists(currentCellX, currentCellY - 1, Direction::down)){
                    if (maze.wallExists(currentCellX, currentCellY - 1, Direction::left)){
                        map.push_back(Direction::up);
                    }
                }
            }
        }
    }
    if (maze.getWidth() > currentCellX + 1){
        if (maze.wallExists(currentCellX + 1, currentCellY, Direction::up)){
            if (maze.wallExists(currentCellX + 1, currentCellY, Direction::right)){
                if (maze.wallExists(currentCellX + 1, currentCellY, Direction::down)){
                    if (maze.wallExists(currentCellX + 1, currentCellY, Direction::left)){
                        map.push_back(Direction::right);
                    }
                }
            }
        }
    }
    if (maze.getHeight() > currentCellY + 1 ){
        if (maze.wallExists(currentCellX, currentCellY + 1, Direction::up)){
            if (maze.wallExists(currentCellX, currentCellY + 1, Direction::right)){
                if (maze.wallExists(currentCellX, currentCellY + 1, Direction::down)){
                    if (maze.wallExists(currentCellX, currentCellY + 1, Direction::left)){
                        map.push_back(Direction::down);
                    }
                }
            }
        }
    }
    if (currentCellX - 1 >= 0){
        if (maze.wallExists(currentCellX - 1, currentCellY, Direction::up)){
            if (maze.wallExists(currentCellX - 1, currentCellY, Direction::right)){
                if (maze.wallExists(currentCellX - 1, currentCellY, Direction::down)){
                    if (maze.wallExists(currentCellX - 1, currentCellY, Direction::left)){
                        map.push_back(Direction::left);
                    }
                }
            }
        }
    }
    return map;
}
void mazeG::build(Maze& maze){
    //calls the validd function to find any valid cells to go to
    vector<Direction> map = validd(maze);
    int count = 1;
    //if there are no more cells that are fully walled in, it backtracks
    while (map.size() == 0){
        if (dimension > visited.size()){
            currentCellX = visited[visited.size() - count][0];
            currentCellY = visited[visited.size() - count][1];
            count += 1;
            map = validd(maze);
        }
    }
    int directionNum = 0;
    //initializes the random function for while loop condition
    Direction direction;
    directionNum = distribution(engine);
    if (directionNum == 0){
        direction = Direction::up;
    }
    if (directionNum == 1){
        direction = Direction::right;
    }
    if (directionNum == 2){
        direction = Direction::down;
    }
    if (directionNum == 3){
        direction = Direction::left;
    }
    while (find(map.begin(), map.end(), direction) == map.end()){
        directionNum = distribution(engine);
        if (directionNum == 0){
            direction = Direction::up;
        }
        if (directionNum == 1){
            direction = Direction::right;
        }
        if (directionNum == 2){
            direction = Direction::down;
        }
        if (directionNum == 3){
            direction = Direction::left;
        }
    }
    //removes the wall in the recorded direction
    maze.removeWall(currentCellX, currentCellY, direction);
    //records the cell we are in as visited
    visited.push_back(vector<int>{currentCellX, currentCellY});
    //depending on the direction the x,y values will change to the next cell in the targeted direction
    if (directionNum == 0){
        currentCellY -= 1;
    }
    if (directionNum == 1){
        currentCellX += 1;
    }
    if (directionNum == 2){
        currentCellY += 1;
    }
    if (directionNum == 3){
        currentCellX -= 1;
    }

}

void mazeG::recursive(Maze& maze){
    build(maze);
    //the number of cells visited must equal the area of the maze for it to be finished, if it doesnt equal the area then it will
    //run recursively until it does
    if (visited.size() == dimension){
        return;
    }
    else{
        recursive(maze);
    }
}

void mazeG::generateMaze(Maze& maze){
    maze.addAllWalls();
    vector<int> init{currentCellX, currentCellY};
    dimension = maze.getHeight() * maze.getWidth();
    visited.push_back(init);
    recursive(maze);
}
