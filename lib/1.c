#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 5

void print_matrix(int adj_matrix[][MAX_VERTICES]) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

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
        {0, 1, 1, 0, 0}, 
        {1, 0, 0, 1, 0}, 
        {1, 0, 0, 0, 1}, 
        {0, 1, 0, 0, 0}, 
        {0, 0, 1, 0, 0}  
    };

    print_matrix(adj_matrix);

    bool visited[MAX_VERTICES] = {false}; 

    printf("\nDFS traversal starting from A: ");
    dfs(0, adj_matrix, visited);
    printf("\n");

    return 0;
}