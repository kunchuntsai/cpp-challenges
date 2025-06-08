#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Exercise 1: Basic Double Pointer Operations
void exercise1() {
    int value = 42;
    int* ptr = &value;
    int** dptr = &ptr;

    printf("Exercise 1: Value through double pointer: %d\n", **dptr);
}

// Exercise 2: Dynamic Memory Allocation with Double Pointers
void exercise2() {
    int** matrix = NULL;
    int rows = 3, cols = 3;

    matrix = (int**)malloc(rows * sizeof(int*));
    assert(matrix != NULL);
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        assert(matrix[i] != NULL);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    // Print matrix
    printf("\nExercise 2: 3x3 Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Exercise 3: Linked List with Double Pointers
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insert_at_beginning(Node** head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    assert(new_node != NULL);
    
    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}

void exercise3() {
    Node* head = NULL;
    
    insert_at_beginning(&head, 3);
    insert_at_beginning(&head, 2);
    insert_at_beginning(&head, 1);

    // Print list
    printf("\nExercise 3: Linked List: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

// Exercise 4: String Array with Double Pointers
void exercise4() {
    char** strings = NULL;
    int num_strings = 3;

    strings = (char**)malloc(num_strings * sizeof(char*));
    assert(strings != NULL);
    
    const char* words[] = {"Hello", "World", "C"};
    for (int i = 0; i < num_strings; i++) {
        strings[i] = (char*)malloc(strlen(words[i]) + 1);
        assert(strings[i] != NULL);
        strcpy(strings[i], words[i]);
    }

    // Print strings
    printf("\nExercise 4: String Array:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
    }
    free(strings);
}

// Exercise 5: Function Pointer Array with Double Pointers
typedef void (*Operation)(int);

void add(int x) { printf("Adding %d\n", x); }
void subtract(int x) { printf("Subtracting %d\n", x); }
void multiply(int x) { printf("Multiplying by %d\n", x); }

void exercise5() {
    Operation* operations = NULL;
    int num_operations = 3;

    operations = (Operation*)malloc(num_operations * sizeof(Operation));
    assert(operations != NULL);
    
    operations[0] = add;
    operations[1] = subtract;
    operations[2] = multiply;

    // Execute operations
    printf("\nExercise 5: Function Pointer Array:\n");
    for (int i = 0; i < num_operations; i++) {
        operations[i](5);
    }

    free(operations);
}

int main() {
    printf("Double Pointers Exercises\n");
    printf("=======================\n");

    exercise1();
    exercise2();
    exercise3();
    exercise4();
    exercise5();

    return 0;
} 