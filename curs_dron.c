//curs dron
//initHead(struct snake *head), initTail(struct tail_t t[],
//size_t size) , init(struct snake *head, struct tail *tail, size_t size).
//timeout(SPEED)
//go(struct snake *head).
//goTail(struct snake_t *head).
//void changeDirection(snake_t* snake, const int32_t key).
//getmaxyx(stdscr, max_y, max_x) вычисления размера терминального окна используется макрос библиотеки ncurses
//В случае, когда координата превышает максимальное значение, происходит её
/*обнуление.
Если координата достигает отрицательного значения, то ей присваивается
соответствующее максимальное значение max_y, max_x. initFood(struct food f[])
и haveEat(struct snake *head, struct food f[ ]):
for(size_t i=0; i<MAX_FOOD_SIZE; i++) происходит проверка
наличия еды и совпадения координат head->x == f[i].x и head->y ==
f[i].y.
В случае выполнения условий enable=0 и возвращается единица.
Увеличение хвоста — отвечает функция addTail(&snake).
В структуре head параметр длины tsize увеличивается на единицу. head->tsize++
putFood(food,
SEED_NUMBER), putFoodSeed(struct food *fp).
Если через какое-то время(FOOD_EXPIRE_SECONDS) точка устаревает, или же она
была съедена(food[i].enable==0), то происходит её повторная отрисовка и
обновление времени — refreshFood(food, SEED_NUMBER).
void printLevel(struct snake *head) позволяет считать количество урожая
(1 собранный урожай – 1 уровень).
Проверка того, столкнулась ли голова с хвостом, происходит при помощи функции
логической функции isCrush(snake_t * snake).
При завершении игры выводится финальный результат void printExit(struct snake
*head)
*/
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
//#include <System.Windows.Forms.Cursor.h>
#define FIELD_SIZE 20
#define MAX_DRONE_LEN 10
#define FRAME_DELAY 100 // Delay per frame in milliseconds (10 FPS)
#define MAX_PUMPKIN 10 // Maximum pumpkin that can be collected
#define MAX_PUMPKIN_SIZE 10
#define MAX_X 20
#define MAX_Y 20


struct control_buttons
{
 int down;
 int up;
 int left;
 int right;
}control_buttons;
typedef struct pumpkin_t{
int x;
int y;
uint8_t isEaten;
} pumpkin_t;

/*struct pumpkins
{
int x;
int y;
time_t put_time;
char point;
uint8_t enable;
} pumpkins[MAX_PUMPKIN_SIZE];
*/
pumpkin_t initPUMPKIN(){
pumpkin_t pumpkin;
pumpkin.x = rand() % MAX_X;
pumpkin.y = rand() % MAX_Y;
pumpkin.isEaten = 0;
return pumpkin;
}
typedef struct tail_t{
	int x;
	int y;
	} tail_t;
typedef struct Drone_t {
    int x;
    int y; // Drone position
    int direction;
	struct control_buttons* controls;
	struct tail_t * tail;
	size_t tsize;
    int count_pumpkin; // Number of collected pumpkins
    int color; // Drone color
} Drone_t;


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

	
//int field[FIELD_SIZE][FIELD_SIZE];
//Drone_t drone;

// Global console handle
HANDLE hConsole;
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME='Q', CONTROLS=3};
struct control_buttons default_controls[CONTROLS]={{'s','w','a','d'} , {'S','W','A','D'}}; 
// Function prototypes
//void initialize_field();
//void display_field();
//void show_color_menu();
//void set_drone_color(int color);
//void apply_drone_color();
//void save_state();
//void load_state();
//bool check_victory();
//void empty_carts();
//void print_message(const char* message);
void hide_cursor();

void set_drone_color(int color, struct Drone_t *drone) {
    switch (color) {
        case 1: drone->color = FOREGROUND_RED | FOREGROUND_INTENSITY; break;   // Red
        case 2: drone->color = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break; // Green
        case 3: drone->color = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;  // Blue
        case 4: drone->color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break; // Yellow
        case 5: drone->color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break; // White
        default: drone->color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default white
    }
}

