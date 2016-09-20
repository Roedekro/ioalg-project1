//
// Created by soren on 9/20/16.
//

#ifndef IOALG_PROJECT1_INPUTSTREAMD_H
#define IOALG_PROJECT1_INPUTSTREAMD_H

#include <stdio.h>

using namespace std;

class InputStreamD {
public:
    FILE* file;
    int filedesc;
    int * map;
    int index;
    int fileSize;
    InputStreamD();
    virtual ~InputStreamD();
    int open(char* s);
    int readNext();
    bool endOfStream();
    void close();
};


#endif //IOALG_PROJECT1_INPUTSTREAMD_H
