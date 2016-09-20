#include <iostream>
#include "InputStreamC.h"
#include "OutputStreamC.h"
#include <stdio.h>
#include <queue>


int main() {
    char file[] = "testfile";

    int bufferSize = 2;

    OutputStreamC * os = new OutputStreamC(bufferSize);
    os->create(file);
    int number = 42;
    os->write(&number);
    int number2 = 34;
    os->write(&number2);
    int number3 = 11;
    os->write(&number3);
    os->close();

    InputStreamC * is = new InputStreamC(bufferSize);
    is->open(file);

    //int test = is->readNext();

    //cout << test;

    cout << is->readNext();
    cout << is->endOfStream();
    cout << is->readNext();
    cout << is->endOfStream();
    cout << is->readNext();
    cout << is->endOfStream();

    return 0;
}