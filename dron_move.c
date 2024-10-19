//dron_move
#include "curs_dron.h"
#include <Windows.h>
#include <stdlib.h>
//#include "curs_dron.c"
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
//HANDLE hConsole = initializeConsole();
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
void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info;
    if (!GetConsoleCursorInfo(hConsole, &cursor_info)) {
        fprintf(stderr, "Error: Unable to get cursor info\n");
        return;
    }
    cursor_info.bVisible = false;
    if (!SetConsoleCursorInfo(hConsole, &cursor_info)) {
        fprintf(stderr, "Error: Unable to hide cursor\n");
    }
}



struct Drone_t initDrone(int x, int y, size_t tsize){
	struct Drone_t drone;
	drone.x = x;
	drone.y = y;
	drone.tsize = tsize;
	drone.cart = (cart_t *) malloc (sizeof(cart_t)*MAX_DRONE_LEN);
	for (int i =0; i < tsize; ++i){
		drone.cart[i].x = x + i +1;
		drone.cart[i].y = y;
		}
		drone.count_pumpkin=0;
		drone.direction=LEFT;
	return drone;
}
void apply_drone_color(struct Drone_t *drone) { // Apply the color selected for the drone
    SetConsoleTextAttribute(hConsole, drone->color);
    //SetConsoleTextAttribute(&hConsole, drone.color);
}


void printDrone(struct Drone_t drone,/*struct Drone_t drone2,*/ pumpkin_t pumpkin){
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
		//matrix[drone2.x][drone2.y] = '%';
			for (int i = 0; i < drone.tsize; ++i){
			matrix[drone.cart[i].x][drone.cart[i].y] = '*';
			}
			//for (int i = 0; i < drone2.tsize; ++i){
			//matrix[drone2.cart[i].x][drone2.cart[i].y] = '-';
			//}
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
			apply_drone_color(&drone); // Set drone color
            printf("%c", matrix[i][j]);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
			}
				printf("\n");
				}
	}

	
	
Drone_t moveDir(Drone_t drone, int32_t dir, pumpkin_t *pumpkin){
	
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
if (drone.x == (pumpkin->x) && drone.y == (pumpkin->y))
	{
pumpkin->isEaten = 1;
drone.tsize++;
drone.count_pumpkin++;
drone.DELAY-=0.09;
drone.cart = realloc(drone.cart, sizeof(cart_t) * drone.tsize);
// Make sure the reallocation was successful
if (drone.cart == NULL) {
    printf("Error reallocating memory for drone cart!\n");
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
/*void generateDroneDirection(Drone_t *drone, pumpkin_t pumpkin)
  { //ver with board
if ((drone->direction == LEFT || drone->direction == RIGHT)
&& drone->y == pumpkin.y)
{
return;
}
if ((drone->direction == LEFT || drone->direction == RIGHT)
&& drone->y != pumpkin.y)
{
if (pumpkin.x == drone->x)
{
drone->direction = UP;
}
return;
}
if ((drone->direction == UP || drone->direction == DOWN)
&& drone->x == pumpkin.x){
return;
}
if ((drone->direction == UP || drone->direction == DOWN)
&& drone->x != pumpkin.x){
if (pumpkin.y == drone->y){
drone->direction = LEFT;
}
return;
}
}
 
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(&hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
*/


/*void save_state() {
    FILE *file = fopen("drone_state.txt", "w");
    if (file) {
        // Save drone count
        fprintf(file, "%d\n", drone.count_pumpkin);
        //fprintf(file, "%d %d %d\n", drone.x, drone.y, drone.carts);
        // Save the field state
       //         }
        fclose(file);
        print_message("Game score saved!"); // Print save message at the bottom
    }
    else
    {
        print_message("Error saving game score."); // Print error message at the bottom
    }
} */

// Load the state from a file
/* void load_state() {
    FILE *file = fopen("drone_state.txt", "r");
    if (file) {
        // Load drone position and cart count fscanf(file, "%d %d %d\n", &drone.x, &drone.y, &drone.carts);
        // Load the field state
        //for (int i = 0; i < FIELD_SIZE; i++) {
          //  for (int j = 0; j < FIELD_SIZE; j++) {
            //    fscanf(file, "%d ", &field[i][j]);
           // }
        
        fscanf(file, "%d", &drone.count_pumpkin);
         
                    }
           printf("Old record %d",drone.count_pumpkin)); // Move to the next line
        }
        fclose(file);
        print_message("Game state loaded!"); // Print load message at the bottom
    } else {
        print_message("Error loading game state."); // Print error message at the bottom
    }
} */




void startMenu(struct Drone_t *drone/* , struct Drone_t *drone2*/){
	int ex=9;
	//int color_1=1;
	//int color_2=1;
	printf("********************************************\n");
	printf("*********** Game Drone *********************\n");
	printf("******* Collect pumpkins *******************\n");
	while(ex!=5)
	{
	printf("\nGame - 5\n");
	printf("\nChange colors - 6\n");
	printf("\nPrint old score - 7\n");
	scanf("%d", &ex);
	/*if(ex==7){
	printf("%d", loadscore());
	}
	*/
	if(ex==6){
	printf("\nchoice for drone 1 - 1\n");
	printf("choice for drone 2 - 2\n");
	scanf("%d", &ex);
	switch (ex)
	{
	case 1:
	show_color_menu(drone);
	//printf("Choice color for drone 1 1-5: ");
	//scanf("%d", &color_1);
	break;
	case 2:
	//show_color_menu(&drone2);
	//printf("\nChoice color for drone 2 1-5: ");
	//scanf("%d", &color_2);
	break;
	case 0:
	break ;
	default:
	printf("choice 1-2 or 0 \n");
	break;
	}	//switch
			}//if
		}//while
	
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
