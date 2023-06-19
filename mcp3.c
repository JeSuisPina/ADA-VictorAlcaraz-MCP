#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define R 100
#define C 100

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

void fillMatrixRandom(int matrix[R][C]) {
    srand(time(NULL));

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            matrix[i][j] = rand() % 9 + 1;
        }
    }
}

void printMatrix(int matrix[R][C]) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[R][C];
    fillMatrixRandom(matrix);

    clock_t start1, end1, start2, end2;
    double cpu_time_used1, cpu_time_used2;

    printf("Matriz generada:\n");
    //printMatrix(matrix);

    int algoritmoIterativo = 0, algoritmoRecursivo = 0;
    
    start1 = clock();
    algoritmoIterativo = minCostIterativo(matrix, R, C);
    end1 = clock();

    start2 = clock();
    algoritmoRecursivo = minCostRecursivo(matrix, R - 1, C - 1);
    end2 = clock();

    cpu_time_used1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cpu_time_used2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;

    printf("El costo mínimo de la ruta por el algoritmo iterativo es: %d\n", algoritmoIterativo);
    printf("El costo mínimo de la ruta por el algoritmo recursivo es: %d\n", algoritmoRecursivo);

    printf("\nTiempo de ejecución para el algoritmo iterativo: %f segundos\n", cpu_time_used1);
    printf("Tiempo de ejecución para el algoritmo recursivo: %f segundos\n", cpu_time_used2);

    return 0;
}
