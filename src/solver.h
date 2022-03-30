/**********************************************************************************
   
   The solver is built for incompressible fluid and laminar flow. 
   For a given time iteration, the momentum coefficients F and G are computed.
   These are used to then compute the pressure. The pressure is computed using 
   the Successive over-relaxation method. The computed pressure is further used
   to compute velocity. 
   The maximum velocity error is the difference between velocities in current and 
   previous iteration for a given node with maximum being taken across all nodes.
   Maximum velocity_error is a measure of convergence of the problem.

************************************************************************************/

#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <cmath>
#include "Grid.h"
#include "Boundary_Conditions.h"
#include "SOR.h"
#include "write2file.h"

class solver
{

public:
    double ue, uw, un, us, ve, vw, vn, vs, temp, time;
    double max_u_error, max_v_error, u_error, v_error, velocity_error;
    int i, j, iter = 0;
    
    solver(Grid &, Boundary_Conditions &, write2file &);

};

#endif
