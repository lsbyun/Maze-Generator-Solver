#ifndef SOLVEG_HPP
#define SOLVEG_HPP
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <vector>
using namespace std;

class solveG: public MazeSolver{
    public:
        solveG();
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
        void recursive(const Maze& maze, MazeSolution& mazeSolution);
        vector<Direction> validd(const Maze& maze, MazeSolution& mazeSolution);
        void buildSol(const Maze& maze, MazeSolution& mazeSolution);
    private:
        int currentCellX;
        int currentCellY;
        vector<vector<int>> visited;
        int dimension;
};

#endif