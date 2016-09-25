//
// Created by soren on 9/16/16.
//

#include "InputStreamC.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

InputStreamC::InputStreamC(int bufferSize) {
    index = 1000000000;
    buffer = new int[bufferSize];
}

InputStreamC::~InputStreamC() {
    // TODO Auto-generated destructor stub
}

void InputStreamC::open(char* s) {
    filedesc = ::open(s, O_RDONLY);
    if(filedesc == -1) {
        perror("Error opening the file in InputStreamC");
        exit(EXIT_FAILURE);
    }
}

int InputStreamC::readNext() {


    if(index >= sizeof(buffer) / sizeof(int)) {
        int bytesRead = ::read(filedesc, buffer, sizeof(buffer));
        index = 0;
    }
    int elm = buffer[index];
    index++;
    return elm;


    /*if (index == 0) {
        int bytesRead = ::read(filedesc, buffer, sizeof(buffer));
        index = bytesRead / sizeof(int);
    }

    index--;
    int elm = buffer[index];
    return elm;*/
}

bool InputStreamC::endOfStream() {
    if (index > 0) return false;
    bool b = false;
    int val;
    int bytesRead = ::read(filedesc, &val, sizeof(int));
    if (bytesRead == 0) b = true;
    lseek(filedesc, -bytesRead, SEEK_CUR);
    return b;
}

void InputStreamC::close() {
    ::close(filedesc);
}

