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
int getMax( int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

//сортирует в двумерном массиве по неубыванию максимальные значения в одномерном массиве
void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m,getMax);
}


//3. Дана прямоугольная матрица. Упорядочить столбцы матрицы по неубыванию
//минимальных элементов столбцов:

//возвращает минимальный элемент в одномерном массиве а размера n
int getMin( int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

void sortColsByMinElement(matrix m){
    insertionSortColsMatrixByColCriteria(m,getMin);
}

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

bool isUnique(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == a[i + 1]) {
            return 0;
        }
    }
    return 1;
}


long long getSum( int *a, int n) {
    long long sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i];
    return sum;
}

void transposeIfMatrixHasEqualSumOfRows(matrix m) {
    int *a = (int *) calloc(m.nRows, sizeof(int));
    assert(a != NULL);

    for (register size_t i = 0; i < m.nRows; ++i) {
        a[i] += getSum(m.values[i], m.nCols);
    }
    if (isUnique(a, m.nRows)) {
        transposeSquareMatrix(m);
    }
    free(a);
}

//6.Даны две квадратные матрицы 𝐴 и 𝐵. Определить, являются ли они взаимно
//обратными (𝐴 = 𝐵−1).

bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix mul=mulMatrices(m1, m2);
    if (isEMatrix(mul)){
        return 1;
    }
    return 0;
}
//Дана прямоугольная матрица. Назовем псевдодиагональю множество элементов этой матрицы, лежащих на прямой, параллельной прямой, содержащей элементы 𝑎𝑖,𝑖. Найти сумму максимальных элементов всех псевдодиагоналей данной матрицы. На рисунке ниже все псевдодиагонали выделены различными
//цветами:

void k_(matrix m) {
    int sum = 0;
    int max_up = m.values[0][1];
    int max_down = m.values[1][0];
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; ++j) {
            if (j > i && max_up < m.values[i][j]){
                max_up = m.values[i][j];
                printf("%d", max_up);}
            if (i > j && max_down < m.values[i][j]){
                max_down = m.values[i][j];

                printf("%d", max_down);}
        }
}

int max(int a, int b) { return a < b ? b : a; }

void append(int *a, int *n, int value) {
    a[*n] = value;
    (*n)++;
}

int getMaxValueOfPseudoDiagonal(matrix m, int row, int col){
    int maxValue = m.values[row][col];

    while (col < m.nCols && row < m.nRows) {
        maxValue=max(m.values[row][col], maxValue);
        row++;
        col++;
    }
    return maxValue;
}

int findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int *sumMax = (int *) malloc(sizeof(int) * (m.nRows + m.nCols - 1));
    int size = 0;

    for (int i = 1; i < m.nCols; i++) {
        int row = 0, col = i;
        int maxValueUp = getMaxValueOfPseudoDiagonal(m, row, col);
        append(sumMax, &size, maxValueUp);
    }
    for (int i = 0; i < m.nRows - 1; i++) {
        int row = m.nRows - 1, col = i;
        int maxValueDown = getMaxValueOfPseudoDiagonal(m, row, col);
        append(sumMax, &size, maxValueDown);
    }

    int sum = (int)getSum(sumMax, size);
    free(sumMax);

    return sum;
}

//8. Дана прямоугольная матрица, все элементы которой различны. Найти минимальный элемент матрицы в выделенной области:


int getMinInArea(matrix m) {
    position maxIndex = getMaxValuePos(m);
    int minValue = m.values[maxIndex.rowIndex][maxIndex.colIndex];
    int left= maxIndex.colIndex;
    int right= maxIndex.colIndex;
    for (int i = maxIndex.rowIndex; i >= 0; i--) {
        for (int j = left; j <= right; ++j) {
            if (m.values[i][j] < minValue)
                minValue = m.values[i][j];
        }
        left = left > 0 ? left - 1 : left;
        right = right < m.nCols ? right + 1 : right;
    }
    return minValue;
}

// 9
double getDistance(int *a, int m){
    int d=0;
    for (int i = 0; i < m; ++i) {
        d+=a[i]*a[i];
    }
    return sqrt(d);
}
void insertionSortRowsMatrixByRowCriteriaDouble(matrix m, double (*criteria)(int *, int)) {

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
void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaDouble(m,getDistance);
}

//10

int cmp(const void *pa, const void *pb) {
    int arg1 = *(const int *) pa;
    int arg2 = *(const int *) pb;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int countNUnique(int *a, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j])
                count++;
    return count;
}

