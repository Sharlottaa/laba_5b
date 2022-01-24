#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "libs\data_structures\matrix\matrix.h"


int main() {
    matrix m=getMemMatrix(2,2);
    inputMatrix(m);
   // insertionSortRowsMatrixByRowCriteria(m);
    outputMatrix(m);
    freeMemMatrix(m);
 return 0;
}






