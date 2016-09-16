//
// Created by soren on 9/16/16.
//

#ifndef IOALG_PROJECT1_OUTPUTSTREAM_H
#define IOALG_PROJECT1_OUTPUTSTREAM_H

using namespace std;

class OutputStreamA {
public:
    int filedesc;
    OutputStreamA();

    OutputStreamA(int filedesc);

    virtual ~OutputStreamA();
    int create(char* s);
    int write(int* number);
    void close();
};

#endif //IOALG_PROJECT1_OUTPUTSTREAM_H
