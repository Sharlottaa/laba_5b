#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "libs\data_structures\matrix\matrix.h"

//1. Дана квадратная матрица, все элементы которой различны. Поменять местами
//строки, в которых находятся максимальный и минимальный элементы.
void swapRowsMinMax(matrix m){
    position min= getMinValuePos(m);
    position max= getMaxValuePos(m);
    swapRows(m,min.rowIndex,max.rowIndex);
}

//2. Упорядочить строки матрицы по неубыванию наибольших элементов строк
//возвращает максимальный элемент в одномерном массиве а размера n
int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

//сортирует в двумерном массиве по неубыванию максимальные значения в одномерном массиве
void sortRowsByMinElement(matrix m){
    for ( size_t i = 0; i < m.nRows - 1; i ++)
        for ( size_t j = m.nRows - 1; j > i ; j --){
            if(getMax(m.values[i],m.nCols)>getMax(m.values[j],m.nCols)){
                swapRows(m,j,i);
            }
    }
}


//3. Дана прямоугольная матрица. Упорядочить столбцы матрицы по неубыванию
//минимальных элементов столбцов:
int getMin(int *a, int n){

}


int main() {
    matrix m1=getMemMatrix(3,3);

    inputMatrix(m1);
    sortRowsByMinElement(m1);
  //  printf("%d",isSymmetricMatrix(m1));
    outputMatrix(m1);

    freeMemMatrix(m1);

    return 0;
}






