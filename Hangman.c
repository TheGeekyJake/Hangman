#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

    // printf("Random word selected: %s\n", wordToGuess);

    secretWord = (char *)malloc(strlen(wordToGuess) + 1);
    strcpy(secretWord, wordToGuess);

    // Initialize guessedLetters array
    memset(guessedLetters, 0, sizeof(guessedLetters));
    numGuesses = 0;

    free(wordToGuess);
}

void handleUserInput(char guess)
{
    // Update guessedLetters
    guessedLetters[guess - 'a'] = 1;

    // Replace asterisk with guessed letter
    for (int i = 0; secretWord[i] != '\0'; i++)
    {
        if (guessedLetters[secretWord[i] - 'a'])
        {
            printf("%c", secretWord[i]);
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}

int main()
{
    char playerInput;

    initializeGame();

    printf("Here is the word to guess: \n");
    for (int i = 0; secretWord[i] != '\0'; i++)
    {
        printf("*");
    }
    printf("\n");

    int remainingLetters = strlen(secretWord);

    while (remainingLetters > 0)
    {
        printf("Enter a letter: ");
        scanf(" %c", &playerInput);
        playerInput = tolower(playerInput);

        while (!isalpha(playerInput))
        {
            printf("Invalid input. Please enter a letter: ");
            scanf(" %c", &playerInput);
            playerInput = tolower(playerInput);
        }

        if (!guessedLetters[playerInput - 'a'])
        {
            handleUserInput(playerInput);
            if (strchr(secretWord, playerInput) != NULL)
            {
                remainingLetters--;
            }
            guessedLetters[playerInput - 'a'] = 1;
        }
        else
        {
            printf("You already guessed that letter. Try again.\n");
        }
    }

    printf("Congratulations! You guessed the word: %s\n", secretWord);

    return 0;
}
