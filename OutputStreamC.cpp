//
// Created by soren on 9/16/16.
//

#include "OutputStreamC.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

OutputStreamC::OutputStreamC(int bufferSize) {
    index = 0;
    buffer = new int[bufferSize];
}

OutputStreamC::~OutputStreamC() {
    // TODO Auto-generated destructor stub
}

int OutputStreamC::create(char* s) {
    filedesc = ::open(s, O_CREAT|O_RDWR);
    return filedesc;
}

void OutputStreamC::write(int* number) {
    index++;
    if (index < sizeof(buffer) / sizeof(int)) {
        buffer[index] = *number;
    } else {
        ::write(filedesc, buffer, sizeof(buffer));
        index = 0;
    }
}

void OutputStreamC::close() {
    ::close(filedesc);
    delete(buffer);
    index = 0;
}