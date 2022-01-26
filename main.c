#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "libs\data_structures\matrix\matrix.h"

//1. Дана квадратная матрица, все элементы которой различны. Поменять местами
//строки, в которых находятся максимальный и минимальный элементы.
void swapRowsMinMax(matrix m) {
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);
    swapRows(m, min.rowIndex, max.rowIndex);
}

//2. Упорядочить строки матрицы по неубыванию наибольших элементов строк
//возвращает максимальный элемент в одномерном массиве а размера n
int getMax(const int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

//сортирует в двумерном массиве по неубыванию максимальные значения в одномерном массиве
void sortRowsByMinElement(matrix m) {
    for (int i = 0; i < m.nRows - 1; i++)
        for (int j = m.nRows - 1; j > i; j--) {
            if (getMax(m.values[i], m.nCols) > getMax(m.values[j], m.nCols)) {
                swapRows(m, j, i);
            }
        }
}


//3. Дана прямоугольная матрица. Упорядочить столбцы матрицы по неубыванию
//минимальных элементов столбцов:

//возвращает минимальный элемент в одномерном массиве а размера n
int getMin(const int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

void sortColsByMinElement(matrix m);

// 4.сли данная квадратная матрица 𝐴 симметрична, то заменить 𝐴 ее квадрат
matrix mulMatrices(matrix m1, matrix m2) {
    matrix saveNewMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m2.nCols; ++j) {
            saveNewMatrix.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; ++k) {
                saveNewMatrix.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }
    return saveNewMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

// 5. Дана квадратная матрица. Если среди сумм элементов строк матрицы нет равных, то транспонировать матрицу

bool isUnique(const long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == a[i + 1]) {
            return 0;
        }
    }
    return 1;
}

long long getSum(const int *a, const int n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    long long *a = (int *) calloc(m.nRows, sizeof(long long));
    assert(a != NULL);

    for (register size_t i = 0; i < m.nRows; ++i) {
        a[i] += getSum(m.values[i], m.nCols);
    }
    if (isUnique(a, m.nRows)) {
        transposeSquareMatrix(m);
    }
    free(a);
}

int main() {
    matrix m1 = getMemMatrix(2, 2);

    inputMatrix(m1);
    transposeIfMatrixHasEqualSumOfRows(m1);
    // printf("%d",isSymmetricMatrix(m1));
    outputMatrix(m1);

    freeMemMatrix(m1);

    return 0;
}






