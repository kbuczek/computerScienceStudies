#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
int board[25] = {
	:,:,:,:,:,
	:,O,-,X,:,
	:,X,-,-,:,
	:,-,-,-,:,
	:,:,:,:,:,
	
	 0, 1, 2, 3, 4,
	 5, 6, 7, 8, 9,
	10,11,12,13,14,
	15,16,17,18,19,
	20,21,22,23,24
	
}
*/

enum { NOUGHTS, CROSSES, BORDER, EMPTY }; //different way of defining const NOUGHTS==0, CROSSES==1, BORDER==2, EMPTY==3
enum { HUMANWIN, COMPWIN, DRAW };

const int directions[4] = { 1, 5, 4, 6}; //ilość sposobów na sprawdzenie czy symbole są w rzędzie poprzez dodawanie. 1 - od lewej do prawej, 5 - od góry w dół, 4 i 6 - na ukos. (patrz numery tablicy)

const int convertTo25[9] = { //to są pola do grania z 25 pól
    6, 7, 8,
    11, 12, 13,
    16, 17, 18
};

int getNumForDir(int startSq, const int dir, const int *board, const int us) //startSq - start square, dir - direction (1,5,4,6), us - our current side. funkcja sprawdza, czy istnieją takie same znaki w danym kierunku, aż dojdzie do granicy.
{
	int found = 0;
	while(board[startSq] != BORDER)
    {		
		if(board[startSq] != us)
        {	
			break;
		}
		found++;	
		startSq += dir;
	}	
	return found;
}

int findThreeInARow(const int *board, const int ourindex, const int us) // ourindex - pole na którym obecnie się znajdujemy
{
    int dirIndex = 0; // od 0 do 3 - numer miejsca tablicy directions
	int dir = 0;
	int threeCount = 1;
	
	for(dirIndex = 0; dirIndex < 4; ++dirIndex)
    {
		dir = directions[dirIndex];
		threeCount += getNumForDir(ourindex + dir, dir, board, us); //sprawdza czy w danym kierunku, w "plusową" stronę są takie same znaki. Może zwrócić 0, 1 lub 2
		threeCount += getNumForDir(ourindex + dir * -1, dir * -1, board, us);  //sprawdza czy w danym kierunku, w "minusową" stronę są takie same znaki. Może zwrócić 0, 1 lub 2
		if(threeCount == 3) {
			break;
		}
		threeCount = 1;
	}
	return threeCount;
}


void initialiseBoard(int *board)
{
    int i;
    for(i = 0; i < 25; i++) //wsztystkie pola to granice
    {
        board[i] = BORDER;
    }

    for(i = 0; i < 9; i++) //pola do grania puste
    {
        board[convertTo25[i]] = EMPTY;
    }
}

void printBoard(const int *board)
{
    int i = 0;
    char pceChars[] = "OX|-"; //mozliwe znaki do zrobienia planszy
    printf("\n\nBoard:\n");
     for(i = 0; i < 9; i++)
    {
        if(i != 0 && i%3 == 0 ) //dzieli print planszy na 3 linijki
        {
            printf("\n\n");    
        }
        printf("%4c",pceChars[board[convertTo25[i]]]); //print znaków pceChars na planszy przy użyciu funkcji converTo25
    }
    printf("\n");
}

int hasEmpty(const int *board) //szukamy pustego miejsca na planszy
{
    int i = 0;
    int empty = 0;
    for(i = 0; i < 9; i++)
    {
        if(board[convertTo25[i]] == EMPTY)
        {
            return 1;
        }
    }
    return 0;
}

void makeMove(int *board, const int sq, const side) //sq == square
{
    board[sq] = side;
}

int getComputerMove(const int *board)
{
    int i = 0;
	int numFree = 0; //zmienna zawiera ilość wolnych miejsc na planszy
	int availableMoves[9]; //tablica zawiera numery (współrzędne) wolnych miejsc na planszy 
	int randMove = 0;	
	
	for(i = 0; i < 9; ++i) {
		if( board[convertTo25[i]] == EMPTY)
        {
			availableMoves[numFree] = convertTo25[i];		
            numFree++;	
		};
	}
	
	randMove = (rand() % numFree); //wybiera randomowe numer z ilości wolncy miejsc
	return availableMoves[randMove];
}

int getHumanMove(const int *board)
{
    char userInput[4];
    int moveOk = 0;
    int move = -1;

    while(moveOk == 0)
    {
        printf("Please enter a move from 1 to 9:");		
		fgets(userInput, 3, stdin); //wczytaj 3 litery 
		fflush(stdin); //usuń cały input, który jest większy od 3

        if(strlen(userInput) != 2) //jeżeli userInput jest większy niż 3
        {
			printf("Invalid strlen()\n");
			continue;			
		}
		
		if( sscanf(userInput, "%d", &move) != 1) //?
        {
			move = -1;
			printf("Invalid sscanf()\n");
			continue;
		}
		
		if( move < 1 || move > 9)
        {
			move = -1;
			printf("Invalid range\n");
			continue;
		}
		
		move--; // indeksy zaczynają się od zera w funkcji convertTo25
		
		if( board[convertTo25[move]]!=EMPTY)
        {
			move=-1;
			printf("Square not available\n");
			continue;
		}
		moveOk = 1;
    }

    printf("Making move %d\n", (move+1));
    return convertTo25[move];
}

void runGame()
{
    int gameOver = 0;
	int side = NOUGHTS; //kółka
	int lastMoveMade = 0;
	int board[25];
	
	initialiseBoard(&board[0]);
	printBoard(&board[0]);

    while(!gameOver)
    {
        if(side == NOUGHTS) //jezeli komputer gra kółkami
        {
            lastMoveMade = getHumanMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = CROSSES; //zmien strone na krzyzyki
        }
        else
        {
            lastMoveMade = getComputerMove(&board[0]);
            makeMove(&board[0], lastMoveMade, side);
            side = NOUGHTS; //zmien strone na kolka
            printBoard(&board[0]);
        }
               
		if(findThreeInARow(board, lastMoveMade, side ^ 1) == 3) // if three in a row exists Game is over. side^1 - zmienia stronę ???
        {
			printf("Game over!\n");
			gameOver = 1;
			if(side==NOUGHTS) //computer just moved and changed the side to noughts
            {
				printf("Computer Wins\n");
			} 
            else
            {
				printf("Human Wins\n");
			}
		}

        if(!hasEmpty(board)) //jezeli nie ma wiecej wolnych pol na planszy
        {
			printf("Game over!\n");
			gameOver = 1;
			printf("It's a draw\n");
		}
    }

    printBoard(&board[0]);
}

int main()
{
    srand(time(NULL)); //random string numbers
    runGame();
    return 0;
}
