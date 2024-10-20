//dron_move
#include "curs_dron.h"
#include <Windows.h>
#include <stdlib.h>
struct control_buttons{
 int down;
 int up;
 int left;
 int right;
} control_buttons;


/*void putPumpkin(struct pumpkins *fp)
{
char spoint[2];
gotoxy(fp->y, fp->x);
printf(" ");
fp->x=rand()%(MAX_X-1);
fp->y=rand()%(MAX_Y-2)+1;
fp->put_time = time(0);
fp->point='o';
fp->enable=1;
spoint[1]=fp->point;
gotoxy(fp->y, fp->x);
printf("%c", spoint[1]);
}
*/
extern HANDLE hConsole;
//HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

HANDLE initializeConsole(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   	if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: Unable to get console handle\n");
        exit(EXIT_FAILURE); // Exit if the handle is invalid
    }
    return hConsole;
}
 

pumpkin_t initPUMPKIN(){
pumpkin_t pumpkin;
pumpkin.x = rand() % MAX_X;
pumpkin.y = rand() % MAX_Y;
pumpkin.isEaten = 0;
return pumpkin;
}
void generatePUMPKIN(pumpkin_t pumpkins[], int num){
//pumpkin_t pumpkin;
srand(time(NULL));
for(int i=0;i<num;i++){
pumpkins[i].x = rand() % MAX_X;
pumpkins[i].y = rand() % MAX_Y;
pumpkins[i].isEaten = 0;}
//return pumpkins[];
}


struct Drone_t initDrone(int x, int y, size_t tsize){
	struct Drone_t drone;
	drone.x = x;
	drone.y = y;
	drone.tsize = tsize;
	drone.DELAY=1.0;
	drone.cart = (cart_t *) malloc (sizeof(cart_t)*MAX_DRONE_LEN);
	for (int i =0; i < tsize; ++i){
		drone.cart[i].x = x + i +1;
		drone.cart[i].y = y;
		}
		drone.count_pumpkin=0;
		drone.direction=LEFT;
	return drone;
}

void printDrone(struct Drone_t drone, struct Drone_t drone2, pumpkin_t pumpkins[], HANDLE hConsole){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}
				}
		for(int i=0;i<num_pumpkins;i++){
			if(pumpkins[i].isEaten==0) 
		{matrix[pumpkins[i].x][pumpkins[i].y] = '$';}
			}
		matrix[drone.x][drone.y] = '@';
		matrix[drone2.x][drone2.y] = '%';
			for (int i = 0; i < drone.tsize; ++i){
			matrix[drone.cart[i].x][drone.cart[i].y] = '*';
			}
			for (int i = 0; i < drone2.tsize; ++i){
			matrix[drone2.cart[i].x][drone2.cart[i].y] = '-';
			}
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
			if(matrix[i][j]=='@' ||matrix[i][j]=='*')
			apply_drone_color(&drone,hConsole);
			else if(matrix[i][j]=='%'|| matrix[i][j]=='-')
			apply_drone_color(&drone2,hConsole); // Set drone color
            printf("%c", matrix[i][j]);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
			}
				printf("\n");
				}
	}
	
Drone_t moveDir(Drone_t drone, int32_t dir, pumpkin_t pumpkins[]){
	
	for (int i = drone.tsize - 1; i > 0; i--)
		{
		drone.cart[i] = drone.cart[i-1];
		}
	drone.cart[0].x = drone.x;
	drone.cart[0].y = drone.y;
	printf("%lld", drone.tsize);
	switch (dir)
	{
	case RIGHT: //right
	drone.x = drone.x + 1;	
	if (drone.x >(MAX_X-1)){
		drone.x =  1;
		}
	break;
	case LEFT: //left
	drone.x = drone.x - 1;	
	if (drone.x < 0)
		{
		drone.x = MAX_X - 1;
		}
	break;
	case UP: //up
	drone.y = drone.y - 1;	
	if (drone.y < 0){
		drone.y = (MAX_Y - 1);
		}
	break;
case DOWN: //down
	drone.y = drone.y + 1;	
	if (drone.y >(MAX_Y-1)){
		drone.y =  1;
		}
	break;
	}
for(int i=0;i<num_pumpkins;i++){
if (drone.x == (pumpkins[i].x) && drone.y == (pumpkins[i].y))
	{
pumpkins[i].isEaten = 1;
drone.tsize++;
drone.count_pumpkin++;
drone.DELAY-=0.09;
drone.cart = realloc(drone.cart, sizeof(cart_t) * drone.tsize);
// Make sure the reallocation was successful
if (drone.cart == NULL) {
    printf("Error reallocating memory for drone cart!\n");
    exit(EXIT_FAILURE);}
    
	}
	}
	return drone;
}
void gotoxy(int x,int y)
{
    HANDLE OutputHandle;
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufInfo;
    OutputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(OutputHandle,&ScreenBufInfo);
    ScreenBufInfo.dwCursorPosition.X=x;
    ScreenBufInfo.dwCursorPosition.Y=y;
    SetConsoleCursorPosition(OutputHandle,ScreenBufInfo.dwCursorPosition);
}
void chageDirection(struct Drone_t* drone, const int32_t key)
{
for(int i=0; i<CONTROLS; i++)
	{
	
	if(key==DOWN)
		{
		drone->direction=DOWN;
		}
	else if(key==UP)
			{
			drone->direction=UP;
			}
	else if(key==RIGHT)
		{
			drone->direction=RIGHT;
			}
	else if(key==LEFT)
			{
			drone->direction=LEFT;
			}
	}
}
int checkDirection(Drone_t* drone, const int32_t key)
{
if ((drone->direction==LEFT && key!=RIGHT) || (drone->direction==RIGHT && key!=LEFT) ||
(drone->direction==DOWN && key!=UP) || (drone->direction==UP && key!=DOWN))
	{
	return 1;
	}
return 0;
}
_Bool IsCrashed(struct Drone_t *drone){
	for(size_t i=1; i<drone->tsize;i++)
	if(drone->x==drone->cart[i].x && drone->y==drone->cart[i].y)
		return 1;
	return 0;
	}
void generateDroneDirection(Drone_t *drone, pumpkin_t *pumpkin){
if ((drone->direction == LEFT || drone->direction == RIGHT)
&& drone->y == pumpkin->y){
return;
}
if ((drone->direction == LEFT || drone->direction == RIGHT)
&& drone->y != pumpkin->y){
if (pumpkin->x == drone->x){
drone->direction = UP;
}
return;
}
if ((drone->direction == UP || drone->direction == DOWN)
&& drone->x == pumpkin->x){
return;
}
if ((drone->direction == UP || drone->direction == DOWN)
&& drone->x != pumpkin->x){
if (pumpkin->y == drone->y){
drone->direction = LEFT;
}
return;
}
}
