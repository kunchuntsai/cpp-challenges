#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int head;
    int tail;
    int capacity;
    int size;
} CircularBuffer;

CircularBuffer* create_circular_buffer(int capacity) {
    CircularBuffer* cb = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    if(cb == NULL) {
        return NULL;
    }
    cb->data = (int*)malloc(sizeof(int)*capacity);
    if(cb->data == NULL) {
        free(cb);
        return NULL;
    }
    cb->head = 0;
    cb->tail = 0;
    cb->capacity = capacity;
    cb->size = 0;
    return cb;
}

void free_circular_buffer(CircularBuffer* cb) {
    free(cb->data);
    free(cb);
}

int circular_buffer_push(CircularBuffer* cb, int value) {
	if(cb->size >= cb->capacity) return 0;
		
    cb->data[cb->tail] = value;
    cb->tail = (cb->tail +1) % cb->capacity;
    cb->size++;
    return 1;
}

int circular_buffer_pop(CircularBuffer* cb, int* value) {
	if(cb->size == 0) return 0;
		
    *value = cb->data[cb->head];
    cb->head = (cb->head +1) % cb->capacity;
    cb->size--;
    return 1;
}

void print_circular_buffer(CircularBuffer* cb) {
    printf("Circular Buffer: ");
    for(int i = 0; i < cb->size; i++) {
        printf("%d ", cb->data[(cb->head + i) % cb->capacity]);
    }
    printf("\n");
}

int main() {
    CircularBuffer* cb = create_circular_buffer(10);
    if(cb == NULL) {    
        printf("Failed to create circular buffer\n");
        return 1;
    }
    circular_buffer_push(cb, 1);
    print_circular_buffer(cb);
    circular_buffer_push(cb, 2);
    print_circular_buffer(cb);
    circular_buffer_push(cb, 3);
    print_circular_buffer(cb);
    int value;
    circular_buffer_pop(cb, &value);
    print_circular_buffer(cb);
    free_circular_buffer(cb);
    return 0;
}