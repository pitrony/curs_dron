all: drone.exe

drone.exe: curs_dron.o dron_move.o dron_varios_func.o
	gcc -o drone.exe curs_dron.o dron_move.o dron_varios_func.o

curs_dron.o: curs_dron.c curs_dron.h
	gcc -c -g -Wall -lconio --std=c17 -o curs_dron.o curs_dron.c

dron_move.o: dron_move.c
	gcc -c -g -Wall -lconio --std=c17 -o dron_move.o dron_move.c

dron_varios_func.o: dron_varios_func.c
	gcc -c -g -Wall -lconio --std=c17 -o dron_varios_func.o dron_varios_func.c

dell:
	del *.o 
	del drone.exe
