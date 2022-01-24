#include <stdio.h>
#include <assert.h>
#include <iso646.h>

#include"bitset.h"

// возвращает пустое множество c универсумом U = {0, 1,..., maxValue}
bitset bitset_create(uint32_t maxValue) {
    assert(maxValue < 32);
    return (bitset) {0, maxValue};
}

//  возвращает значение ’истина’, если value лежит в допустимом диапазоне множества
// иначе - ’ложь’
bool bitset_checkValue(bitset set, uint32_t value) {
    return value >= 0 and value <= set.maxValue;
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset set, uint32_t value) {
    assert(bitset_checkValue(set, value));
    return set.values >> value & 1;
}

// добавляет элемент value в множество set
void bitset_insert(bitset *set, uint32_t value) {
    assert(bitset_checkValue(*set, value));
    set->values |= (1 << value);
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return set1.values == set2.values;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

// удаляет элемент value из множества set
void bitset_deleteElement(bitset *set, uint32_t value) {
    assert(bitset_checkValue(*set, value));
    set->values & ~(1 << value);
}

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values | set2.values, set1.maxValue};
}

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & ~set2.values, set1.maxValue};
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values ^ set2.values, set1.maxValue};
}

// возвращает дополнение до универсума множества set
bitset bitset_complement(bitset set) {
    return (bitset) {~set.values, set.maxValue};
}

// возвращает значение ’истина’ если множество subset
// не строго является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset subset, bitset set) {
    assert(subset.maxValue == set.maxValue);
    return (set.values & subset.values) == subset.values;
}

// вывод множества set
void bitset_print(bitset set) {
    printf("{");
    bool isEmpty = true;//является ли множество пустым
    for (int i = 0; i <= set.maxValue; i++) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = false;
        }
    }
    if (isEmpty == true) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}




