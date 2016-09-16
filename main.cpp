#include <iostream>
#include "InputStreamA.h"
#include "OutputStreamA.h"


int main() {
    char file[] = "testfile";

    OutputStreamA * os = new OutputStreamA;
    os->create(file);
    int number = 42;
    os->write(&number);
    int number2 = 34;
    os->write(&number2);
    os->close();

    InputStreamA * is = new InputStreamA;
    is->open(file);

    //int test = is->readNext();

    //cout << test;

    cout << is->readNext();
    cout << is->endOfStream();
    cout << is->readNext();
    cout << is->endOfStream();
    cout << is->readNext();
    //cout << is->endOfStream();

    return 0;
}