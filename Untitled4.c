#include <stdio.h>
#include <stdlib.h>

void getInput(int **matrix, int rowCount, int columnCount);
void printMatrix(int **matrix, int rowCount, int columnCount);
void cramerSolve(int **matrix, int *result, int rowCount, int columnCount);

int main() {
    int rowCount, columnCount;
    printf("Enter the number of rows in the matrix: ");
    scanf("%d", &rowCount);
    printf("Enter the number of columns in the matrix: ");
    scanf("%d", &columnCount);

    int **matrix = (int **)malloc(rowCount * sizeof(int *));
    for (int i = 0; i < rowCount; ++i) {
        matrix[i] = (int *)malloc(columnCount * sizeof(int));
    }
    if (matrix == NULL) {
        printf("%s: %d Failed to allocate memory\n", __FILE__, __LINE__);
        exit(0);
    } else {
        getInput(matrix, rowCount, columnCount);
        printf("Entered Matrix:\n");
        printMatrix(matrix, rowCount, columnCount);

        int *result = (int *)malloc(rowCount * sizeof(int));
        printf("Enter the result vector:\n");
        for (int i = 0; i < rowCount; ++i) {
            printf("Result[%d]: ", i);
            scanf("%d", &result[i]);
        }

        cramerSolve(matrix, result, rowCount, columnCount);

        free(result);
    }
    for (int i = 0; i < rowCount; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

void getInput(int **matrix, int rowCount, int columnCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            printf("Enter the element at [%d][%d] of the matrix: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int **matrix, int rowCount, int columnCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void cramerSolve(int **matrix, int *result, int rowCount, int columnCount) {
    if (rowCount != columnCount) {
        printf("Invalid matrix dimensions!\n");
        return;
    }

    int *determinants = (int *)malloc(rowCount * sizeof(int));
    int determinantA = 0;

    for (int k = 0; k < rowCount; ++k) {
        int **matrixK = (int **)malloc(rowCount * sizeof(int *));
        for (int i = 0; i < rowCount; ++i) {
            matrixK[i] = (int *)malloc(columnCount * sizeof(int));
            for (int j = 0; j < columnCount; ++j) {
                matrixK[i][j] = matrix[i][j];
            }
            matrixK[i][k] = result[i];
        }

        int determinantK = determinant(matrixK, rowCount);

        determinantA = determinant(matrix, rowCount);

        printf("x%d = %d / %d = %.2f\n", k + 1, determinantK, determinantA, (float)determinantK / determinantA);

        for (int i = 0; i < rowCount; ++i) {
            free(matrixK[i]);
        }
        free(matrixK);
    }

    free(determinants);
}

int determinant(int **matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }

    int det = 0;
    int **submatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        submatrix[i] = (int *)malloc(n * sizeof(int));
    }

    int sign = 1;
    for (int f = 0; f < n; ++f) {
        getSubmatrix(matrix, submatrix, 0, f, n);
        det += sign * matrix[0][f] * determinant(submatrix, n - 1);
        sign = -sign;
    }

    for (int i = 0; i < n; ++i) {
        free(submatrix[i]);
    }
    free(submatrix);

    return det;
}

void getSubmatrix(int **matrix, int **submatrix, int row, int col, int n) {
    int i = 0, j = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r != row && c != col) {
                submatrix[i][j++] = matrix[r][c];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
