#ifndef MAZEG_HPP
#define MAZEG_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>

using namespace std;

class mazeG: public MazeGenerator{
    public:
        mazeG();
        void generateMaze(Maze& maze) override;
        void recursive(Maze& maze);
        vector<Direction> validd(Maze& maze);
        void build(Maze& maze);
    private:
        vector<vector<int>> visited;
        int currentCellX;
        int currentCellY;
        int dimension;
        random_device device;
        default_random_engine engine{device()};
        uniform_int_distribution<int> distribution{0, 3}; //0 = up, 1 = right, 2 = down, 3 = left

};

#endif