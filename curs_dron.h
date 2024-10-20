#ifndef CURS_DRON_H
#define CURS_DRON_H
#include <stdint.h>
#include <process.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <WinCon.h>
#include <memory.h>
#define FIELD_SIZE 20
#define MAX_DRONE_LEN 50
#define FRAME_DELAY 100 // Delay per frame in milliseconds (10 FPS)
#define MAX_PUMPKIN 50 // Maximum pumpkin that can be collected
#define MAX_X 20
#define MAX_Y 20
#define num_pumpkins 5 // pumpkins in field


enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME='Q', CONTROLS=3};
typedef struct pumpkin_t{
int x;
int y;
uint8_t isEaten;
} pumpkin_t;
typedef struct cart_t{
	int x;
	int y;
	} cart_t;
typedef struct Drone_t {
    int x;
    int y; // Drone position
    int direction;
	struct control_buttons* controls;
	struct cart_t *cart;
	size_t tsize;
	double DELAY;
    int count_pumpkin; // Number of collected pumpkins
    int color; // Drone color
	int mode_auto;
} Drone_t;
pumpkin_t initPUMPKIN();
void generatePUMPKIN(pumpkin_t pumpkins[], int num);
HANDLE initializeConsole();
void hide_cursor(HANDLE hConsole); 
void set_drone_color(int color, struct Drone_t *drone);
void apply_drone_color(struct Drone_t *drone, HANDLE hConsole);
void generateDroneDirection(Drone_t *drone, pumpkin_t pumpkins[]);
void show_color_menu(struct Drone_t *drone);
struct Drone_t initDrone(int x, int y, size_t tsize);
void printDrone(struct Drone_t drone, struct Drone_t drone2, pumpkin_t pumpkins[], HANDLE hConsole);
Drone_t moveDir(Drone_t drone, int32_t dir, pumpkin_t pumpkins[]);
void gotoxy(int x,int y);
_Bool IsCrashed(struct Drone_t *drone);
void changeDirection(struct Drone_t* drone, const int32_t key);
int checkDirection(Drone_t* drone, const int32_t key);
void printExit(struct Drone_t *drone,struct Drone_t *drone2);
void save_state(Drone_t *drone /*, pumpkin_t pumpkin*/);
void load_state();
void startMenu(struct Drone_t *drone, struct Drone_t *drone2 );
#endif // CURS_DRON_H