void show_color_menu(struct Drone_t *drone) {
    int choice;
    printf("Choose a color for the drone:\n");
    printf("1. Red\n");
    printf("2. Green\n");
    printf("3. Blue\n");
    printf("4. Yellow\n");
    printf("5. White\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);
    
    // Set the drone's color based on the user's choice
    set_drone_color(choice, drone);
}

// Set the drone color based on user selection
struct Drone_t initDrone(int x, int y, size_t tsize){
	struct Drone_t drone;
	drone.x = x;
	drone.y = y;
	drone.tsize = tsize;
	drone.tail = (tail_t *) malloc (sizeof(tail_t)*MAX_DRONE_LEN);
	for (int i =0; i < tsize; ++i){
		drone.tail[i].x = x + i +1;
		drone.tail[i].y = y;
		}
		drone.count_pumpkin=0;
		drone.direction=LEFT;
	return drone;
}
void apply_drone_color(struct Drone_t drone) { // Apply the color selected for the drone
    SetConsoleTextAttribute(hConsole, drone.color);
}


void printDrone(struct Drone_t drone, pumpkin_t pumpkin){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}
				}
		if(pumpkin.isEaten==0) 
		{matrix[pumpkin.x][pumpkin.y] = '$';}
		matrix[drone.x][drone.y] = '@';
			for (int i = 0; i < drone.tsize; ++i){
			matrix[drone.tail[i].x][drone.tail[i].y] = '*';
			}
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
			apply_drone_color(drone); // Set drone color
            printf("%c", matrix[i][j]);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
			}
				printf("\n");
				}
	}

	
	
Drone_t moveDir(Drone_t drone, int32_t dir, pumpkin_t *pumpkin){
	
	for (int i = drone.tsize - 1; i > 0; i--)
		{
		drone.tail[i] = drone.tail[i-1];
		}
	drone.tail[0].x = drone.x;
	drone.tail[0].y = drone.y;
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
if (drone.x == (pumpkin->x) && drone.y == (pumpkin->y))
	{
pumpkin->isEaten = 1;
drone.tsize++;
drone.count_pumpkin++;
drone.tail = realloc(drone.tail, sizeof(tail_t) * drone.tsize);
// Make sure the reallocation was successful
if (drone.tail == NULL) {
    printf("Error reallocating memory for drone tail!\n");
    exit(EXIT_FAILURE);}
    
//pumpkin->x = rand() % MAX_X;
  //  pumpkin->y = rand() % MAX_Y;
    //pumpkin->isEaten = 0; 

// *pumpkin = initPUMPKIN();
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

void printExit(struct Drone_t *drone)
{
gotoxy(MAX_Y /2, MAX_X /2 - 3);
printf("\nYour LEVEL is %d", drone->count_pumpkin);
printf("\n");
system("pause");
system("cls");
}
/*void generateSnakeDirection(snake_t *snake, struct food f){
if ((snake->direction == LEFT || snake->direction == RIGHT)
&& snake->y == food.y){
return;
}
if ((snake->direction == LEFT || snake->direction == RIGHT)
&& snake->y != food.y){
if (food.x == snake->x){
snake->direction = UP;
}
return;
}
if ((snake->direction == UP || snake->direction == DOWN)
&& snake->x == food.x){
return;
}
if ((snake->direction == UP || snake->direction == DOWN)
&& snake->x != food.x){
if (food.y == snake->y){
snake->direction = LEFT;
}
return;
}
}
*/
/*void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}*/
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main()
{
setlocale(LC_CTYPE, "");
int32_t key;
srand((unsigned int)time(NULL));
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct Drone_t drone =initDrone(2,2,2);
show_color_menu(&drone);
hide_cursor();
pumpkin_t pumpkin = initPUMPKIN();
printDrone(drone, pumpkin);

	
while(1)
		{
		
		if(_kbhit())
		 {
        char tmp=(_getch());    
		switch (tmp) 
			{
		case 'a'://97 
		case 'A'://65 
		key=LEFT;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		
		break;	
		case 's'://115 's'
		case 'S'://83 'S'
		key=DOWN;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		
		break;	
		case 'd': //100 'd'
		case 'D'://68 'D'
		key=RIGHT;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		
		break;	
		case 'w'://119 'w'
		case 'W'://87 'W'
		key=UP;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		break;	
		
		case 'Q'://81 'Q'
		case 'q'://113 'q'
		printExit(&drone);
		printf("\nBay!");
		return 0;
		break;
		case 'P':// 'P'
		case 'p':// 'p'
		printf("\nGame in PAUSE\n\n");
		system("pause");
		break;
		
		default:
		printf("w a s d - for control Q - for exit");
		break;	
			}
		//drone = moveDir(drone,key, &pumpkin);
			}
		else {
			drone = moveDir(drone,key=drone.direction,&pumpkin);
			}
	if(pumpkin.isEaten==1){
	
	pumpkin = initPUMPKIN();
	drone = moveDir(drone, key, &pumpkin);
	//printDrone(drone, pumpkin);
	}
		sleep(1);
	system("cls");
	
	printDrone(drone, pumpkin);
	
}  //while

return 0;
}
