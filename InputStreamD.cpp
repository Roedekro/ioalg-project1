/*
 * InputStream.cpp
 *
 *  Created on: 16/09/2016
 *      Author: Martin
 */

#include "InputStreamD.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

InputStreamD::InputStreamD() {
    index = 0;
    filedesc = -1;
    fileSize = 0;
}

InputStreamD::~InputStreamD() {
    // TODO Auto-generated destructor stub
}

int InputStreamD::open(char* s) {
    file = fopen(s, "r+");
    filedesc = fileno(file);
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    map = (int *) mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, filedesc, 0);
    if (map == MAP_FAILED) {
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    return filedesc;
}

int InputStreamD::readNext() {
    if (index == fileSize / sizeof(int)) {
        return -1;
    }

    int elm = map[index];
    index++;
    return elm;
}

bool InputStreamD::endOfStream() {
    return index == fileSize / sizeof(int);
}

void InputStreamD::close() {
    fclose(file);
    munmap(map, fileSize);
}
