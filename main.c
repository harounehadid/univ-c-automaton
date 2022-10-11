#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct stringList {
    char* word;
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

    // The while loop to account for memory allocation failures
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
    // Just in case
    fflush(stdin);

    FILE* file;
    char ch;

    // Opening the file
    file = fopen(fileName, "r");

    if (file == NULL) printf("\nThe file can't be opened\n");

    printf("\n\nChecking file...\n");

    // Count how many character in the file
    int charCount = 0;

    for (char c = getc(file); c != EOF; c = getc(file)) {
        charCount++;
    }

    // Going back to the begining of the file
    rewind(file);

    // Creating the variable that's gonna hold all file's text
    char* str;

    do {
        str = malloc(charCount * sizeof(char));

    } while (str == NULL);
    

    // Append characters from the file to form a string
    do {
        ch = fgetc(file);
        strncat(str, &ch, 1);

    } while (ch != EOF);

    // Closing the file
    fclose(file);

    return str;
}

stringList* addWordToList(stringList* strList, char* word) {
    // To prevent jumpig lines
    fflush(stdin);

    stringList* newWord = NULL;

    // The while loop to account for memory allocation failures
    do {
        newWord = malloc(sizeof(stringList));
    
    } while (newWord == NULL);

    newWord->word = word;
    newWord->next = NULL;

    if (strList == NULL) {
        strList = newWord;
        newWord = NULL;
        
    }
    else {
        stringList* temp = strList;

        while (temp->next != NULL) {
            temp = temp->next;  
        }

        temp->next = newWord;
        temp = NULL;
        newWord = NULL;
    }

    return strList;
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

    char* fileText = readFileAndReturnText("testing-file.txt");

    printf("\nFILE TEXT: %s", fileText);

    // Create analyze function that takes the text and two lists for recognized and non recognized words
    // Analyze and filter
    // Check against automaton function

    char word[100] = "";

    bool newWord = true;
    bool isValid = false;
    int cyclesCounter = 1;

    return 0;
}