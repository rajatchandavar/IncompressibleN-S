#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include "Grid.h"

//  Refer to eq (27) Boundary Conditions

class Boundary_Conditions {

public:
    double Re, dt, t_final;

    Boundary_Conditions(double , double , double );

    void apply_BC(Grid &);

};

#endif
