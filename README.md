# Bonus_AP_NS

This is an Incompressible Navier stokes equation solver. A lid driven cavity is simulated in the code. 
Firstly, the momentum equations are solved and results are used in the compute pressure (Successive Over-relaxation used). The updated pressure is used to further update the velocity (Predictor Corrector Method). Non-dimensional formulation is done.
For more details on formulation, please refer to the bonus_AP_NS_Formulation.pdf in 'docs'.

Procedure to build the code:
(1) Please ensure 'build' and 'results' directories exist. 
(2) Go to the build directory. When running for the first time, please clear the build folder.
(3) execute cmake ../src --> make --> ./incompressible

Results:
The results from the simulation is written in the 'results' folder. The pressure and velocity data is written into dat files for each time step. The values are parsed according (x_cord, y_cord, pressure_value) for pressure and (x_cord, y_cord, vel_value, x-vel, y-vel) for velocity.

Procedure to view Results
(1) Please clear any existing data from results/Pressure and results/Velocity.
(2) Make sure gnuplot is installed on the system.
(3) Go to the results directory. Open gnuplot terminal and execute load 'plot.gnu'

![alt text](<./docs/Geometry.png>) 

