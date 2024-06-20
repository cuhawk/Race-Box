// Include Header Files

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

// Define size of Box

#define ROW 10
#define COL 10


// Declare Boxes as Global

char pl_1[ROW][COL]={'_'};
char pl_2[ROW][COL]={'_'};
char res[ROW][COL]={'_'};
char pl_1_name[21],pl_2_name[21];

// Declare and Initialize Global Variables

int g=1;
int count_1=0,roll_1=0,remain_1=0,total_1=0,c_1=0,u_1=1;
int count_2=0,roll_2=0,remain_2=0,total_2=0,c_2=0,u_2=1;


///////////Starting user define Functions


////////// Printing boards for players

void printing_board(char pl[][COL]){
	int i,j;
	for(i=0;i<ROW;i++){
		printf("\t\t");
		for(j=0;j<COL;j++){
			printf("%c ",pl[i][j]);
		}
	puts(" ");
	}	
}

///////////  file opening Function

int open_file(){
	int loop;
	char rule[501];
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tWelcome To Box Race");
	printf("\n\n\t\t\t\t\t\t  Please Wait!");
	printf("\n\n\t\t\t\t\t\t   Loading");
	for(loop=0;loop<3;loop++){
		Sleep(1000);
		printf(".");
	}
	Sleep(1000);
	system("cls");
	
	//	 Game Rule
	FILE *fp;
	fp=fopen("Game Rules.txt","r");
	if(fgets(rule,500,fp)==NULL){
		printf("\n\nError!\nIt seems that some files from game were deleted.");
		return 0;
	}
	while(fgets(rule,500,fp)!=NULL){
		printf("%s",rule);
	}
	fclose(fp);
	printf("Are you ready?\n");
	Sleep(2000);
	printf("Lets play...\n");
	Sleep(2000);
	printf("Press any Key to continue...");
	getch();
	system("cls");
}


////////// Dice Handling Function

void Dice(int &roll){
	int dice;
	srand((unsigned) time(NULL));
	printf("\n\t\t\tPRESS ENTER TO ROLL DICE...");
		getch();
	do{
		dice=rand()%7;
// Condition for 6 value of dice
		if(dice==6){
			printf("\n\n\t\t\tYOU GOT %d. ",dice);
			printf("\n\t\t\tROLL AGAIN. ");
			roll=roll+dice;
			getch();
		}
		
	}while(dice==0||dice==6);
	printf("\n\n\t\t\tYOU GOT %d.\n\n",dice);
	roll=roll+dice;
}

////////// Object 'o' motion handling Function

void object_motion(int &c,int &u, int &roll, int &remain, char pl[][COL]){
	int w,v,i,x,y,j;
	for(i=c;i<u;i++){
// If value of roll is greater than the length of line then print remaining at next line
		if(roll>ROW){
			remain=roll-ROW;
			roll=ROW;
			w=c+1;
            v=u+1;
				for(x=w;x<v;x++){
					for(y=0;y<remain;y++){
						pl[x][y]='o';
					}
				}
		roll=ROW;
		}
	// Moving o to next line

		if(roll==ROW){
			roll=ROW;
			c=c+1;
			u=u+1;
		}
		for(j=0;j<roll;j++){

			pl[i][j]='o';
		}

		if(roll>=ROW){
		    roll=remain;
		}
    }
}

////////// Checking win Conditions Function

void checking(char pl[][COL],char re[][COL]){
	int i,j;
	for(i=ROW-1;i<ROW;i++){
		printf("\t\t\t");
		for(j=COL-1;j<COL;j++){
			printf("%c ",pl_2[i][j]);
			if(pl[i][j]==re[i][j]){
				g=0;
			}
		}
		puts(" ");
	}
}

////////// Player 1 Function

int player_1(void)
{
// Declare variables
	int i,j;
	system("cls");
	printf("\t\t\t*** %s TURN ***\n",pl_1_name);
	
// Rolling dice
	Dice(roll_1);
	
// Object motion
	object_motion(c_1,u_1,roll_1,remain_1,pl_1);

// Checking win condtion
	checking(pl_1,res);
	return 0;
}


////////// Player 2 Function

int player_2(void){
// Variable Declaration
	int i,j;
	system("cls");
	printf("\t\t\t*** %s TURN ***\n",pl_2_name);
	
// Rolling dice
	Dice(roll_2);
	
// Object motion
	object_motion(c_2,u_2,roll_2,remain_2,pl_2);
	
// checking win condition
	checking(pl_1,res);
	return 0;
}

////////// Game loop Function

void GameLoop(){
	while(g!=0){
	// Calling Player 1 Function	
		player_1();
		printing_board(pl_1);
		printf("Enter any key to continue...");
		getch();
		
	// Calling Player 2 Function
		player_2();
		printing_board(pl_2);
		printf("Enter any key to continue...");
		getch();
	}
}


////////// Main Function

int main(){
// Declare Local Variables	
	int draw=0;
	int i,j;

// Opening File
	open_file();
	
// Gets player name
	printf("\n\t\t\tPlayer 1 enter your name(max 20 ch): ");
	gets(pl_1_name);
	printf("\n\t\t\tPlayer 2 enter your name(max 20 ch): ");
	gets(pl_2_name);

// Print Player 1 box
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++){
			pl_1[i][j]='_';
			printf("%c ",pl_1[i][j]);
		}
		puts(" ");
	}
	
// Print Player 2 box
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++){
			pl_2[i][j]='_';
			printf("%c ",pl_2[i][j]);
		}
		puts(" ");
	}
		
// put o at last block of resultant box	
	for(i=ROW-1;i<ROW;i++){
		for(j=COL-1;j<COL;j++){
			res[i][j]='o';
		}
		puts(" ");
	}

// Game loop
	GameLoop();
	system("cls");
	printf("\n\n\t\t\tRESULTS\n\n");

// Printing Final Box of Player 1
	printf("\t\t PLAYER %s\n",pl_1_name);
	printing_board(pl_1);
	
// Printing Final Box of Player 2
	printf("\n\n\t\t PLAYER %s\n",pl_2_name);
	printing_board(pl_2);
	
// Checking for Draw	
	for(i=ROW-1;i<ROW;i++){
		for(j=COL-1;j<COL;j++){
			if(pl_1[i][j]==pl_2[i][j]){
				printf("\n\t\t\tDraw");
				draw=1;
			}
		}
	}	
	
// Printing Wining Player
	
	if(draw!=1){
		for(i=0;i<ROW;i++){
			for(j=0;j<COL;j++){
				if(pl_2[i][j]==res[i][j]){
					printf("\n\n\t\t**** %s WIN ****",pl_2_name);
				}
			}
		}

		for(i=0;i<ROW;i++){
			for(j=0;j<COL;j++){
				if(pl_1[i][j]==res[i][j]){
					printf("\n\n\t\t**** %s WIN ****",pl_1_name);
				}
			}
		}
	}
	getch();
	return 0;
}

