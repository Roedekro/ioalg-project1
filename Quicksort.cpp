//
// Created by martin on 10/1/16.
//

#include "Quicksort.h"

Quicksort::Quicksort() {

}

Quicksort::~Quicksort() {

}

void Quicksort::sort(int *array, int p, int r) {

    if(p<r) {
        int q = partition(array, p, r);
        sort(array, p, q-1);
        sort(array,q+1, r);
    }
}

int Quicksort::partition(int *array, int p, int r) {

    int x = array[r];
    int i = p-1;
    for(int j = p; j < r; j++) {
        if(array[j] <= x) {
            i++;
            int tempI = array[i];
            int tempJ = array[j];
            array[j] = tempI;
            array[i] = tempJ;
        }
    }
    int tempI = array[i+1];
    array[r] = tempI;
    array[i+1] = x;

    return i+1;
}