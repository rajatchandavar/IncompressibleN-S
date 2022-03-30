#include "Grid.h"   
    
    Grid::Grid(int n_x, int n_y) : no_x(n_x), no_y(n_y)
    {
        dx = 1.0 / no_x;
        dy = 1.0 / no_y;
        r = dx / dy;

        pn.resize(no_y + 2, std::vector<double> (no_x + 2, 0));
        p.resize(no_y + 2, std::vector<double> (no_x + 2, 0));
        u.resize(no_y + 2, std::vector<double> (no_x + 1, 0));
        v.resize(no_y + 1, std::vector<double> (no_x + 2, 0));
        F.resize(no_y + 2, std::vector<double> (no_x + 1, 0));
        G.resize(no_y + 1, std::vector<double> (no_x + 2, 0));
};
