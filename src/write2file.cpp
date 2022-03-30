#include "write2file.h"
#include<fstream>
#include<string>
#include<cmath>

void write2file::write_pr(const Grid &mesh, int &iter)
{
    std::fstream pr;
    std::string filename = "../results/Pressure/P_" + std::to_string(iter) + ".dat";
    pr.open(filename, std::ios::out);
    for (int i = mesh.no_y; i >= 0; --i)
    {
        for (int j = 1; j < mesh.no_x + 2; ++j)
        {
            pr << (mesh.dx*(j-1)) << " " << mesh.dy*i << " ";
            pr << (mesh.p[i][j] + mesh.p[i + 1][j] + mesh.p[i + 1][j - 1] + mesh.p[i][j - 1]) / 4;
            pr << '\n';
        }
        pr << '\n';
    }
    pr.close();
}

void write2file::write_vel(const Grid &mesh, int &iter)
{
    std::fstream vel;
    std::string filename = "../results/Velocity/vel_" + std::to_string(iter) + ".dat";
    vel.open(filename, std::ios::out);

    for (int i = mesh.no_y; i >= 0; --i)
    {
        for (int j = 0; j < mesh.no_x + 1; ++j)
        {
            vel << mesh.dx*j << " " << mesh.dy*i << " ";
            double u_node = (mesh.u[i][j] + mesh.u[i + 1][j])/2, v_node = (mesh.v[i][j] + mesh.v[i][j + 1]) / 2;
            double vel_magn = std::sqrt(u_node*u_node + v_node*v_node);
            vel << vel_magn << " ";
            vel <<  u_node << " ";
            vel <<  v_node << "\n";
        }
        vel << '\n';
    }
    vel.close();
}