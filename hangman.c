#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS_LIST 10000
#define MAX_ATTEMPTS 15

void intro();
void randomWord(char answer[]);
int wordLength(char word[]);
void guessUnderscore(char guess[], int word_size);
void printGuess(char guess[], int size);
void askLetter(char *letter);
void checkIncorrect(char letter, char answer[], char guess[], int size, int *attempt);
int isLetter(char letter);
int repeatedLetter(char letter, char guess[], int size);
int correctLetter(char letter, char answer[], int answer_size, char guess[]);
int correctWord(char answer[], char guess[], int size);
void end(char answer[]);

int main() {
    intro();

    char answer[MAX_WORD_LENGTH], guess[MAX_WORD_LENGTH];
    char letter;
    int answer_size, incorrect_attempts = 0;

    randomWord(answer);
    answer_size = wordLength(answer);
    guessUnderscore(guess, answer_size);
    
    while ((incorrect_attempts != MAX_ATTEMPTS) && (correctWord(answer, guess, answer_size) == 0)) {
        printf("_________________________________________________\n\nGuess the word...\n");
        printGuess(guess, answer_size);
        printf("\n\n");
        printf("LIVES: %d\n", MAX_ATTEMPTS - incorrect_attempts);
        askLetter(&letter);
        checkIncorrect(letter, answer, guess, answer_size, &incorrect_attempts);
    }
    printf("_________________________________________________\n\n");

    if (incorrect_attempts == MAX_ATTEMPTS) {
        printf("You LOST!");
    }
    else {
        printf("You WON!");
    }

    printf(" Word: %s\nPlay again? (y/n): ", answer);
    end(answer);

    return 0;
}
void intro() {
    printf("\nHANGMAN GAME\n\n");
    printf("Rules: You must guess the correct letters of the word.\n");
    printf("You have %d lives in total.\n", MAX_ATTEMPTS);
    printf("If you type the wrong letter or if you repeat a letter, you will lose a life.\n");
}

void randomWord(char answer[]) {
    FILE *dictionary = fopen("dictionary.txt", "r");
    char buffer[MAX_WORDS_LIST];

    srand(time(0));
    int random_number = (rand() % MAX_WORDS_LIST);
    int current_word = 0;
    
    while (fgets(buffer, MAX_WORD_LENGTH, dictionary) != NULL) {
        if (current_word == random_number) {
            strcpy(answer, buffer);
            break;
        }
        current_word++;
    }
    fclose(dictionary);
}

int wordLength(char word[]) {
    int number_of_letters = strlen(word) - 1;
    return number_of_letters;
}

void guessUnderscore(char guess[], int word_size) {
    for (int i = 0; i < word_size; i++) {
        guess[i] = '_';
    }
    guess[word_size] = '\0';
}

void printGuess(char guess[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", guess[i]);
    }
}

void askLetter(char *letter) {
    printf("Enter a letter: ");
    scanf(" %c", letter);
    while (getchar() != '\n');
    printf("\n");
}

void checkIncorrect(char letter, char answer[], char guess[], int size, int *attempt) {
    if ((isLetter(letter) == 1 || repeatedLetter(letter, guess, size) == 1) || (correctLetter(letter, answer, size, guess) == 0)) {
        (*attempt)++;
    }
}

int isLetter(char letter) {
    if (isalpha(letter) == 0) {
        printf("Incorrect! (Not a valid letter...)\n");
        return 1;
    }
    return 0;
}

int repeatedLetter(char letter, char guess[], int size) {
    for (int i = 0; i < size; i++) {
        if (letter == guess[i]) {
            printf("_________________________________________________\n\n");
            printf("Incorrect! (This word has already been chosen...)\n");
            return 1;
        }
    }
    return 0;
}

int correctLetter(char letter, char answer[], int answer_size, char guess[]) {
    int flag = 0;
    for (int i = 0; i < answer_size; i++) {
        if (letter == answer[i]) {
            guess[i] = letter;
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("_________________________________________________\n\n");
        printf("Incorrect! (That letter is not in the word...)\n");
    }
    return flag;
}

int correctWord(char answer[], char guess[], int size) {
    int letter_match = 0;
    for (int i = 0; i < size; i++) {
        if (answer[i] == guess[i]) {
            letter_match++;
        }
    }
    if (letter_match == size) {
        return 1;
    }
    return 0;
}

void end(char answer[]) {
    char response;
    scanf(" %c", &response);
    if (response == 'y') {
        main();
    }
    else if (response == 'n') {
        return;
    }
    else {
        printf("Please pick y or n: ");
        end(answer);
    }
}

