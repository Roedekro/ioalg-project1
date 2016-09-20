//
// Created by soren on 9/16/16.
//

#ifndef IOALG_PROJECT1_INPUTSTREAMC_H
#define IOALG_PROJECT1_INPUTSTREAMC_H

using namespace std;

class InputStreamC {
public:
    int filedesc;
    int * buffer;
    int index;
    InputStreamC(int bufferSize);
    virtual ~InputStreamC();
    int open(char* s);
    int readNext();
    bool endOfStream();
    void close();
};

#endif //IOALG_PROJECT1_INPUTSTREAMC_H
