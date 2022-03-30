#ifndef WRITE2FILE_H
#define WRITE2FILE_H

#include "Grid.h"

class write2file{

    public:

    void write_pr(const Grid &, int &);

    void write_vel(const Grid &, int &);

};

#endif