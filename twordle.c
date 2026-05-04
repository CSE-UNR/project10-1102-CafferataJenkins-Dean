//Author: Dean Cafferata-Jenkins
#include <stdio.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6


void loadWord(char word[]);
void toLowerCase(char str[]);
void getGuess(char guess[], int guessNum);
void checkWorks(char guess[], int *works);
void checkCorrect(char guess[], char word[], int *correct);
void displayGuess(char guesses[][WORD_LENGTH + 1], int count, char word[]);
void contains(char word[], char letter, int *found);


void loadWord(char word[]) {
    FILE *file = fopen("word.txt", "r");
    fscanf(file, "%s", word);
    fclose(file);
}

void getGuess(char guess[], int guessNum) {
    printf("GUESS %d! Enter your guess: ", guessNum);
    scanf("%s", guess);
    printf("================================\n");
}

void checkWorks(char guess[], int *works) {
    int length = 0;
    *works = 1;

    while (guess[length] != '\0') {
        if (!((guess[length] >= 'a' && guess[length] <= 'z') ||
              (guess[length] >= 'A' && guess[length] <= 'Z'))) {
            *works = 0;
        }
        length++;
    }

    if (length != WORD_LENGTH) {
        *works = 0;
    }
}

void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

void checkCorrect(char guess[], char word[], int *correct) {
    *correct = 1;

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] != word[i]) {
            *correct = 0;
        }
    }
}

void contains(char word[], char letter, int *found) {
    *found = 0;

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word[i] == letter) {
            *found = 1;
        }
    }
}

void displayGuess(char guesses[][WORD_LENGTH + 1], int count, char word[]) {
    printf("\n");

    for (int i = 0; i < count; i++) {

        // print guess (capitalize correct letters)
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (guesses[i][j] == word[j]) {
                char c = guesses[i][j];
                if (c >= 'a' && c <= 'z') {
                    c -= 32;
                }
                printf("%c", c);
            } else {
                printf("%c", guesses[i][j]);
            }
        }
        printf("\n");

        // print hint arrows
        for (int j = 0; j < WORD_LENGTH; j++) {
            int found;
            contains(word, guesses[i][j], &found);

            if (guesses[i][j] != word[j] && found == 1) {
                printf("^");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("\n");
}



int main() {
    char word[WORD_LENGTH + 1];
    char guesses[MAX_GUESSES][WORD_LENGTH + 1];

    int guessCount = 0;
    int correct = 0;

    loadWord(word);

    while (guessCount < MAX_GUESSES && correct == 0) {
        char guess[WORD_LENGTH + 1];
        int works = 0;

        getGuess(guess, guessCount + 1);
        checkWorks(guess, &works);

        if (works == 0) {
            printf("Invalid guess. Try again.\n");
            continue;
        }

        toLowerCase(guess);

        
        for (int i = 0; i <= WORD_LENGTH; i++) {
            guesses[guessCount][i] = guess[i];
        }

        displayGuess(guesses, guessCount + 1, word);

        checkCorrect(guess, word, &correct);

        guessCount++;
    }

  
    printf("FINAL GUESS: %s\n", guesses[guessCount - 1]);
    printf("================================\n");

    displayGuess(guesses, guessCount, word);

    if (correct != 0) {
        printf("You win! Yippie! Yippie!! \n");
    } else {
        printf("Uh oh :(, You lost, better luck next time!\n");
    }

    return 0;
}


