set datafile separator ',' 
set terminal png
set output "heapo2.png"
set title "Heaps with O2"
set xlabel 'N'
set ylabel 'Ticks'
plot "fafaO2.csv" using 1:2 title "ZkwHeap" smooth csplines linewidth 2,'' using 1:3 title "SkewHeapA" smooth csplines linewidth 2,'' using 1:4 title "SkewHeapP" smooth csplines linewidth 2,'' using 1:5 title "StdPriorityQueue" smooth csplines linewidth 2,'' using 1:6 title "PairingHeap" smooth csplines linewidth 2,'' using 1:7 title "Dummy" smooth csplines linewidth 2
