#include "matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


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
    for (int i = 0; i < m.nRows; i++) {
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
            scanf("%d", &m.values[i][j]);
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

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {

    int *arrayRowsWithCriteria = (int *) (malloc(sizeof(int) * m.nRows));
    for (int i = 0; i < m.nRows; ++i) {
        arrayRowsWithCriteria[i] = criteria(m.values[i], m.nCols);
    }
    for (int i = 1; i < m.nRows; ++i) {
        int t = arrayRowsWithCriteria[i];
        int j = i;
        while (j > 0 && arrayRowsWithCriteria[j - 1] > t) {
            arrayRowsWithCriteria[j] = arrayRowsWithCriteria[j - 1];
            swapRows(m, j, j - 1);
            j--;
        }
        arrayRowsWithCriteria[j] = t;
    }
    free(arrayRowsWithCriteria);

}

void insertionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *arrayCols = (int *) (malloc(sizeof(int) * m.nCols));
    int *arrayColsWithCriteria = (int *) (malloc(sizeof(int) * m.nCols));
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            arrayCols[j] = m.values[j][i];
        }
        arrayColsWithCriteria[i] = criteria(arrayCols, m.nRows);
    }
    for (int i = 1; i < m.nRows; ++i) {
        int t = arrayColsWithCriteria[i];
        int j = i;
        while (j > 0 && arrayColsWithCriteria[j - 1] > t) {
            arrayColsWithCriteria[j] = arrayColsWithCriteria[j - 1];
            swapColumns(m, j, j - 1);
            j--;
        }
        arrayColsWithCriteria[j] = t;
    }
    free(arrayCols);
    free(arrayColsWithCriteria);
}

bool isSquareMatrix(matrix m) { return m.nRows == m.nCols; }

bool twoMatricesEqual(matrix m1, matrix m2) {
    if(m1.nRows == m2.nRows && m1.nCols == m2.nCols) {

        for (int i = 0; i < m1.nRows; ++i) {
            if (memcmp(m1.values[i], m2.values[i], sizeof(int) * m1.nCols) != 0) {
                return 0;
            }
        }
        return 1;
    }else{
        return 0;
    }
}

bool isEMatrix(matrix m) {
    bool isIdentityMatrix = true;
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (i == j && m.values[i][j] != 1) {
                isIdentityMatrix = false;
            }
        }
    }
    return isIdentityMatrix;
}

bool isSymmetricMatrix(matrix m) {
    bool isSymmetric = true;
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = i+1; j < m.nCols; ++j) {
            if (m.values[i][j] != m.values[j][i]) {
                isSymmetric = false;
            }
        }
    }
    return isSymmetric;
}

void transposeSquareMatrix(matrix m) {
    for (int i = 1; i < m.nCols; ++i) {
        for (int j = 0; j < i; ++j) {
            swap(&m.values[i][j], &m.values[j][i], sizeof(int));
        }
    }
}
position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minIndex.rowIndex = i;
                minIndex.colIndex = j;
            }
        }
    }
    return minIndex;
}

position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxIndex.rowIndex = i;
                maxIndex.colIndex = j;
            }
        }
    }
    return maxIndex;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}


