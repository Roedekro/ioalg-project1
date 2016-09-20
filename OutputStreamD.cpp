//
// Created by soren on 9/20/16.
//

#include "OutputStreamD.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

OutputStreamD::OutputStreamD() {
    filedesc = 0;
    index = 0;
}

OutputStreamD::~OutputStreamD() {
    // TODO Auto-generated destructor stub
}

void OutputStreamD::create(char* s) {
    //file = fopen(s, "w+");
    //filedesc = fileno(file);
    filedesc = open(s, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    //fseek(file, 0, SEEK_END);
    fileSize = 8;
    map = (int *) mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, filedesc, 0);
    if (map == MAP_FAILED) {
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
}

int OutputStreamD::write(int* number) {
    map[index] = 422;
    index++;
    return 0;
}

void OutputStreamD::close() {
    fclose(file);
    munmap(&filedesc, fileSize);
}