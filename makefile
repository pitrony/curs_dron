all: drone.exe

drone.exe: curs_dron.o
	gcc -lconio -o drone.exe curs_dron.o

curs_dron.o:  
	gcc -c --std=c17 -lconio -o curs_dron.o curs_dron.c

clean:
	del *.o 
	del drone.exe
