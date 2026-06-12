

#include <stdio.h>
#include <stdlib.h>

void constantSpace(int n) {
    int a = 10;
    int b = 20;
    int c;
    c = a + b + n;
    printf("Constant Space Used : %lu bytes\n",
           (unsigned long)(sizeof(a) + sizeof(b) + sizeof(c)));
}

void linearSpace(int n) {
    int *arr;
    int i;
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
    printf("Linear Space Used : %lu bytes\n",
           (unsigned long)(n * sizeof(int)));
    free(arr);
}

void quadraticSpace(int n) {
    int **matrix;
    int i, j;
    matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i][j] = i + j;
        }
    }
    printf("Quadratic Space Used: %lu bytes\n",
           (unsigned long)(n * n * sizeof(int)));
    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n;
    printf("Enter value of n: ");
    scanf("%d", &n);
    printf("\n--- SPACE COMPLEXITY ANALYSIS ---\n\n");
    printf("Constant Space Case:\n");
    constantSpace(n);
    printf("Space Complexity: O(1)\n\n");
    printf("Linear Space Case:\n");
    linearSpace(n);
    printf("Space Complexity: O(n)\n\n");
    printf("Quadratic Space Case:\n");
    quadraticSpace(n);
    printf("Space Complexity: O(n^2)\n");
    return 0;
}