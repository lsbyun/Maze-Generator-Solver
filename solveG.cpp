#include <ics46/factory/DynamicFactory.hpp>
#include "solveG.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, solveG, "Proj 1 Maze Solver");

solveG::solveG(){
    currentCellX = 0;
    currentCellY = 0;
}

vector<Direction> solveG::validd(const Maze& maze, MazeSolution& mazeSolution){
    vector<Direction> map;
    Direction d;
    vector<int> next{0,0};
    //loops through 4, since there are 4 possible directions
    for (int i = 0; i < 4; i++){
        //these if statement will always run in every loop but only one of the directions will pass the last if statement
        if (i == 0){
            next[0] = currentCellX;
            next[1] = currentCellY - 1;
            d = Direction::up;
        }
        if (i == 1){
            next[0] = currentCellX + 1;
            next[1] = currentCellY;
            d = Direction::right;
        }
        if (i == 2){
            next[0] = currentCellX;
            next[1] = currentCellY + 1;
            d = Direction::down;
        }
        if (i == 3){
            next[0] = currentCellX - 1;
            next[1] = currentCellY;
            d = Direction::left;
        }
        //multiple if statements to prove that the recorded direction is the only way out
        if (maze.wallExists(currentCellX, currentCellY, d) == false){
            if (next[0] < maze.getWidth()){
                if (next[0] >= 0){
                    if (next[1] < maze.getHeight()){
                        if (next[1] >= 0){
                            if (find(visited.begin(), visited.end(), next) == visited.end()){
                                map.push_back(d);
                            }
                        }
                    }
                }
            }
        }
    }
    return map;
}

void solveG::buildSol(const Maze& maze, MazeSolution& mazeSolution){
    vector<Direction> map = validd(maze, mazeSolution);
    vector<int> cell{0, 0};
    //if there are no possible direction to go to, then the solver must backtrack
    while (map.size() == 0){
        if (dimension > mazeSolution.getCells().size()){
            mazeSolution.backUp();
            currentCellX = mazeSolution.getCurrentCell().first;
            currentCellY = mazeSolution.getCurrentCell().second;
            map = validd(maze, mazeSolution);
        }
    }
    //since this is ran recursively for every cell, there will only be one value in the map vector, so we can just call it explicitly
    Direction d = map[0];
    //if statement to see if there are no walls in front of the recorded direction
    if (maze.wallExists(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, d) == false){
        mazeSolution.extend(d);
        cell[0] = mazeSolution.getCurrentCell().first;
        cell[1] = mazeSolution.getCurrentCell().second;
        visited.push_back(cell);
        currentCellX = cell[0];
        currentCellY = cell[1];
    }
}

void solveG::recursive(const Maze& maze, MazeSolution& mazeSolution){
    buildSol(maze, mazeSolution);
    //checks to see if the mazeSolution finished if not then it runs buildSol again until it does
    if (mazeSolution.isComplete()){
        return;
    }
    else{
        recursive(maze, mazeSolution);
    }
}

void solveG::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    mazeSolution.restart();
    dimension = maze.getHeight() * maze.getWidth();
    recursive(maze, mazeSolution);
}