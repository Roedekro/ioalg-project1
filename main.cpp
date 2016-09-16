#include <iostream>
#include "InputStreamA.h"
#include "OutputStreamA.h"


int main() {
    char file[] = "testfile";

    OutputStreamA * os = new OutputStreamA;
    os->create(file);
    int number = 42;
    os->write(&number);
    os->close();

    InputStreamA * is = new InputStreamA;
    is->open(file);
    int test = is->readNext();

    cout << test;

    return 0;
}