#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "libs\data_structures\matrix\matrix.h"


int main() {
    matrix m1=getMemMatrix(3,2);

    inputMatrix(m1);
    transposeSquareMatrix(m1);
  //  printf("%d",isSymmetricMatrix(m1));
    outputMatrix(m1);

    freeMemMatrix(m1);

    return 0;
}






