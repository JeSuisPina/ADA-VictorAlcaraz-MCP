#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define R 5
#define C 5

int min(int x, int y, int z) {
    if(x < y)
        return (x < z) ? x : z;
    else
        return (y < z) ? y : z;
}

int minCostIterativo(int cost[R][C], int m, int n) {
    int tc[R][C];
    int i, j;

    tc[0][0] = cost[0][0];

    // Inicializar primera columna del arreglo total cost(tc)
    for (i = 1; i < m; i++) {
        tc[i][0] = tc[i - 1][0] + cost[i][0];
    }

    // Calcular el costo mínimo para llegar a la primera fila
    for (j = 1; j < n; j++) {
        tc[0][j] = tc[0][j - 1] + cost[0][j];
    }

    // Calcular el costo mínimo para llegar a cada celda restante
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            tc[i][j] = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]) + cost[i][j];
        }
    }

    return tc[m - 1][n - 1];
}

int minCostRecursivo(int cost[R][C], int m, int n){
    if(n < 0 || m < 0)
        return INT_MAX;

    else if(m == 0 && n == 0)
        return cost[m][n];

    else {
        return cost[m][n] + min(minCostRecursivo(cost, m - 1, n - 1), minCostRecursivo(cost, m - 1, n), 
        minCostRecursivo(cost, m, n - 1));
    }
}

int main() {
    int matrix[R][C] = {{4, 7, 8, 6, 4}, {6, 7, 3, 9, 2}, {3, 8, 1, 2, 4},
    {7, 1, 7, 3, 7}, {2, 9, 8, 9, 3}};

    int algoritmoIterativo = 0, algoritmoRecursivo = 0;
    
    algoritmoIterativo = minCostIterativo(matrix, R, C);
    algoritmoRecursivo = minCostRecursivo(matrix, R - 1, C - 1);


    printf("El costo mínimo de la ruta por el algoritmo iterativo es: %d\n", algoritmoIterativo);
    printf("El costo mínimo de la ruta por el algoritmo recursivo es: %d\n", algoritmoRecursivo);

    return 0;
}
