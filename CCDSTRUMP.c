#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 16 //max number of pairs

// game sets for Uno and Tres 
int UnoX[MAX_SIZE], UnoY[MAX_SIZE];
int TresX[MAX_SIZE], TresY[MAX_SIZE];
int F_X[MAX_SIZE], F_Y[MAX_SIZE];
int unoSize = 0, tresSize = 0, fSize = 0;

//game flags
bool turn = true; //1 is Uno's turn, 0 is Tres's turn
bool over = false; // if 1 game is over
bool go = false; // if 1 player is ready to move, false if waiting for input

// Function to check if a pair a pair (x,y) is  in a players set
int isInSet (int X[], int Y[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        if (X[i] == x && Y[i] == y) {
            return 1; // pair found
        }
    }
    return 0; // pair not found
}

// Function to add a pair (x,y) to a player's set
void addToSet(int X[], int Y[], int *size, int x, int y) {
    if (*size < MAX_SIZE) {
        X[*size] = x;   // store x
        Y[*size] = y;   // store y
        (*size)++;
    }
}

// Function to remove a pair (x,y) from a player's set
void removeFromSet(int X[], int Y[], int *size, int x, int y) {
    for (int i = 0; i < *size; i++) {
        if (X[i] == x && Y[i] == y) {
            // shift all elements to the left
            for (int j = i; j < *size - 1; j++) {
                X[j] = X[j + 1];
                Y[j] = Y[j + 1];
            }
            (*size)--; // decrease size of the set
            break;
        }
    }
}

// Function to switch turns between player Uno and Tres
void nextTurn() {
    turn = !turn; // switch the turn
}

// Function to handle a player's move 
void handleMove(int x, int y) {
    if (turn) {  // Player Uno's turn
        if (isInSet(F_X, F_Y, fSize, x, y)) {
            addToSet(UnoX, UnoY, &unoSize, x, y);
            nextTurn();
            go = !go;
        } else {
            printf("Invalid move, not in F.\n");
        }
    } else {  // Player Tres's turn
        if (isInSet(UnoX, UnoY, unoSize, x, y)) {
            removeFromSet(UnoX, UnoY, &unoSize, x, y);
            removeFromSet(TresX, TresY, &tresSize, x, y);
        } else {
            addToSet(TresX, TresY, &tresSize, x, y);
        }
        nextTurn();
    }
}

// Check for game over conditions
void checkGameOver() {
    if (unoSize == MAX_SIZE) {
        over = true;
        printf("Player Uno wins!\n");

    } else if (tresSize == MAX_SIZE) {
        over = true;
        printf("Player Tres wins!\n");
    } else if (fSize == 0) {
        over = true;
        printf("Player Dos Wins!.\n");
    }
}

void displayState() {
    printf("Uno: ");
    for (int i = 0; i < unoSize; i++) {
        printf("(%d, %d) ", UnoX[i], UnoY[i]);
    }
    printf("\n");

    printf("Tres: ");
    for (int i = 0; i < tresSize; i++) {
        printf("(%d, %d) ", TresX[i], TresY[i]);
    }
    printf("\n");

    printf("It's %s's turn\n", turn ? "Player Uno" : "Player Tres");
    printf("Game Over: %s\n", over ? "Yes" : "No");
}

int main () {
    

    while(!over) {
        displayState();

        int x, y;
        printf("Enter x and y coordinates: ");
        scanf("%d %d", &x, &y);

        handleMove(x, y);
        checkGameOver();
    }
    
    return 0;
}