int countEqClassesByRowsSum(matrix m){
    int *sum=(int*) malloc(sizeof(int)*m.nRows);
    if(NULL==sum){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    for (int i = 0; i < m.nRows; ++i) {
        sum[i]= (int)getSum(m.values[i],m.nCols);
    }
    qsort(sum,m.nRows,sizeof(int),cmp);
    int countEq=countNUnique(sum,m.nRows);
    free(sum);
    return countEq;
}

//11. Дана квадратная матрица. Определить 𝑘 – количество "особых" элементов матрицы, считая элемент "особым", если он больше суммы остальных элементов
//своего столбца.

int getNSpecialElement(matrix m){
    int *aColm=(int*) malloc(sizeof(int)*m.nCols);
    int *aColmSum=(int*) malloc(sizeof(int)*m.nRows);
    if(NULL==aColm||NULL==aColmSum){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    int count=0;
    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j)
            aColm[j] = m.values[j][i];
        int maxInCol= getMax(aColm,m.nRows);
         aColmSum[i]= (int)getSum(aColm,m.nRows);
        if(aColmSum[i]-maxInCol<maxInCol){
            count++;
        }
    }
    free(aColm);
    free(aColmSum);
    return count;
}

//12 Дана квадратная матрица. Заменить предпоследнюю строку матрицы первым
//из столбцов, в котором находится минимальный элемент матрицы.


void swapPenultimateRow(matrix m){
    assert(m.nCols==m.nRows);
    int *aColm=(int*) malloc(sizeof(int)*m.nRows);
    if(NULL==aColm){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    position min= getMinValuePos(m);
    int col=min.colIndex;//местоположение столбца с минимом
    for (int i = 0; i < m.nRows; ++i) {
        aColm[i]=m.values[i][col];//столбец с минимом
    }
    for (int i = 0; i < m.nCols; ++i) {
        m.values[m.nRows-2][i]=aColm[i];//строка предпоследняя с минимом столбца
    }
    free(aColm);
}

//13 Дан массив квадратных матриц. Определить число матриц, строки которых
//упорядочены по неубыванию элементов (подходящие матрицы выделены зеленым):

bool isNonDescendingSorted(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        if (a[i-1] > a[i])
            return 0;
    }
    return 1;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        if (!isNonDescendingSorted(m.values[i], m.nCols)) {
            return 0;
        }
    }
    return 1;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){
    int count=0;
    for (int i = 0; i < nMatrix; ++i) {
        if(hasAllNonDescendingRows(ms[i])){
            count++;
        }
    }
    return count;
}

//14 Дан массив целочисленных матриц. Вывести матрицы, имеющие наибольшее
//число нулевых строк

bool countValues(const int *a, int n, int value){
    for (int i = 0; i < n; ++i) {
        if(a[i]!=value){
            return 0;
        }
    }
    return 1;
}

int countZeroRows(matrix m){
    int count=0;
    for (int i = 0; i < m.nRows; ++i) {
        count+= countValues(m.values[i],m.nCols,0);
    }
    return count;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix){
    int *aCountZeroRows=(int*) malloc(sizeof(int) * nMatrix);
    if(NULL == aCountZeroRows){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    for (int i = 0; i < nMatrix; ++i) {
        aCountZeroRows[i]= countZeroRows(ms[i]);
    }
    int maxCountZeroRows= getMax(aCountZeroRows,nMatrix);
    for (int i = 0; i < nMatrix; ++i) {
        if(aCountZeroRows[i]==maxCountZeroRows){
            outputMatrix(ms[i]);
        }
    }
    free(aCountZeroRows);
}

//15
//поиск максимального вещественного числа по модулю в матрице
double getMaxMatrixDoublefabs(matrixDouble m) {
    double maxfabs = fabs(m.valueDouble[0][0]);
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            if (maxfabs < fabs(m.valueDouble[i][j])) {
                maxfabs = fabs(m.valueDouble[i][j]);
            }
        }
    }
    return fabs(maxfabs);
}

