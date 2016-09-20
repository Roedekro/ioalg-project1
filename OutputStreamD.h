//
// Created by soren on 9/20/16.
//

#ifndef IOALG_PROJECT1_OUTPUTSTREAMD_H
#define IOALG_PROJECT1_OUTPUTSTREAMD_H

#include <stdio.h>

using namespace std;

class OutputStreamD {
public:
    int index;
    int filedesc;
    int portionSize;
    int *map;
    OutputStreamD(int portionSize);

    virtual ~OutputStreamD();
    void create(char* s);
    int write(int* number);
    void close();
};

#endif //IOALG_PROJECT1_OUTPUTSTREAMD_H
