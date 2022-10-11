#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct stringList {
    char* text;
    struct stringList* next;
} stringList;

typedef struct automaton {
    int state;
    char transition;
    struct automaton* next;
} automaton;


automaton* createNewNode(int state) {
    // To prevent jumpig lines
    fflush(stdin);

    automaton* newNode = NULL;
    char transition;

    // The while loop to counter memory allocation failures
    do {
        newNode = malloc(sizeof(automaton));
    
    } while (newNode == NULL);

    printf("Enter the transition of state number %d: ", state);
    scanf("%c", &transition);

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

int main() {
    automaton* automatonChain = NULL;
    int statesToAdd;

    printf("---------- Welcome ----------------");    
    printf("\nHow many states to add: ");
    scanf("%d", &statesToAdd);

    for (int i = 1; i <= statesToAdd; i++) {
        automaton* newState = createNewNode(i);
        automatonChain = addToAutomatonChain(automatonChain, newState);
    }

    displayAutomaton(automatonChain);

    FILE* file;
    char ch;

    // Opening the file
    file = fopen("testing-file.txt", "r");

    if (file == NULL) printf("\nThe file can't be opened\n");

    printf("\nCheck file...\n");

    char str[100] = "";

    do {
        ch = fgetc(file);
        
        strncat(str, &ch, 1);

    } while (ch != EOF);

    // Closing the file
    fclose(file);

    printf("\n this is the text: %s", str);

    return 0;
}