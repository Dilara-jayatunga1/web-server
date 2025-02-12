#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 7

void dfs(int vertex, int adj_matrix[][MAX_VERTICES], bool visited[]) {
    visited[vertex] = true;
    printf("%c ", 'H' + vertex);
    for (int neighbor = 0; neighbor < MAX_VERTICES; neighbor++) {
        if (adj_matrix[vertex][neighbor] == 1 && !visited[neighbor]) {
            dfs(neighbor, adj_matrix, visited);
        }
    }
}

int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0, 0, 0, 0}, // H -> I
        {0, 0, 1, 0, 0, 0, 0}, // I -> M
        {0, 0, 0, 0, 0, 1, 0}, // M -> N
        {0, 0, 0, 0, 0, 0, 1}, // N -> P
        {0, 0, 0, 1, 0, 0, 0}, // J -> K
        {0, 0, 0, 0, 0, 0, 1}, // K -> L
        {0, 0, 0, 0, 0, 0, 0}  // L -> (none)
    };

    bool visited[MAX_VERTICES] = {false};

    printf("DFS traversal starting from H: ");

    if (!visited[0]) {
        dfs(0, adj_matrix, visited);
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i]) {
            dfs(i, adj_matrix, visited);
        }
    }

    printf("\n");

    return 0;
}