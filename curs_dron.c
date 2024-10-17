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

#include "curs_dron.h"
//#include <stdlib.h>
//#include <time.h>
//#include <stdio.h>
#include <windows.h>

//#include <stdint.h>
//isCrush(Drone_t *drone); test for crash head and tail
//void show_color_menu(); menu choice  color 
//void set_drone_color(int color); set  color for dron
//void apply_drone_color(); set color for print dron
//void save_state(); save new score
//void load_state(); load last score
//void print_message(const char* message);
//void hide_cursor();

double DELAY=1.0;
 extern HANDLE hConsole ;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
//const int* ptr_hConsole=hConsole;
int main()
{
setlocale(LC_CTYPE, "");
int32_t key;
srand((unsigned int)time(NULL));

struct Drone_t drone =initDrone(2,2,2);
//struct Drone_t drone2 =initDrone(5,5,2);
//show_color_menu(&drone);
startMenu(&drone);
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
		/* for drone2
		case 'j':// 
		case 'J':// 
		key=LEFT;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		break;	
		case 'k'://
		case 'K'://
		key=DOWN;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		break;	
		case 'l': //
		case 'L'://
		key=RIGHT;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		break;	
		case 'i'://
		case 'I'://
		key=UP;
		if(checkDirection(&drone, key))
		{chageDirection(&drone, key);}
		break;	*/
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
		printf("w(i) a(j) s(k) d(l) - for control Q - for exit");
		break;	
			}//switch
		//drone = moveDir(drone,key, &pumpkin);
		}//if
		else {
			generateDroneDirection(&drone, &pumpkin);
            drone = moveDir(drone,key=drone.direction,&pumpkin);
			if(IsCrashed(&drone))
				{
				printf("Crashed Game Over!");
				printExit(&drone);
				break;}
			}
	if(pumpkin.isEaten==1){
	
	pumpkin = initPUMPKIN();
	drone = moveDir(drone, key, &pumpkin);
	//printDrone(drone, pumpkin);
	}
	DELAY=drone.DELAY;
	usleep(DELAY*1000000);
//	sleep(1);
	system("cls");
	
	printDrone(drone, pumpkin);
	
}  //while

return 0;
}
