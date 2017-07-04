@echo off
rm brute.exe
rm gen.exe
rm my.exe
g++ -std=c++11 brute.cpp -o brute
g++ -std=c++11 gen.cpp -o gen
g++ -std=c++11 E.cpp -o my
:loop
    gen > data.in
    my < data.in > a.out
    brute < data.in > b.out
    fc a.out b.out
if not errorlevel 1 goto loop
pause
goto loop
