#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1003  // Setting slightly higher than max constraint

typedef struct {
    int locations[MAX_N];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// Check if queue is empty
bool isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// Enqueue function
void enqueue(Queue* q, int value) {
    q->locations[q->rear++] = value;
}

// Dequeue function
int dequeue(Queue* q) {
    return q->locations[q->front++];
}

int main() {
    int N, M, K, C;
    scanf("%d %d %d %d", &N, &M, &K, &C);

    // Input validation
    if (N > MAX_N) {
        printf("Error: N exceeds maximum allowed value.\n");
        return 1;
    }

    // Adjacency list instead of matrix (avoids segmentation fault for large N)
    int **graph = (int **)malloc((N + 1) * sizeof(int *));
    for (int i = 0; i <= N; i++) {
        graph[i] = (int *)calloc(N + 1, sizeof(int));
    }

    // Read paths safely
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= N && y >= 1 && y <= N) {
            graph[x][y] = 1;
            graph[y][x] = 1; // Bidirectional
        }
    }

    // BFS Setup
    bool visited[MAX_N] = {false}; 
    int distance[MAX_N] = {0};
    Queue q;
    initQueue(&q);

    visited[C] = true;
    enqueue(&q, C);

    int reachable_locations = 0;

    // BFS Traversal
    while (!isQueueEmpty(&q)) {
        int current = dequeue(&q);
        reachable_locations++;

        // Traverse all connected locations
        for (int i = 1; i <= N; i++) {
            if (graph[current][i] == 1 && !visited[i] && distance[current] < K) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                enqueue(&q, i);
            }
        }
    }

    printf("%d\n", reachable_locations);

    // Free allocated memory
    for (int i = 0; i <= N; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
