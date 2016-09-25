//
// Created by soren on 9/16/16.
//

#include "OutputStreamC.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <initializer_list>
#include <algorithm>

using namespace std;

OutputStreamC::OutputStreamC(int bufferSize) {
    index = 0;
    buffer = new int[bufferSize];
}

OutputStreamC::~OutputStreamC() {
    // TODO Auto-generated destructor stub
}

void OutputStreamC::create(char* s) {
    filedesc = ::open(s, O_CREAT|O_RDWR);
}

void OutputStreamC::write(int* number) {
    if (index >= sizeof(buffer) / sizeof(int)) {
        ::write(filedesc, buffer, sizeof(buffer));
        index = 0;
    }

    buffer[index] = *number;
    index++;
}

void OutputStreamC::close() {
    if (index != 0) {
        ::write(filedesc, buffer, index * sizeof(int));
        //::write(filedesc, buffer, (index - 1) * sizeof(int));
        //::write(filedesc, buffer, sizeof(buffer));
    }

    ::close(filedesc);
    delete(buffer);
    index = 0;
}