//возвращает минимальный вещественный элемент в одномерном массиве а размера n
double getMinDouble(double *a, int n) {
    double min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

void outputMatricesWithMinNorm(matrixDouble *ms,int nMatrices) {
    double *aMatricesMaxfabs = (double *) malloc(sizeof(double) * nMatrices);
    for (int i = 0; i < nMatrices; ++i) {
        aMatricesMaxfabs[i] = getMaxMatrixDoublefabs(ms[i]);
    }
    double minInMaxfabsMatrices = getMinDouble(aMatricesMaxfabs, nMatrices);
    for (int i = 0; i < nMatrices; ++i) {
        if (fabs(aMatricesMaxfabs[i] - minInMaxfabsMatrices) < 0.0000001) {
            outputMatrixDouble(ms[i]);
        }
    }
    free(aMatricesMaxfabs);
}

void test_swapRowsMinMax1 () {
    matrix m1= createMatrixFromArray (
            (int []) {
                       1 , 2 , 0 ,
                       8 , 5 , 1 ,
                       7 , 9 , 6 ,
            } ,
            3 , 3
    ) ;
    swapRowsMinMax(m1);
    matrix m2= createMatrixFromArray (
            (int []) {
                    7 , 9 , 6 ,
                    8 , 5 , 1,
                    1 , 2 , 0 ,
            } ,
            3 , 3
    ) ;
    assert (twoMatricesEqual(m1,m2)) ;

    freeMemMatrix (m1) ;
    freeMemMatrix (m2) ;
}
void test_swapRowsMinMax2 () {
    matrix m1= createMatrixFromArray (
            (int []) {
                    7 , 2 , 6 ,
                    8 , 5 , 1 ,
                    7 , 9 , 10 ,
            } ,
            3 , 3
    ) ;
    swapRowsMinMax(m1);
    matrix m2= createMatrixFromArray (
            (int []) {
                    7 , 2 , 6 ,
                    7 , 9 , 10,
                    8 , 5 , 1 ,
            } ,
            3 , 3
    ) ;
    assert (twoMatricesEqual(m1,m2)) ;

    freeMemMatrix (m1) ;
    freeMemMatrix (m2) ;
}

void test_swapRowsMinMax3 () {
    matrix m1= createMatrixFromArray (
            (int[]) {
                    1, 2, 3, 5,
                    11, 2, 6, 14,
                    8, 5, 1, 4,
                    7, 0, 10, 3,
            },
            4, 4
    );
    swapRowsMinMax(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 5,
                    7, 0, 10, 3,
                    8, 5, 1, 4,
                    11, 2, 6, 14,
            },
            4, 4
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}


void test_swapRowsMinMax() {
    test_swapRowsMinMax1();
    test_swapRowsMinMax2();
    test_swapRowsMinMax3();
}

void test_sortRowsByMaxElement_classic() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 2, 6,
                    18, 5, 1,
                    7, 9, 10,
            },
            3, 3
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 2, 6,
                    7, 9, 10,
                    18, 5, 1,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement_maxEqual() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 18, 6,
                    18, 5, 1,
                    7, 9, 18,
            },
            3, 3
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 18, 6,
                    18, 5, 1,
                    7, 9, 18,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement_rows_Equal() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 7, 7,
                    8, 8, 8,
                    1, 1, 1,
            },
            3, 3
    );
    sortRowsByMaxElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    7, 7, 7,
                    8, 8, 8,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortRowsByMaxElement() {
    test_sortRowsByMaxElement_classic();
    test_sortRowsByMaxElement_maxEqual();
    test_sortRowsByMaxElement_rows_Equal();
}

void test_sortColsByMinElement_classic() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 6,
                    18, -8, 0,
                    7, 9, 10,
            },
            3, 3
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    2, 6, 1,
                    -8, 0, 18,
                    9, 10, 7,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortColsByMinElement_minEqual() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, -8, 6,
                    -8, 5, 1,
                    7, 9, -8,
            },
            3, 3
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, -8, 6,
                    -8, 5, 1,
                    7, 9, -8,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortColsByMinElement_cols_Equal() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    6, 1, 7,
                    6, 1, 7,
                    6, 1, 7,
            },
            3, 3
    );
    sortColsByMinElement(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 6, 7,
                    1, 6, 7,
                    1, 6, 7,
            },
            3, 3
    );
    assert (twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}



void test_sortColsByMinElement() {
    test_sortColsByMinElement_classic();
    test_sortColsByMinElement_minEqual();
    test_sortColsByMinElement_cols_Equal();
}


void test_getSquareOfMatrixIfSymmetric1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3
            },
            1, 1
    );
    getSquareOfMatrixIfSymmetric(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    9
            },
            1, 1
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}


void test_getSquareOfMatrixIfSymmetric2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    2, 1
            },
            2, 2
    );
    getSquareOfMatrixIfSymmetric(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 4,
                    4, 5
            },
            2, 2
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_getSquareOfMatrixIfSymmetric3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 1, 3,
                    1, 3, 5,
                    3, 5, 5
            },
            3, 3
    );
    getSquareOfMatrixIfSymmetric(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    35, 23, 35,
                    23, 35, 43,
                    35, 43, 59
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}


