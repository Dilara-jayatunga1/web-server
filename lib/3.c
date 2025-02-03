#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 8

// Queue implementation (simple array for demonstration)
typedef struct {
    char items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isQueueEmpty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, char value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

char dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return '\0'; // Or handle as needed
    }
    char item = q->items[q->front++];
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

int main() {
    // Adjacency list representation (for clarity and efficiency)
    char adj[MAX_VERTICES][MAX_VERTICES] = {
        {'B', 'E', 'F', '\0'}, // A (0)
        {'A', 'C', 'D', '\0'}, // B (1)
        {'B', 'D', '\0'},      // C (2)
        {'B', 'C', 'F', 'H', '\0'}, // D (3)
        {'A', 'F', '\0'},      // E (4)
        {'A', 'D', 'G', '\0'}, // F (5)
        {'F', '\0'},          // G (6)
        {'D', '\0'}           // H (7)
    };

    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int num_vertices = sizeof(vertices) / sizeof(vertices[0]);

    bool visited[MAX_VERTICES] = {false};
    Queue q;
    initQueue(&q);

    char start_node = 'A';
    int start_index = -1;
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i] == start_node) {
            start_index = i;
            break;
        }
    }

    if (start_index == -1) {
        printf("Start node not found!\n");
        return 1;
    }

    printf("BFS Traversal starting from %c: ", start_node);

    enqueue(&q, start_node);
    visited[start_index] = true;

    while (!isQueueEmpty(&q)) {
        char current_node = dequeue(&q);
        printf("%c ", current_node);

        int current_index = -1;
        for (int i = 0; i < num_vertices; i++) {
            if (vertices[i] == current_node) {
                current_index = i;
                break;
            }
        }

        // Enqueue unvisited neighbors in lexicographical order
        for (int i = 0; adj[current_index][i] != '\0'; i++) {
            char neighbor = adj[current_index][i];
            int neighbor_index = -1;
            for (int j = 0; j < num_vertices; j++) {
                if (vertices[j] == neighbor) {
                    neighbor_index = j;
                    break;
                }
            }
            if (!visited[neighbor_index]) {
                enqueue(&q, neighbor);
                visited[neighbor_index] = true;
            }
        }
    }

    printf("\n");

    return 0;
}