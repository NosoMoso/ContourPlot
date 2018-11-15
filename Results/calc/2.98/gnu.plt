set xrange [-10:10]
set yrange [-10:10]
set xtics 2
set size square
#set terminal wxt size 800,800
unset key

set grid

p "left.dat" w l lc 2 
rep "right.dat" w l lc 2 
rep "center.dat" w l lc 3

rep "center_fronts.dat" w l lc 7 lw 1
rep "left_fronts.dat" w l lc 7 lw 1
rep "right_fronts.dat" w l lc 7 lw 1
#plot "center.dat" w l lc 2 lw 1.5