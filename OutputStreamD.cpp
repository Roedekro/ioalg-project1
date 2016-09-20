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
#include <errno.h>
#include <string.h>

using namespace std;

OutputStreamD::OutputStreamD(int portionSize) {
    filedesc = 0;
    index = 0;
    this->portionSize = portionSize;
    portionIndex = 0;
}

OutputStreamD::~OutputStreamD() {
    // TODO Auto-generated destructor stub
}

void OutputStreamD::create(char* s) {
    filedesc = open(s, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

    lseek(filedesc, 4 * 10000 + 1, SEEK_SET);
    ::write(filedesc, "", 1);
    lseek(filedesc, 0, SEEK_SET);

    //fseek(file, 0, SEEK_END);
    //fileSize = 8;
    // MAP_SHARED works on VM, MAP_Private does not work on a VM
    map = (int *) mmap(0, portionSize, PROT_READ | PROT_WRITE, MAP_SHARED, filedesc, 0);
    if (map == MAP_FAILED) {
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
}

int OutputStreamD::write(int* number) {
    if(index == portionSize / sizeof(int)) {
        munmap(map, portionSize);
        portionIndex++;
        //map = (int *) mmap(0, portionSize, PROT_READ | PROT_WRITE, MAP_SHARED, filedesc, portionIndex * portionSize);
        // Ignore portionIndex, offset must be a multiplum of pagesize
        map = (int *) mmap(0, portionSize, PROT_READ | PROT_WRITE, MAP_SHARED, filedesc, getpagesize()*portionIndex);
        if (map == MAP_FAILED) {
            perror("Error mmapping the file");
            exit(EXIT_FAILURE);
        }
        index=0;
    }
    map[index] = *number;
    index++;
    return 0;
}

void OutputStreamD::close() {
    //munmap(&filedesc, portionSize);
    if(munmap(map, portionSize) == -1) {
        printf ("Error errno is: %s\n",strerror(errno));
        perror("Error unmapping the file");
        exit(EXIT_FAILURE);
    }
    ::close(filedesc);
}