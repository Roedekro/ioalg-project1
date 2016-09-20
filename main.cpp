#include <iostream>
#include "InputStreamA.h"
#include "OutputStreamA.h"
#include "InputStreamB.h"
#include "OutputStreamB.h"
#include "InputStreamC.h"
#include "OutputStreamC.h"
#include "InputStreamD.h"
#include "OutputStreamD.h"
#include <stdio.h>
#include <queue>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "OutputStream.h"

void test1() {
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
}

void testA(int b, int n) {

    OutputStreamA* os = new OutputStreamA();
    InputStreamA* is = new InputStreamA();

    char test[] = "testA";
    os->create(test);
    for(int i = 0; i < n; i++) {
        os->write(&i);
    }
    os->close();

    is->open(test);
    for(int i = 0; i < n; i++) {
        is->readNext();
    }
    is->close();

}

void testB(int b, int n) {

    OutputStreamB* os = new OutputStreamB();
    InputStreamB* is = new InputStreamB();

    char test[] = "testB";
    os->create(test);
    for(int i = 0; i < n; i++) {
        os->write(&i);
    }
    os->close();

    is->open(test);
    for(int i = 0; i < n; i++) {
        is->readNext();
    }
    is->close();

}

void testC(int b, int n) {

    OutputStreamC* os = new OutputStreamC(b);
    InputStreamC* is = new InputStreamC(b);

    char test[] = "testC";
    os->create(test);
    for(int i = 0; i < n; i++) {
        os->write(&i);
    }
    os->close();

    is->open(test);
    for(int i = 0; i < n; i++) {
        is->readNext();
    }
    is->close();

}

void testD(int b, int n) {

    OutputStreamD* os = new OutputStreamD(b);
    InputStreamD* is = new InputStreamD(b);

    char test[] = "testD";
    os->create(test);
    for(int i = 0; i < n; i++) {
        os->write(&i);
    }
    os->close();

    is->open(test);
    for(int i = 0; i < n; i++) {
        is->readNext();
    }
    is->close();

}

int main(int argc, char* argv[]) {

    int b, n ,r;
    if(argc == 1) {
        b = 4096;
        n = 24000000;
        r = 1;
    }
    else {
        b = atoi(argv[1]);
        n = atoi(argv[2]);
        r = atoi(argv[3]);
    }

    cout << "Running tests with B = " << b << " and N = " << n << " for " << r << " runs\n";

    long time_testA = 0;
    long time_testB = 0;
    long time_testC = 0;
    long time_testD = 0;
    struct timeval te1;
    struct timeval te2;

    for(int i = 0; i < r; i++) {
        cout << "Run " << i+1 << '\n';

        gettimeofday(&te1,NULL);
        testA(b,n);
        gettimeofday(&te2,NULL);
        time_testA = time_testA + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;

        gettimeofday(&te1,NULL);
        testB(b,n);
        gettimeofday(&te2,NULL);
        time_testB = time_testB + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;

        gettimeofday(&te1,NULL);
        testC(b,n);
        gettimeofday(&te2,NULL);
        time_testC = time_testC + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;

        gettimeofday(&te1,NULL);
        //testD(b,n);
        gettimeofday(&te2,NULL);
        time_testD = time_testD + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
    }

    if(time_testA > 0) time_testA = time_testA / r;
    if(time_testB > 0) time_testB = time_testB / r;
    if(time_testC > 0) time_testC = time_testC / r;
    if(time_testD > 0) time_testD = time_testD / r;

    cout << "Times in milliseconds averaged over runs:\n";
    cout << "TestA " << time_testA << '\n';
    cout << "TestB " << time_testB << '\n';
    cout << "TestC " << time_testC << '\n';
    cout << "TestD " << time_testD << '\n';
    //test1();

    return 0;
}