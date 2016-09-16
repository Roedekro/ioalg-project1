/*
 * OutputStream.cpp
 *
 *  Created on: 16/09/2016
 *      Author: Martin
 */

#include "OutputStreamA.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

OutputStreamA::OutputStreamA() {
    filedesc = -1;
}

OutputStreamA::~OutputStreamA() {
    // TODO Auto-generated destructor stub
}

int OutputStreamA::create(char* s) {
    filedesc = ::open(s, O_CREAT|O_RDWR);
    return filedesc;
}

int OutputStreamA::write(int* number) {
    return ::write(filedesc, number, sizeof(int));
}

void OutputStreamA::close() {
    ::close(filedesc);
}