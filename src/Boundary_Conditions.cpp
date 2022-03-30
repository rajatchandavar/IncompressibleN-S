#include "Boundary_Conditions.h"

    Boundary_Conditions::Boundary_Conditions(double Re, double dt, double t_final){
        this->Re = Re;
        this->dt = dt;
        this->t_final = t_final;
    }

    void Boundary_Conditions::apply_BC(Grid &mesh){
        int i, j;
        //y-velocity Boundary conditions
        for (j = 1; j < mesh.no_x + 1; ++j)
        {
            mesh.v[0][j] = 0.0;
            mesh.v[mesh.no_y][j] = 0.0;
        }

        for (i = 0; i < mesh.no_y + 1; ++i)
        {
            mesh.v[i][0] = -mesh.v[i][1];
            mesh.v[i][mesh.no_x + 1] = -mesh.v[i][mesh.no_x];
        }

        //x-velocity Boundary conditions
        for (i = 1; i < mesh.no_y + 1; ++i)
        {
            mesh.u[i][0] = 0.0;    
            mesh.u[i][mesh.no_x] = 0.0; 
        }

        for (j = 0; j < mesh.no_x + 1; ++j)
        {
            mesh.u[0][j] = -mesh.u[1][j];
            mesh.u[mesh.no_y + 1][j] = 2 - mesh.u[mesh.no_y][j];
        }

        //Pressure boundary conditions
        for (i = 1; i < mesh.no_y + 1; ++i)
        {
            mesh.pn[i][0] = mesh.pn[i][1];
            mesh.pn[i][mesh.no_x + 1] = mesh.pn[i][mesh.no_x];
        }

        for (j = 0; j < mesh.no_x + 2; ++j)
        {
            mesh.pn[0][j] = mesh.pn[1][j];
            mesh.pn[mesh.no_y + 1][j] = mesh.pn[mesh.no_y][j];
        }
    }
