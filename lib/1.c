#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11

// Structure to represent a queue
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
    int size;
} Queue;

// Queue functions
void enqueue(Queue *q, int value) {
    if (q->size == MAX_VERTICES) {
        printf("Queue is full!\n");
        return;
    }
    q->items[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_VERTICES;
    q->size++;
}

int dequeue(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty!\n");
        return -1; 
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX_VERTICES;
    q->size--;
    return value;
}

bool is_empty(Queue *q) {
    return q->size == 0;
}

// BFS function
void bfs(int adjacency_matrix[][MAX_VERTICES], int start_vertex, char vertices[]) {
    Queue q;
    q.front = 0;
    q.rear = 0;
    q.size = 0;

    bool visited[MAX_VERTICES] = {false};

    printf("BFS traversal starting from vertex %c: ", vertices[start_vertex]);

    enqueue(&q, start_vertex);
    visited[start_vertex] = true;

    while (!is_empty(&q)) {
        int current_vertex = dequeue(&q);
        printf("%c ", vertices[current_vertex]);

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (adjacency_matrix[current_vertex][i] == 1 && !visited[i]) {
                enqueue(&q, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

int main() {
    // Adjacent matrix representation of the graph
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0}, // A
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // B
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // C
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // D
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}, // E
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0}, // G
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // H
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1}, // I
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // J
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // K
    };

    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'G', 'H', 'I', 'J', 'K'};

    // Start BFS from vertex G 
    bfs(adjacency_matrix, 5, vertices);

    return 0;
}