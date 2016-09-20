#include <iostream>
#include "InputStreamD.h"
#include "OutputStreamD.h"
#include <stdio.h>
#include <queue>
#include <unistd.h>


int main() {

    cout << "Page Size: " << getpagesize() << '\n';

    char file[] = "testfile";

    int bufferSize = 2;

    OutputStreamD * os = new OutputStreamD(16);
    os->create(file);
    int number = 42;
    os->write(&number);
    int number2 = 34;
    os->write(&number2);
    int number3 = 11;
    os->write(&number3);
    int number4 = 3030303;
    os->write(&number4);
    for(int i = 0; i < 10; i++) {
        os->write(&i);
    }
    os->close();

    cout << "OutStream Success\n";


    InputStreamD * is = new InputStreamD(16);
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

    for(int i = 0; i < 10; i++) {
        cout << is->readNext() << '\n';
    }

    is->close();

    return 0;
}