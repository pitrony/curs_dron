//curs dron
#include "curs_dron.h"
#include <Windows.h>
double DELAY=1.0;
HANDLE hConsole;

int main()
{
setlocale(LC_CTYPE, "");
int32_t key,key2;
srand((unsigned int)time(NULL));
HANDLE hConsole = initializeConsole();
struct Drone_t drone =initDrone(2,2,2);
struct Drone_t drone2 =initDrone(5,2,2);
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
		//if(checkDirection(&drone, key))
		//{changeDirection(&drone, key);}
		break;	
		case 's'://115 's'
		case 'S'://83 'S'
		key=DOWN;
		//if(checkDirection(&drone, key))
		//{changeDirection(&drone, key);}
		break;	
		case 'd': //100 'd'
		case 'D'://68 'D'
		key=RIGHT;
		if(checkDirection(&drone, key))
		{changeDirection(&drone, key);}
		break;	
		case 'w'://119 'w'
		case 'W'://87 'W'
		key=UP;
		if(checkDirection(&drone, key))
		{changeDirection(&drone, key);}
		break;	
		//for drone2
		case 'j':// 
		case 'J':// 
		key2=LEFT;
		if(checkDirection(&drone2, key2))
		{changeDirection(&drone2, key2);}
		break;	
		case 'k'://
		case 'K'://
		key2=DOWN;
		if(checkDirection(&drone2, key2))
		{changeDirection(&drone2, key2);}
		break;	
		case 'l': //
		case 'L'://
		key2=RIGHT;
		if(checkDirection(&drone2, key2))
		{changeDirection(&drone2, key2);}
		break;	
		case 'i'://
		case 'I'://
		key2=UP;
		if(checkDirection(&drone2, key2))
		{changeDirection(&drone2, key2);}
		break;	
		case 'Q'://81 'Q'
		case 'q'://113 'q'
		printExit(&drone, &drone2);
		save_state(&drone);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
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
		
		}//if
		else {
			if(checkDirection(&drone, key))
			{
			changeDirection(&drone, key);
			drone = moveDir(drone,key=drone.direction,pumpkins);
			}
		
			if(drone2.mode_auto)
			{generateDroneDirection(&drone2, pumpkins);
			drone2 = moveDir(drone2,drone2.direction,pumpkins);}
			else drone2= moveDir(drone2,key2,pumpkins);
			if(IsCrashed(&drone)||IsCrashed(&drone2))
				{
				printf("Crashed!");
				system("pause");
				//printf("Crashed, Game Over!");
				//printExit(&drone, &drone2);
				//break;
				}
			}
	for(int i=0;i<num_pumpkins;i++)
	{
	if(pumpkins[i].isEaten==1){
		generatePUMPKIN(pumpkins, num_pumpkins);
		drone = moveDir(drone, key, pumpkins);
		drone2 = moveDir(drone2, key2, pumpkins);
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
