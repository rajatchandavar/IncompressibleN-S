#include <iostream>
#include <fstream>
#include <chrono>
#include "Grid.h"
#include "Boundary_Conditions.h"
#include "solver.h"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

    int nx, ny;
    double Re, dt, t_final;

    std::cout << "Transient Lid Driven Cavity Simulation\n";
    std::cout << "\nNumber of cells in x direction: ";
    std::cin >> nx;
    std::cout << "\nNumber of cells in y direction: ";
    std::cin >> ny;
    std::cout << "\nEnter Reynolds number for the lid (laminar i.e. Re < 2000): ";
    std::cin >> Re;
    std::cout << "\nFor a stable simulation, Courant number has to be less than 1. This imposes a restriction on the time step for simulation.\n";
    std::cout << "\nEnter a time step (s) less than " << (1.0 / nx) << " s: ";
    std::cin >> dt;
    std::cout << "\nEnter total time (s) simulation is to be run: ";
    std::cin >> t_final;

    start = std::chrono::system_clock::now();

    Grid domain(nx, ny);
    Boundary_Conditions BC(Re, dt, t_final);
    write2file data;
    solver solve(domain, BC, data);

    end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\nElapsed time: " << elapsed.count() / 1000.0 << " seconds" << std::endl;
}