void test_getSquareOfMatrixIfSymmetric() {
    test_getSquareOfMatrixIfSymmetric1();
    test_getSquareOfMatrixIfSymmetric2();
    test_getSquareOfMatrixIfSymmetric3();
}

void test_transposeIfMatrixHas_NOT_EqualSumOfRows1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 2,
                    5, 0,
            },
            2, 2
    );
    transposeIfMatrixHasEqualSumOfRows(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 2,
                    5, 0,
            },
            2, 2
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeIfMatrixHasEqualSumOfRows2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 4,
                    1, 0, 8,
                    1, 0, 9,
            },
            3, 3
    );
    transposeIfMatrixHasEqualSumOfRows(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 1, 1,
                    5, 0, 0,
                    4, 8, 9,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_transposeIfMatrixHasEqualSumOfRows3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 1,
                    2, 2,
            },
            2, 2
    );
    transposeIfMatrixHasEqualSumOfRows(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    1, 2,
            },
            2, 2
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}


void test_transposeIfMatrixHasEqualSumOfRows() {
    test_transposeIfMatrixHas_NOT_EqualSumOfRows1();
    test_transposeIfMatrixHasEqualSumOfRows2();
    test_transposeIfMatrixHasEqualSumOfRows3();
}

void test_isMutuallyInverseMatrices1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0,
                    0, 1
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0,
                    0, 1
            },
            2, 2
    );

    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 5, 7,
                    6, 3, 4,
                    5, -2, -3,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, -1, 1,
                    -38, 41, -34,
                    27, -29, 24
            },
            3, 3
    );

    assert(isMutuallyInverseMatrices(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 4,
                    0, 1
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0,
                    0, 4
            },
            2, 2
    );

    assert(!(isMutuallyInverseMatrices(m1, m2)));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isMutuallyInverseMatrices() {
    test_isMutuallyInverseMatrices1();
    test_isMutuallyInverseMatrices2();
    test_isMutuallyInverseMatrices3();
}

void test_findSumOfMaxesOfPseudoDiagonal1() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 24);

    freeMemMatrix(m1);
}

void test_findSumOfMaxesOfPseudoDiagonal2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7,
            },
            1, 1
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 0);

    freeMemMatrix(m1);
}

void test_findSumOfMaxesOfPseudoDiagonal3() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 8,
                    3, 2, 1, 3,
            }, 3, 4
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 23);

    freeMemMatrix(m1);
}


void test_findSumOfMaxesOfPseudoDiagonal() {
    test_findSumOfMaxesOfPseudoDiagonal1();
    test_findSumOfMaxesOfPseudoDiagonal2();
    test_findSumOfMaxesOfPseudoDiagonal3();
}


void test_getMinInArea1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    10, 0, 7,
                    3, 11, 8,
                    4, 1, 12,
            },
            3, 3
    );

    assert(getMinInArea(m1) == 0);

    freeMemMatrix(m1);
}

void test_getMinInArea2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -7, 2, -8,
                    21, 47, 9,
                    23, 11, 25,
            },
            3, 3
    );

    assert(getMinInArea(m1) == -8);

    freeMemMatrix(m1);
}

void test_getMinInArea3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -7, 2, 1, 7, 5,
                    21, 1, 30, 10, 4,
                    23, 11, 25, 4, 5,
            },
            3, 5
    );

    assert(getMinInArea(m1) == 1);

    freeMemMatrix(m1);
}

void test_getMinInArea() {
    test_getMinInArea1();
    test_getMinInArea2();
   test_getMinInArea3();
}

void test_sortByDistances1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 7, 7,
                    8, 8, 8,
                    1, 1, 1,
            },
            3, 3
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    7, 7, 7,
                    8, 8, 8,
            },
            3, 3
    );
    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7,8,9,
                    4,5,6,
                    1,2,3,
            },
            3, 3
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7,6,9,
                    4,5,6,
                    0,2,3,
            },
            3, 3
    );
    sortByDistances(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0,2,3,
                    4,5,6,
                    7,6,9,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_sortByDistances() {
    test_sortByDistances1();
    test_sortByDistances2();
    test_sortByDistances3();
}

void test_countEqClassesByRowsSum1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,5,6,
                    0,6,6,
                    0,5,7,
            },
            3, 3
    );

    assert(countEqClassesByRowsSum(m1)==3);

    freeMemMatrix(m1);
}

