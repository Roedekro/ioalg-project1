//
// Created by soren on 9/20/16.
//

#include <stdio.h>
#include "OutputStreamInterface.h"

#ifndef IOALG_PROJECT1_OUTPUTSTREAMD_H
#define IOALG_PROJECT1_OUTPUTSTREAMD_H

class OutputStreamD {
public:
    int index;
    int filedesc;
    int portionSize;
    int portionIndex;
    int *map;
    OutputStreamD(int portionSize);
    virtual ~OutputStreamD();
    void create(char* s);
    void write(int* number);
    void close();

};

#endif //IOALG_PROJECT1_OUTPUTSTREAMD_H
