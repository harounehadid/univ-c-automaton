#include <stdio.h>
#include <malloc.h>

typedef struct automaton {
    int state;
    char transition;
    struct automaton* next;
}automaton;

int main() {
    

    

    return 0;
}

automaton* createNewNode(int state, char transition) {
    automaton* newNode = malloc(sizeof(automaton));

    newNode->state = state;
    newNode->transition = transition;
    newNode->next = NULL;

    return NULL;
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

//Display info