#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

int numGuesses;
char guessedLetters[26];
char words[MAX_WORDS][MAX_WORD_LENGTH];
int numWords = 0;
char *secretWord;

void readDatabaseFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%19s", words[numWords]) == 1)
    {
        numWords++;
        if (numWords == MAX_WORDS) // Check if the maximum number of words has been reached
        {
            printf("Maximum number of words reached.\n");
            break;
        }
    }

    fclose(file);
}

void shuffleWords()
{
    srand(time(NULL));
    for (int i = numWords - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp[MAX_WORD_LENGTH];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

char *getRandomWord()
{
    int randomIndex = rand() % numWords;
    char *wordToGuess = malloc(MAX_WORD_LENGTH * sizeof(char)); // Allocate memory
    if (wordToGuess == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(wordToGuess, words[randomIndex]); // Copy the selected word
    return wordToGuess;
}

int initializeGame()
{
    readDatabaseFile("word_list.txt");
    shuffleWords();

    char *wordToGuess = getRandomWord();

    if (wordToGuess == NULL)
    {
        printf("Failed to get random word.\n");
        return EXIT_FAILURE;
    }

    printf("Random word selected: %s\n", wordToGuess);

    secretWord = (char *)malloc(strlen(wordToGuess) + 1);
    strcpy(secretWord, wordToGuess);

    // Initialize guessedLetters array
    memset(guessedLetters, 0, sizeof(guessedLetters));
    numGuesses = 0;

    // free(wordToGuess);
}

int main()
{
    initializeGame();

    // Rest of your code goes here

    return 0;
}
