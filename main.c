#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct automaton {
    int state;
    char transition;
    struct automaton* next;
} automaton;


automaton* createNewNode(int state, bool finalState) {
    // To prevent jumpig lines
    fflush(stdin);

    automaton* newNode = NULL;
    char transition;

    // The while loop to account for memory allocation failures
    do {
        newNode = malloc(sizeof(automaton));
    
    } while (newNode == NULL);

    if (!finalState) {
        printf("Enter the transition of state number %d: ", state);
        scanf("%c", &transition);
    }
    else {
        transition = '-';
    }

    newNode->state = state;
    newNode->transition = transition;
    newNode->next = NULL;

    return newNode;
}

automaton* addToAutomatonChain(automaton* chain, automaton* node) {
    // To prevent jumping lines
    fflush(stdin);

    if (chain == NULL) {
        chain = node;
        node = NULL;     
    }
    else {
        automaton* temp = chain;

        while (temp->next != NULL) {
            temp = temp->next;  
        }

        temp->next = node;
        temp = NULL;
        node = NULL;
    }

    return chain;
}

void displayAutomaton(automaton* chain) {
    // To prevent jumping lines
    fflush(stdin);

    automaton* temp = chain;

    while (temp != NULL) {
        printf("(%d)", temp->state);
        if (temp->next != NULL) printf("- %c ->", temp->transition);
        temp = temp->next;
    }
}

int getAutomatonLength(automaton* chain) {
    automaton* temp = chain;
    int length = 0;

    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}

char* readFileAndReturnText(char* fileName) {
    FILE* file;
    char ch;

    // Opening the file
    file = fopen(fileName, "r");

    if (file == NULL) printf("\nThe file can't be opened\n");

    printf("\n\nChecking file...\n");

    // Count how many character in the file
    int charCount = 0;

    for (char c = fgetc(file); c != EOF; c = fgetc(file)) {
        charCount++;
    }

    // Going back to the begining of the file
    rewind(file);

    // Creating the variable that's gonna hold all file's text
    char* str = NULL;

    do {
        str = malloc(charCount * sizeof(char));

    } while (str == NULL);

    str[0] = '\0';

    // Append characters from the file to form a string
    do {
        ch = fgetc(file);
        strncat(str, &ch, 1);

    } while (ch != EOF);

    // Closing the file
    fclose(file);

    return str;
}

bool checkAgainstAutomaton(automaton* chain, char* word) {
    bool isRecognizable = true;
    automaton* temp = chain;
    int automatonLength = getAutomatonLength(chain);

    // The -1 is added because the final state doesn't have a transition, I made '-' to indicate no transition exists
    if (strlen(word) == automatonLength - 1) {
        for (int i = 0; i < strlen(word); i++) {
            if (word[i] != temp->transition || temp == NULL) {
                isRecognizable = false;
                break;
            }

            temp = temp->next;
        }
    }
    else {
        isRecognizable = false;
    }

    return isRecognizable;
}

// I could've made this function better but it's way too out of this project's scope
void analyzeAndFilter(automaton* chain, char* text) {
    bool isRecognizable;
    
    for (int i = 0; i < strlen(text) - 1; i++) {
        char word[50] = "";
        
        while (text[i] != ' ' && i < strlen(text) - 1) {
            strncat(word, &text[i], 1);
            i++;
        }

        printf("\nWord: %s", word);

        isRecognizable = checkAgainstAutomaton(chain, word);

        // Here dipaly the recognized and non recognized words
        printf(isRecognizable ? "  Recognized" : "  Lexical Error");
    }
}

int main() {
    automaton* automatonChain = NULL;
    int statesToAdd;

    printf("---------- Welcome ----------------");    
    printf("\nHow many states to add: ");
    scanf("%d", &statesToAdd);

    for (int i = 1; i <= statesToAdd; i++) {
        automaton* newState = NULL;
        // If it reaches the final state don't ask for input
        newState = createNewNode(i, i == statesToAdd);

        automatonChain = addToAutomatonChain(automatonChain, newState);
    }

    displayAutomaton(automatonChain);

    char* fileText = readFileAndReturnText("testing-file.txt");

    printf("\nFILE TEXT: %s", fileText);
    printf("\n");

    analyzeAndFilter(automatonChain, fileText);
    printf("\n\n");

    return 0;
}