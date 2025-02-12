#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 5

void dfs(int vertex, int adj_matrix[][MAX_VERTICES], bool visited[]) {
    visited[vertex] = true;
    printf("%c ", 'A' + vertex);
    for (int neighbor = 0; neighbor < MAX_VERTICES; neighbor++) {
        if (adj_matrix[vertex][neighbor] == 1 && !visited[neighbor]) {
            dfs(neighbor, adj_matrix, visited);
        }
    }
}

int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0}
    };

    bool visited[MAX_VERTICES] = {false};

    printf("DFS Traversal 1 (A D C B E): ");
    dfs(0, adj_matrix, visited);
    printf("\n");

    for (int i = 0; i < MAX_VERTICES; i++) visited[i] = false;
    printf("DFS Traversal 2 (A B E C D): ");
    
    // Manually change the order of neighbors to get different traversals
    int adj_matrix2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 1, 1}, // A -> B, D, E
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0}
    };
    dfs(0, adj_matrix2, visited);
    printf("\n");


    for (int i = 0; i < MAX_VERTICES; i++) visited[i] = false;
    printf("DFS Traversal 3 (A E B C D): ");
    int adj_matrix3[MAX_VERTICES][MAX_VERTICES] = {
        {0, 0, 1, 1, 1}, // A -> C, D, E
        {0, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0}
    };
    dfs(0, adj_matrix3, visited);
    printf("\n");


    return 0;
}