void test_countEqClassesByRowsSum2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7,1,
                    2,7,
                    5,4,
                    4,3,
                    1,6,
                    8,0,
            },
            6, 2
    );

    assert(countEqClassesByRowsSum(m1)==3);

    freeMemMatrix(m1);
}

void test_countEqClassesByRowsSum3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7,1,
                    8,0,
            },
            2, 2
    );

    assert(countEqClassesByRowsSum(m1)==1);

    freeMemMatrix(m1);
}

void test_countEqClassesByRowsSum() {
    test_countEqClassesByRowsSum1();
    test_countEqClassesByRowsSum2();
    test_countEqClassesByRowsSum3();
}

void test_getNSpecialElement1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3,5,5,4,
                    2,3,6,7,
                    12,1,2,1,
            },
            3, 4
    );

    assert(getNSpecialElement(m1)==3);

    freeMemMatrix(m1);
}

void test_getNSpecialElement2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2,3,
                    3,4,
                    3,6,
            },
            3, 2
    );

    assert(getNSpecialElement(m1)==0);

    freeMemMatrix(m1);
}

void test_getNSpecialElement3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,2,3,2,
                    2,3,4,3,
                    4,7,6,9,
            },
            3, 4
    );

    assert(getNSpecialElement(m1)==3);

    freeMemMatrix(m1);
}

void test_getNSpecialElement() {
    test_getNSpecialElement1();
    test_getNSpecialElement2();
    test_getNSpecialElement3();
}

void test_swapPenultimateRow1(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,1,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    1,4,7,
                    7,8,1,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapPenultimateRow2(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 2, 5,
                    6, 1, 8,
                    9, 10, 11,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 5,
                    2, 1, 10,
                    9, 10, 11,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapPenultimateRow3(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    5, 2, 8,
                    6, 2, 1,
                    9, 10, 11,
            },
            3, 3
    );
    swapPenultimateRow(m1);
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 8,
                    8, 1, 11,
                    9, 10, 11,
            },
            3, 3
    );

    assert(twoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_swapPenultimateRow() {
    test_swapPenultimateRow1();
    test_swapPenultimateRow2();
    test_swapPenultimateRow3();
}

void test_countNonDescendingRowsMatrices1() {
    int a[] = {
               7, 1,
               1,1,
            ////
               1,6,
               3,8,
            ////
               5,4,
               2,3,
            ////
               1,3,
               7,8,
    };

    matrix *ms = createArrayOfMatrixFromArray(a, 4, 2, 2);

    assert(countNonDescendingRowsMatrices(ms, 4) == 2);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices2() {
    int a[] = {7, 9,
               1, 1,
               3, 3,
               1, 6,
            ////
               2, 3,
               4, 5,
               5, 4,
               2, 3,
            ////
               4, 7,
               1, 1,
               6, 7,
               2, 13,
            ////
               3, 1,
               2, 3,
               6, 1,
               2, 2,
    };

    matrix *ms = createArrayOfMatrixFromArray(a, 4, 4, 2);

    assert(countNonDescendingRowsMatrices(ms, 4) == 2);

    freeMemMatrices(ms, 4);
}

void test_countNonDescendingRowsMatrices3() {
    int a[] = {
            0, 1,
            2, 3,
            0, 1,
            2, 9,
            ////
            7, 9,
            1, 8,
            3, 3,
            1, 6,
            ////
            2, 3,
            4, 5,
            1, 4,
            2, 3,
    };

    matrix *ms = createArrayOfMatrixFromArray(a, 3, 4, 2);

    assert(countNonDescendingRowsMatrices(ms, 3) == 3);

    freeMemMatrices(ms, 3);
}

void test_countNonDescendingRowsMatrices() {
    test_countNonDescendingRowsMatrices1();
    test_countNonDescendingRowsMatrices2();
    test_countNonDescendingRowsMatrices3();
}
void test(){
    test_swapRowsMinMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
}


int main() {
    matrixDouble *ms = createArrayOfMatrixFromArrayDouble((double []) {
                                                                  -3.4, 4.5,
                                                                  3.4, -3.9,
                                                                  ////
                                                                  9.4, 8.4,
                                                                  2.3, -23.4,
                                                                  ////
                                                                  2.1, 4.5,
                                                                  10.3,-45.5,
                                                          },
                                                          3, 2, 2);
    outputMatricesWithMinNorm(ms,3);
    freeMemMatricesDouble(ms,3);
    return 0;
}






