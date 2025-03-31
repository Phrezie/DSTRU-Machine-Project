#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 16 //max number of pairs and total number of pairs in set P = A x A

// game sets for Uno and Tres 
int A[] = {1, 2, 3, 4};
int UnoX[MAX_SIZE], UnoY[MAX_SIZE];
int TresX[MAX_SIZE], TresY[MAX_SIZE];
int F_X[MAX_SIZE], F_Y[MAX_SIZE];


//game flags
bool turn = true; // true = player Uno's turn, false = player Tres's turn
bool over = false; // true = game is over, false = game still ongoing
bool go = false; // true = player is ready to move, false = waiting for player input

// function to switch turns between player Uno and Tres
void nextTurn() {
    turn = !turn; // switch the turn from true to false or vice versa
}

// variables to track how many moves a player has made
int unoSize = 0;
int tresSize = 0;
int fSize = 16; // set F should have all valid pairs at first

// winning combinations (Set C)
int winningCoords[3][4][2] = {
	{{1,1}, {1,2}, {1,3}, {1,4}},  // winning combination 1
    {{1,4}, {2,3}, {3,2}, {4,1}},  // winning combination 2
    {{4,1}, {4,2}, {4,3}, {4,4}}   // winning combination 3
};

// function to initialize set F (valid moves of A x A)
void initializeF() {
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            F_X[index] = A[i];  // Store X part of the pair
            F_Y[index] = A[j];  // Store Y part of the pair
            index++;
        }
    }
}

// function to check if a pair a pair (x,y) is in a players set
int isInSet (int X[], int Y[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        if (X[i] == x && Y[i] == y) {
            return 1; // pair found
        }
    }
    return 0; // pair not found
}

// function to add a pair (x,y) to a player's set
void addToSet(int X[], int Y[], int *size, int x, int y) {
    if (*size < MAX_SIZE) {
        X[*size] = x;   // store x part of the pair
        Y[*size] = y;   // store y part of the pair
        (*size)++;		// increase the size of the set
    }
}

// function to remove a pair (x, y) from set F (make the move invalid for the other player)
void removeFromF(int x, int y, int *size) {
    for (int i = 0; i < *size; i++) {
        if (F_X[i] == x && F_Y[i] == y) {
            // Shift all elements to the left
            for (int j = i; j < *size - 1; j++) {
                F_X[j] = F_X[j + 1];
                F_Y[j] = F_Y[j + 1];
            }
            (*size)--;  // Decrease the size of F (valid moves left)
            break;
        }
    }
}

// function to check for winning combinations in a players moves
bool checkWinningCoords(int X[], int Y[], int size) {
	for(int i = 0; i < 4; i++) { 				// 4 winning combinations
		int pairCount = 0;						// number of winning combinations
		for(int j = 0; j < 4; j++) {			// each winning combination has 4 pairs
			for(int k = 0; k < size; k++) {		// compare to the player's set to the winning combinations
				if (X[k] == winningCoords[i][j][0] && Y[k] == winningCoords[i][j][1]) {
					pairCount++;
				}
			}
		}
		if(pairCount == 4) {	// if player has 4 pairs in correct combination, player wins
			return true; 		// player wins
		}
	}
	return false;				// no winning combination
}

// Function to handle a player's move 
void handleMove(int x, int y) {
    printf("Player %s trying to place move: (%d, %d)\n", turn ? "Uno" : "Tres", x, y); // Debug output to check move
	if (turn) {  	// Player Uno's turn
    	// to check if the move is valid if it's in F
		if (isInSet(F_X, F_Y, fSize, x, y)) {
            addToSet(UnoX, UnoY, &unoSize, x, y);		// add the move to player Uno's set
            removeFromF(x, y, &fSize);					// remove the move from set F
			go = true;									// uno made a move	
			nextTurn();                            		// switch turn to Tres
        } else {
            printf("Invalid move: (%d, %d), not in F.\n", x, y);
            return; 									// dont switch turns if move is invalid
        }
    } else {  // Player Tres's turn
    	// if player Tres wants to remove from Uno's set
        if (isInSet(F_X, F_Y, fSize, x, y)) {
            addToSet(TresX, TresY, &tresSize, x, y);	// add to player Tres's set
            removeFromF(x, y, &fSize);					// remove the move from Set F
            go = true;									// tres made a move	
            nextTurn();                            		// switch turn to Uno
        } else {
            printf("Invalid move: (%d, %d), not in F.\n", x, y);
            return; 									// dont switch turns if move is invalid
        }
    }
    
}

// function to check if the game is over (winning conditions)
void checkGameOver() {
    // check if Player Uno has won
    if (checkWinningCoords(UnoX, UnoY, unoSize)) {
        over = true;
        printf("Game Over! Player Uno wins!\n");
    }
    // check if Player Tres has won
    else if (checkWinningCoords(TresX, TresY, tresSize)) {
        over = true;
        printf("Game Over! Player Tres wins!\n");
    }
    // check if Player Dos wins (if no valid moves are left)
    else if (fSize == 0) {
        over = true;
        printf("Game Over! Player Dos wins!\n");
    }
}


void displayState() {
    printf("Uno's moves: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if(UnoX[i] != 0 && UnoY[i] != 0) {		// only print the valid moves
			printf("(%d, %d) ", UnoX[i], UnoY[i]);
		}
    }
    printf("\n");

    printf("Tres's moves: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (TresX[i] != 0 && TresY[i] != 0) {  	// only print the valid moves
            printf("(%d, %d) ", TresX[i], TresY[i]);
        }
    }
    printf("\n");
	
	printf("Game Over: %s\n", over ? "Yes" : "No");
    printf("It's %s's turn\n", turn ? "Player Uno" : "Player Tres");
}

int main () {
    // initialize valid moves (A x A)
	initializeF();
	
	// loop the game until game is over
    while(!over) {
        displayState();	// show the current moves and game state

        int x, y;
        printf("Enter your move (x,y): ");
        while(getchar() != '\n'); // clear input buffer
        scanf("%d, %d", &x, &y);	// get the players input

        handleMove(x, y);		// process the player's move
        checkGameOver();		// check if the game should end, else loop back to the top
        
        if (go) {
            go = false;  // Reset go to false after a valid move
        }
    }
    
    return 0;
}