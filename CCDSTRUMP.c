#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 16 //max number of pairs

// game sets for Uno and Tres 
int UnoX[MAX_SIZE], UnoY[MAX_SIZE];
int TresX[MAX_SIZE], TresY[MAX_SIZE];
int unoSize = 0, tresSize = 0;

//game flags
bool turn = true; //1 is Uno's turn, 0 is Tres's turn
bool over = false; // if 1 game is over

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
                X[j] = X[j+1];
                Y[j] = Y[j+1];
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
void handleTurn(int x, int y) {
    if (turn) { // Uno's turn
        if (isInSet(UnoX, UnoY, unoSize, x, y)) {
            printf("Uno already has this pair\n");
        } else {
            addToSet(UnoX, UnoY, &unoSize, x, y); // add pair to Uno's set
            printf("Player Uno added (%d, %d)\n", x, y);
        }
        nextTurn(); // switch to Tres 
    } else { // Tres's turn
        if (isInSet(TresX, TresY, tresSize, x, y)) {
            printf("Tres already has this pair\n");
        } else {
            addToSet(TresX, TresY, &tresSize, x, y);
        }
    }
    nextTurn();
}

int main () {
    
    
    return 0;
}