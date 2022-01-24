#include "matrix.h"
#include <stdio.h>
#include <malloc.h>


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; ++i) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; ++i) {
        ms[i] = getMemMatrix(nRows, nCols);
    }
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nCols; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            scanf("%d", &(m.values[i][j]));
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        inputMatrix(ms[i]);
    }
}


void outputMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; ++i) {
        printf("|");
        for (size_t j = 0; j < m.nCols; ++j) {
            printf("%d ", m.values[i][j]);
        }
        printf("\b| \n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        outputMatrix(ms[i]);
    }
    printf("\n");
}


void swapRows(matrix m, int i1, int i2) {
    int *const t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swap(void *a, void *b, size_t size) {
    char *pa = a;
    char *pb = b;
    for (size_t i = 0; i < size; i++) {
        char t = *pa;
        *pa = *pb;
        *pb = t;
        *pa++;
        *pb++;
    }
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; ++i) {
        swap(&m.values[i][j1], &m.values[i][j2], sizeof(int));
    }
}

//выполняет сортировку вставками строк
//матрицы m по неубыванию значения функции criteria применяемой для строк
//В процессе сортировки создайте вспомогательный массив из nRows элементов, найдите значение
//функции для каждого ряда и выполните сортировку данного массива. В процессе обмена элементов
//полученного массива производите обмен строк при помощи swapRows.
void insertionSortRowsMatrixByRowCriteria(matrix m){
    for (int i = 0; i < m.nRows; ++i) {

        for (int i = 0; i < m.values; ++i) {
            int *const t = m.values[i];
            int j = i;
            while (j > 0 && m.values[j] > t) {
                m.values[j] = m.values[j - 1];
                j--;
            }
            m.values[j] = t;
        }

    }
}
