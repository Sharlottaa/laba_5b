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
void sortRowsByMinElement(matrix m) {
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
    long long *a = (long long *) calloc(m.nRows, sizeof(long long));
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

void append(int *a, int *n, const int value) {
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

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
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

    long long sum = getSum(sumMax, size);
    free(sumMax);
    return sum;
}


int k(matrix m){
    int sum = 0;
    for (int i =0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; ++j) {
            if(i==j){
                sum+=m.values[i][j];
            }
        }
    return sum;
}

//8. Дана прямоугольная матрица, все элементы которой различны. Найти минимальный элемент матрицы в выделенной области:

int getMinInArea(matrix m){
    position maxIndex= getMaxValuePos(m);

}

// 9
double getDistance(int *a, int m){
    int d=0;
    for (int i = 0; i < m; ++i) {
        d+=a[i]*a[i];
    }
    return sqrt(d);
}
void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteria(m,getDistance);
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
    assert(m.nCols==m.nRows);
    int *aColm=(int*) malloc(sizeof(int)*m.nRows);
    int *aColmSum=(int*) malloc(sizeof(int)*m.nRows);
    if(NULL==aColm||NULL==aColmSum){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    int count=0;
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            aColm[i]=m.values[j][i];
        }
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
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[i+1])
            return 0;
    }
    return 1;
}
bool hasAllNonDescendingRows(matrix m){
    for (int i = 0; i < m.nRows; ++i) {
            if (!isNonDescendingSorted(m.values[i],m.nCols)) {
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


int main() {
    //int a[] = {0, 1,
               //1, 0,
              // 0, 0,
            ////

             // };
      //int a[5]={1,0,3,4,0};
   // printf("%d",countValues(a,5,0));
   // matrix *ms = createArrayOfMatrixFromArray(a, 4, 3, 2);
     matrix m1 = getMemMatrix(3, 3);
    inputMatrix(m1);
    // inputMatrix(m2);
   // int a[5]={1,2,3,4,5};
    //printf("%d", countNonDescendingRowsMatrices(ms,4));
    //transposeIfMatrixHasEqualSumOfRows(m1);
    //getNSpecialElement(m1);
    //swapPenultimateRow(m1);
     //printf("%d",getLeftMin(m1));
    //maxDiagonalSum(m1);
    outputMatrix(m1);
 //   outputMatrix(m2);
   // printMatrixWithMaxZeroRows(ms,4);
   //freeMemMatrices(ms,4);
   freeMemMatrix(m1);
    return 0;
}






