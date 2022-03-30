set xrange[0:1]
set yrange[0:1]
filename1 = "./Pressure/P_17732.dat"
filename2 = "./Velocity/vel_17732.dat"
set size ratio 1
set palette rgb 33,13,10

set term wxt 1
set pm3d map
set title "Pressure Contour"
#set term png
#set output 'Pressure_Contour.png'
splot filename1 notitle 


set term wxt 2
set pm3d map
set title "Velocity Contour"
#set term png
#set output 'Velocity_Contour.png'
splot filename2 using 1:2:3 notitle


set term wxt 3
set title "Velocity Vectors"
#set term png
#set output 'Velocity_vectors.png'
plot filename2 using 1:2:(0.1*$4):(0.1*$5) with vectors lc -1 notitle 



