gcc -g -c --std=c11 -lconio -Wall -o curs_dron.o curs_dron.c
gcc -g -c --std=c11 -lconio -Wall -o dron_move.o dron_move.c
gcc -o dron.exe curs_dron.o dron_move.o
pause
dron.exe
pause