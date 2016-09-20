//
// Created by soren on 9/16/16.
//

#ifndef IOALG_PROJECT1_OUTPUTSTREAMC_H
#define IOALG_PROJECT1_OUTPUTSTREAMC_H

using namespace std;

class OutputStreamC {
public:
    int index;
    int * buffer;
    int filedesc;
    OutputStreamC(int bufferSize);

    virtual ~OutputStreamC();
    int create(char* s);
    void write(int* number);
    void close();
};


#endif //IOALG_PROJECT1_OUTPUTSTREAMC_H
