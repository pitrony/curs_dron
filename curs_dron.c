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
#include <Windows.h>
double DELAY=1.0;
HANDLE hConsole;


int main()
{
setlocale(LC_CTYPE, "");
int32_t key;
srand((unsigned int)time(NULL));
HANDLE hConsole = initializeConsole();
struct Drone_t drone =initDrone(2,2,2);
struct Drone_t drone2 =initDrone(5,5,2);
system("cls");
startMenu(&drone, &drone2);
hide_cursor(hConsole);
//pumpkin_t pumpkin = initPUMPKIN();
pumpkin_t pumpkins[num_pumpkins];
generatePUMPKIN(pumpkins,num_pumpkins);
printDrone(drone, drone2, pumpkins, hConsole);

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
		if(checkDirection(&drone2, key))
		{chageDirection(&drone2, key);}
		break;	
		case 'k'://
		case 'K'://
		key=DOWN;
		if(checkDirection(&drone2, key))
		{chageDirection(&drone2, key);}
		break;	
		case 'l': //
		case 'L'://
		key=RIGHT;
		if(checkDirection(&drone2, key))
		{chageDirection(&drone2, key);}
		break;	
		case 'i'://
		case 'I'://
		key=UP;
		if(checkDirection(&drone2, key))
		{chageDirection(&drone2, key);}
		break;	*/
		case 'Q'://81 'Q'
		case 'q'://113 'q'
		printExit(&drone, &drone2);
		save_state(&drone);
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
			generateDroneDirection(&drone2, pumpkins);
            drone = moveDir(drone,key=drone.direction,pumpkins);
			drone2 = moveDir(drone2,key=drone2.direction,pumpkins);
			if(IsCrashed(&drone)||IsCrashed(&drone2))
				{
				printf("Crashed Game Over!");
				printExit(&drone, &drone2);
				break;}
			}
	for(int i=0;i<num_pumpkins;i++){
	if(pumpkins[i].isEaten==1){
	//pumpkin = initPUMPKIN();
	generatePUMPKIN(pumpkins, num_pumpkins);
	drone = moveDir(drone, key, pumpkins);
	drone2 = moveDir(drone2, key, pumpkins);
	//printDrone(drone, pumpkin, hConsole);
	}
	}
	DELAY=drone.DELAY;
	usleep(DELAY*1000000);
//	Sleep(1);
	system("cls");
	
	printDrone(drone, drone2, pumpkins, hConsole);
	
}  //while

return 0;
}
