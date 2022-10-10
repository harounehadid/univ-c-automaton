#include <stdio.h>
#include <malloc.h>

typedef struct automaton {
    int state;
    char transition;
    struct automaton* next;
}automaton;



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

    return 0;
}