//
#include "curs_dron.h"
extern HANDLE hConsole;
// Load the state from a file
void load_state() {
    int carts=0;
    FILE *file = fopen("drone_state.txt", "r");
    if (file) 
    {
        // Load drone position and cart count fscanf(file, "%d %d %d\n", &drone.x, &drone.y, &drone.carts);
        // Load the field state
        //for (int i = 0; i < FIELD_SIZE; i++) {
          //  for (int j = 0; j < FIELD_SIZE; j++) {
            //    fscanf(file, "%d ", &field[i][j]);
           // }
        
        fscanf(file, "%d", &carts);
        printf("\nOld record %d ", carts); // Move to the next line
        fclose(file);
        //printf("Game state loaded!"); // Print load message at the bottom
        }
    else {
        printf("Error loading game score"); // Print error message at the bottom
    }
} 
void startMenu(struct Drone_t *drone, struct Drone_t *drone2){
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
    int ex=9;
    int ch_auto=1;
	while(ex!=5)
	{
	system("cls");
	printf("********************************************\n");
	printf("*********** Game Drone *********************\n");
	printf("******* Collect pumpkins *******************\n");
	printf("\nGame - 5\n");
	printf("\nChange colors - 6\n");
	printf("\nPrint old score - 7\n");
    printf("\nDrone2 choice auto  - 8\n");
	scanf("%d", &ex);
	if(ex==7)
    {
	system("cls");
    load_state();
    printf("\n");
    system("pause");
	}
	if(ex==8){
	printf("\nchoice for drone 2 - 1 auto, 0 - manual \n");
	scanf("%d", &ch_auto);
    if(ch_auto==0)
    drone2->mode_auto=0;// manual
    else drone2->mode_auto=1;
    }
	if(ex==6){
	printf("\nchoice for drone 1 - 1\n");
	printf("choice for drone 2 - 2\n");
	scanf("%d", &ex);
	switch (ex)
	{
	case 1:
	show_color_menu(drone);
	break;
	case 2:
	show_color_menu(drone2);
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
// Set the drone's color by the user's choice
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
    set_drone_color(choice, drone);
}
// Set the drone color by user selection
void apply_drone_color(struct Drone_t *drone, HANDLE hConsole) { // Apply the color selected for the drone
    SetConsoleTextAttribute(hConsole, drone->color);
    //SetConsoleTextAttribute(&hConsole, drone.color);
}
void hide_cursor(HANDLE hConsole) {
	
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
void printExit(struct Drone_t *drone, struct Drone_t *drone2)
{
gotoxy(MAX_Y /2, MAX_X /2 - 3);
printf("\nYour LEVEL drone is %d", drone->count_pumpkin);
printf("\nYour LEVEL drone 2 is %d", drone2->count_pumpkin);
printf("\n");
save_state(drone);
system("pause");
system("cls");
}
void save_state(Drone_t *drone /*, pumpkin_t pumpkin*/) {
    FILE *file = fopen("drone_state.txt", "w");
    if (file) {
        // Save drone count
        fprintf(file, "%d\n", drone->count_pumpkin);
        //fprintf(file, "%d %d %d\n", drone.x, drone.y, drone.carts);
        // Save the field state
       //         }
        fclose(file);
        printf("Game score saved!"); // Print save message at the bottom
    }
    else
    {
        printf("Error saving game score."); // Print error message at the bottom
    }
} 


