//
// Created by soren on 9/16/16.
//

#ifndef IOALG_PROJECT1_OUTPUTSTREAMB_H
#define IOALG_PROJECT1_OUTPUTSTREAMB_H

#include <stdio.h>

using namespace std;

class OutputStreamB {
public:
    FILE* file;
    OutputStreamB();

    virtual ~OutputStreamB();
    void create(char* s);
    int write(int* number);
    void close();
};

#endif //IOALG_PROJECT1_OUTPUTSTREAMB_H
