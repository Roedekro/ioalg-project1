//
// Created by soren on 9/16/16.
//

//#include "OutputStreamInterface.h"

#ifndef IOALG_PROJECT1_OUTPUTSTREAM_H
#define IOALG_PROJECT1_OUTPUTSTREAM_H

using namespace std;

class OutputStreamA {
public:
    int filedesc;
    OutputStreamA();
    virtual ~OutputStreamA();
    void create(char* s);
    void write(int* number);
    void close();
};

#endif //IOALG_PROJECT1_OUTPUTSTREAM_H
