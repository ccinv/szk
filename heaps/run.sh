g++ fafa.cpp -std=c++11 -o fafa
g++ fafa.cpp -std=c++11 -O2 -o fafaO2
./fafa > fafa.csv
./fafaO2 > fafaO2.csv
gnuplot draw.plt
gnuplot drawO2.plt
rm fafa.* fafaO2.*
