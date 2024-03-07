#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

int numGuesses;
char wordToGuess[20];
char guessedLetters[26];
char words[MAX_WORDS][MAX_WORD_LENGTH];
int numWords = 0;

void readDatabaseFile(const char* filename) {
 FILE* file = fopen(filename, "r");
 if (file == NULL) {
 printf("Error opening file.\n");
 return;
 }

 while (fscanf(file, "%s", words[numWords]) == 1) {
 numWords++;
 }

 fclose(file);
}

void shuffleWords() {
 srand(time(NULL));
 for (int i = numWords - 1; i > 0; i--) {
 int j = rand() % (i + 1);
 char temp[MAX_WORD_LENGTH];
 strcpy(temp, words[i]);
 strcpy(words[i], words[j]);
 strcpy(words[j], temp);
 }
}

char* getRandomWord() {
 int randomIndex = rand() % numWords;
 return words[randomIndex];
}

void initializeGame() {
    readDatabaseFile("database.txt");
    shuffleWords();
    char* wordToGuess = getRandomWord();
    
    // Initialize guessedLetters array
    memset(guessedLetters, 0, sizeof(guessedLetters));
    numGuesses = 0;
}

int main() {
 initializeGame();
 
 // Rest of your code goes here
 
 return 0;
}