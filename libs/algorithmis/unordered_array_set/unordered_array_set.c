#include <stdio.h>
#include "unordered_array_set.h"
#include <stdbool.h>
#include <assert.h>


// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

// возвращает множество, состоящее из элементов массива a размера size
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    unordered_array_set_shrinkToFit(&set);
    return set;
}

//освобождает неиспользуемую оперативную память, отведённую под множество
static void unordered_array_set_shrinkToFit(unordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(set, value) == set->size) {
        append_(set->data, &set->size, value);
    }
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size)
        return 0;
    qsort(set1.data, set1.size, sizeof(int), compare_ints);
    qsort(set2.data, set2.size, sizeof(int), compare_ints);
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == false;
}

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t posDeleteElement = unordered_array_set_in(set, value);
    if (posDeleteElement != set->size)
        deleteByPosSaveOrder_(set->data, &set->size, posDeleteElement);
}

// вывод множества set
void unordered_array_set_printf(unordered_array_set set) {
    printf("{");
    for (int i = 0; i <= set.size; i++) {
        printf("%d, ", set.data[i]);
    }
    if (set.size == 0) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
}

// возвращает объединение множеств set1 и set2
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size + set2.size);
    for (int i = 0; i < set1.size; i++) {
        append_(set.data, &set.size, set1.data[i]);
    }
    for (int i = 0; i < set2.size; i++) {
        unordered_array_set_insert(&set, set2.data[i]);
    }
    return (unordered_array_set) set;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size);
    for (int i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) != set2.size) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }
    return (unordered_array_set) set;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set = unordered_array_set_create(set1.size);
    for (int i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size) {
            unordered_array_set_insert(&set, set1.data[i]);
        }
    }
    return (unordered_array_set) set;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set setDif1 = unordered_array_set_difference(set1, set2);
    unordered_array_set setDif2 = unordered_array_set_difference(set2, set1);
    unordered_array_set setUnion = unordered_array_set_union(setDif1, setDif2);
    unordered_array_set_delete(setDif1);
    unordered_array_set_delete(setDif2);
    return setUnion;
}

// возвращает дополнение до универсума множества set
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    unordered_array_set notSet = unordered_array_set_difference(universumSet, set);
    return (unordered_array_set) notSet;
}

// возвращает значение ’истина’ если множество subset является подмножеством множества set, иначе - ’ложь’.
bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (size_t i = 0; i < subset.size; i++)
        if (linearSearch_(set.data, set.size, subset.data[i]) == set.size)
            return false;
    return true;
}

