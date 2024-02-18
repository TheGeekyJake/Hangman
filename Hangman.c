#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int numGuesses;
char wordToGuess[20];
char guessedLetters[26];

void initializeGame() {
 // Array of possible words
 char* words[] = {"hangman", "computer", "programming", "challenge", "coding"};

 // Seed for random word selection
 srand(time(NULL));
 
 // Select a random word from the array
 int randomIndex = rand() % 5;
 strcpy(wordToGuess, words[randomIndex]);

 // Initialize guessedLetters array
 memset(guessedLetters, 0, sizeof(guessedLetters));

 numGuesses = 0;
}

int main() {
 initializeGame();
 
 // Rest of your code goes here
 
 return 0;
}