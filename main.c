#include <stdio.h>
#include <malloc.h>

typedef struct automaton {
    int state;
    char transition;
    struct automaton* next;
}automaton;

int main() {
    automaton* automatonChain;
    int statesToAdd;

    printf("---------- Welcome ----------------");    
    printf("How many states to add: ");
    scanf("%d", &statesToAdd);

    for (int i = 1; i <= statesToAdd; i++) {
        int transition;

        printf("State number %d transition: ", i);
        scanf("%d", &transition);

        automaton* newState = createNewNode(i);
        addToAutomatonChain(automatonChain, newState);
    }

    displayAutomaton(automatonChain);

    return 0;
}

automaton* createNewNode(int state) {
    automaton* newNode = (automaton*)malloc(sizeof(automaton));
    char transition;

    printf("Enter transition character: ");
    scanf("%c", &transition);

    newNode->state = state;
    newNode->transition = transition;
    newNode->next = NULL;

    return newNode;
}

void addToAutomatonChain(automaton* chain, automaton* node) {
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
}

void displayAutomaton(automaton* chain) {
    automaton* temp = chain;

    while (temp != NULL) {
        if (temp->next != NULL) {
            printf("(%d)- %c ->", temp->state, temp->transition);
        }
        else {
            printf("(%d)", temp->state);
        }
    }
}