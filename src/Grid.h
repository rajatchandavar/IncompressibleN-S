#ifndef GRID_H
#define GRID_H

#include <vector>
#include <array>

class Grid
{

public:
    double dx, dy, r;
    const int no_x, no_y;

    std::vector<std::vector<double>> pn, p, u, v, F, G;

    Grid(int , int);
};

#endif
