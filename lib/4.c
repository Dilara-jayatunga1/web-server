#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 6

void dfs(int start_node, int adj_matrix[][MAX_VERTICES], bool visited[], char vertices[]) {
    visited[start_node] = true;
    printf("%c ", vertices[start_node]);

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (adj_matrix[start_node][i] == 1 && !visited[i]) {
            dfs(i, adj_matrix, visited, vertices); // Corrected: Pass 'vertices' argument
        }
    }
}

int main() {
    int adj_matrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 1, 0, 0}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 1}, 
        {0, 0, 0, 0, 1, 0}, 
        {0, 0, 1, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0}  
    };

    char vertices[] = {'s', 'a', 'c', 'b', 'd', 'e'};
    bool visited[MAX_VERTICES] = {false};
    int start_node = 0;

    printf("DFS traversal starting from %c: ", vertices[start_node]);
    dfs(start_node, adj_matrix, visited, vertices); // Corrected: Pass 'vertices' argument here as well
    printf("\n");

    return 0;
}