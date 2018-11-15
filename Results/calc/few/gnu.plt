set xrange [-10:10]
set yrange [-10:10]
set xtics 2
set size square
#set terminal wxt size 800,800
unset key

set grid

#p "left.dat" w l lc 2 
#rep "right.dat" w l lc 2 
#rep "center.dat" w l lc 3

p "center_fronts.dat" w l lc 7 lw 1
rep "left_fronts.dat" w l lc 7 lw 1
rep "right_fronts.dat" w l lc 7 lw 1

rep "center_fronts (2).dat" w l lc 7 lw 1
rep "left_fronts (2).dat" w l lc 7 lw 1
rep "right_fronts (2).dat" w l lc 7 lw 1

rep "center_fronts (3).dat" w l lc 7 lw 1
rep "left_fronts (3).dat" w l lc 7 lw 1
rep "right_fronts (3).dat" w l lc 7 lw 1

#rep "point.txt" w p pt 6 ps 0.1 lc rgb "black"
#rep "point.txt" w p pt 6 ps 1.5 lc rgb "black"
#rep "point.txt" w p pt 6 ps 3.0 lc rgb "black"
#plot "center.dat" w l lc 2 lw 1.5