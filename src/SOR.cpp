#include "SOR.h"

    SOR::SOR(Grid &mesh)
    {
        double p_error, max_p_error = 0.0;
        double ae, ap, aw, an, as, q, omega_sor = 1.9;
        int i, j;
        do
        {
            for (i = mesh.no_y; i > 0; --i)
            {
                for (j = 1; j < mesh.no_x + 1; ++j)
                {
                    aw = 1.0;
                    ae = 1.0;
                    an = mesh.r * mesh.r;
                    as = mesh.r * mesh.r;

                    // Refer to eq (20) - RHS in the formulation
                    q = (mesh.F[i][j] - mesh.F[i][j - 1]) * mesh.dx + (mesh.G[i][j] - mesh.G[i - 1][j]) * mesh.r * mesh.dx;
                    
                    if (i == 1)
                        as = 0;
                    
                    else if (i == mesh.no_y)
                        an = 0;
                    
                    if (j == 1)
                        aw = 0;
                    
                    else if (j == mesh.no_x)
                        ae = 0;
                    
                    ap = -(aw + ae + as + an);

                    // Refer to eq (24) in the formulation
                    mesh.pn[i][j] = (1 - omega_sor) * mesh.p[i][j] + omega_sor * (q - ae * mesh.pn[i][j + 1] - aw * mesh.pn[i][j - 1] - an * mesh.pn[i + 1][j] - as * mesh.pn[i - 1][j]) / ap;
                    p_error = fabs(mesh.pn[i][j] - mesh.p[i][j]);
                    
                    if (i == mesh.no_y && j == 1)
                        max_p_error = p_error;
                    
                    else if (p_error > max_p_error)
                        max_p_error = p_error;

                }
            }
            //Update pressure
            for (i = 0; i < mesh.no_y + 2; ++i) {
                for (j = 0; j < mesh.no_x + 2; ++j) {
                    mesh.p[i][j] = mesh.pn[i][j];

                }
            }

        } while (max_p_error > 1e-6);
    }
