/*
 * OutputStream.cpp
 *
 *  Created on: 16/09/2016
 *      Author: Martin
 */

#include "OutputStreamB.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

OutputStreamB::OutputStreamB() {

}

OutputStreamB::~OutputStreamB() {
    // TODO Auto-generated destructor stub
}

void OutputStreamB::create(char* s) {
    file = fopen(s, "wb");
}

int OutputStreamB::write(int* number) {
    return fwrite(number, sizeof(int), 1, file);
}

void OutputStreamB::close() {
    fclose(file);
}