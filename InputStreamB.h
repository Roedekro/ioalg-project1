//
// Created by soren on 9/16/16.
//

#ifndef IOALG_PROJECT1_INPUTSTREAMB_H
#define IOALG_PROJECT1_INPUTSTREAMB_H

#include <stdio.h>

using namespace std;

class InputStreamB {
public:
    FILE* file;
    InputStreamB();
    virtual ~InputStreamB();
    void open(char* s);
    int readNext();
    bool endOfStream();
    void close();
};

#endif //IOALG_PROJECT1_INPUTSTREAMB_H
