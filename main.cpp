#include <iostream>
#include "InputStreamB.h"
#include "OutputStreamB.h"
#include <stdio.h>
#include <queue>


int main() {
    char file[] = "testfile";

    OutputStreamB * os = new OutputStreamB;
    os->create(file);
    int number = 42;
    os->write(&number);
    int number2 = 34;
    os->write(&number2);
    os->close();

    InputStreamB * is = new InputStreamB;
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