gcc -g -c --std=c11 -lconio -Wall -o curs_dron.o curs_dron.c
gcc -g -c --std=c11 -lconio -Wall -o dron_move.o dron_move.c
gcc -g -c --std=c11 -lconio -Wall -o dron_varios_func.o dron_varios_func.c
gcc -o drone.exe curs_dron.o dron_move.o dron_varios_func.o
pause
dron.exe
pause