#include <iostream>
#include "InputStreamD.h"
#include "OutputStreamD.h"
#include <stdio.h>
#include <queue>


int main() {
    char file[] = "testfile";

    int bufferSize = 2;

    OutputStreamD * os = new OutputStreamD();
    os->create(file);
    int number = 42;
    os->write(&number);
    int number2 = 34;
    os->write(&number2);
    int number3 = 11;
    os->write(&number3);
    int number4 = 3030303;
    os->write(&number4);
    os->close();

    InputStreamD * is = new InputStreamD();
    is->open(file);

    //int test = is->readNext();

    //cout << test;

    cout << "readNext: " << is->readNext() << '\n';
    cout << "endOfStream: " << is->endOfStream() << '\n';
    cout << "readNext: " << is->readNext() << '\n';
    cout << "endOfStream: " << is->endOfStream() << '\n';
    cout << "readNext: " << is->readNext() << '\n';
    cout << "endOfStream: " << is->endOfStream() << '\n';
    cout << "readNext: " << is->readNext() << '\n';
    cout << "endOfStream: " << is->endOfStream() << '\n';

    return 0;
}