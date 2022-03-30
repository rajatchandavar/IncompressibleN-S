#include "solver.h"

solver::solver(Grid &mesh, Boundary_Conditions &BC, write2file &data)
    {

        BC.apply_BC(mesh);
        double inv_dx = 1 / mesh.dx;
        double inv_dy = 1 / mesh.dy;
        do
        {
            ++iter;
            time = BC.dt * iter;

            //Calculation of x-momentum coefficient mesh.F
            for (i = 1; i < mesh.no_y + 1; ++i)
            {
                for (j = 1; j < mesh.no_x; ++j)
                {
                    ue = (mesh.u[i][j] + mesh.u[i][j + 1]) * 0.5;
                    uw = (mesh.u[i][j - 1] + mesh.u[i][j]) * 0.5;
                    un = (mesh.u[i][j] + mesh.u[i + 1][j]) * 0.5;
                    us = (mesh.u[i][j] + mesh.u[i - 1][j]) * 0.5;
                    vn = (mesh.v[i][j] + mesh.v[i][j + 1]) * 0.5;
                    vs = (mesh.v[i - 1][j + 1] + mesh.v[i - 1][j]) * 0.5;

                    // Refer to eq (15) in the formulation
                    mesh.F[i][j] = -((ue * ue - uw * uw) * inv_dx + (un * vn - us * vs) * inv_dy - (1.0 / BC.Re) * ((mesh.u[i][j + 1] - 2 * mesh.u[i][j] + mesh.u[i][j - 1]) * (inv_dx * inv_dx) + (mesh.u[i + 1][j] - 2 * mesh.u[i][j] + mesh.u[i - 1][j]) * (inv_dy * inv_dy)));
                    
                }
            }

            //Calculation of y-momentum coefficient mesh.G
            for (i = 1; i < mesh.no_y; ++i)
            {
                for (j = 1; j < mesh.no_x + 1; ++j)
                {
                    vn = (mesh.v[i + 1][j] + mesh.v[i][j]) * 0.5;
                    vs = (mesh.v[i][j] + mesh.v[i - 1][j]) * 0.5;
                    ve = (mesh.v[i][j] + mesh.v[i][j + 1]) * 0.5;
                    vw = (mesh.v[i][j] + mesh.v[i][j - 1]) * 0.5;
                    ue = (mesh.u[i + 1][j] + mesh.u[i][j]) * 0.5;
                    uw = (mesh.u[i + 1][j - 1] + mesh.u[i][j - 1]) * 0.5;

                    // Refer to eq (16) in the formulation
                    mesh.G[i][j] = -((vn * vn - vs * vs) * inv_dy + (ue * ve - uw * vw) * inv_dx - (1.0 / BC.Re) * ((mesh.v[i + 1][j] - 2 * mesh.v[i][j] + mesh.v[i - 1][j]) * (inv_dy * inv_dy) + (mesh.v[i][j + 1] - 2 * mesh.v[i][j] + mesh.v[i][j - 1]) * (inv_dx * inv_dx)));

                }
            }

            //Pressure computation
            SOR sor(mesh);

            // Velocity computation

            for (i = 1; i < mesh.no_y + 1; ++i)
            {
                for (j = 1; j < mesh.no_x; ++j)
                {
                    temp = mesh.u[i][j];

                    // Refer to eq (26) in the formulation
                    mesh.u[i][j] = mesh.u[i][j] + BC.dt * mesh.F[i][j] - (BC.dt * inv_dx) * (mesh.p[i][j + 1] - mesh.p[i][j]);
                    u_error = fabs(mesh.u[i][j] - temp);
                    if (i == 1 && j == 1)
                        max_u_error = u_error;
                    else if (u_error > max_u_error)
                        max_u_error = u_error;
                }
            }

            for (i = 1; i < mesh.no_y; ++i)
            {
                for (j = 1; j < mesh.no_x + 1; ++j)
                {
                    temp = mesh.v[i][j];

                    // Refer to eq (27) in the formulation
                    mesh.v[i][j] = mesh.v[i][j] + BC.dt * mesh.G[i][j] - (BC.dt * inv_dy) * (mesh.p[i + 1][j] - mesh.p[i][j]);
                    v_error = fabs(mesh.v[i][j] - temp);

                    if (i == 1 && j == 1)
                        max_v_error = v_error;

                    else if (v_error > max_v_error)

                        max_v_error = v_error;
                }
            }

            if (max_u_error > max_v_error)
                velocity_error = max_u_error;

            else
                velocity_error = max_v_error;

            std::cout << "Iteration:" << iter << " "
                      << "Error:" << velocity_error << "\n";

            BC.apply_BC(mesh);

            data.write_pr(mesh, iter);
            data.write_vel(mesh, iter);
        } while (velocity_error > 1e-8 && time < BC.t_final);

        if (velocity_error < 1e-8)
        {
            std::cout << "Solution has Converged\n";
        }
    }
