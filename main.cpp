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

    OutputStreamD * os = new OutputStreamD(16,14);
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


    InputStreamD * is = new InputStreamD(16,14);
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

    OutputStreamD* os = new OutputStreamD(b,n);
    InputStreamD* is = new InputStreamD(b,n);

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

void testAvsD(int b, int n) {

    /*
     * Hvis den giver segmentation fault så rename filen.
     * /o\
     * Den er testet, og begge inputstreams giver samme resultat.
     */

    OutputStreamB* os = new OutputStreamB();
    char test[] = "testAvsD";
    os->create(test);
    for(int i = 0; i < n; i++) {
        os->write(&i);
    }
    os->close();

    cout << "Output\n";

    int * as = new int[n];
    int * ds = new int[n];

    InputStreamA* isA = new InputStreamA();
    isA->open(test);
    for(int i = 0; i < n; i++) {
        as[i] = isA->readNext();
    }
    isA->close();

    cout << "InputA\n";

    sleep(1);
    InputStreamD* isD = new InputStreamD(b,n);
    isD->open(test);
    for(int i = 0; i < n; i++) {
        ds[i] = isD->readNext();
    }
    isD->close();

    for (int i = 0; i < n; i++) {
        if (as[i] != ds[i]) {
            cout << "!!!!!!!!!!!!!!!!\n";
        }
    }
}

void testAll(int b, int n, int r) {

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
        testD(b,n);
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
}

int main(int argc, char* argv[]) {

    int test_type, b, n ,r;
    if(argc == 1) {
        test_type = 1; // v1.1
        b = 4096;
        n = 240000;
        r = 1;
    }
    else {
        test_type = atoi(argv[1]);
        b = atoi(argv[2]);
        n = atoi(argv[3]);
        r = atoi(argv[4]);
    }

    cout << "Running test type " << test_type << " with B = " << b << " and N = " << n << " for " << r << " runs\n";

    if(test_type == 1) {
        testAll(b, n, r);
    }
    else if(test_type == 2) {
        long time_testA = 0;
        struct timeval te1;
        struct timeval te2;

        for(int i = 0; i < r; i++) {
            gettimeofday(&te1,NULL);
            testA(b,n);
            gettimeofday(&te2,NULL);
            time_testA = time_testA + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        }

        if(time_testA > 0) time_testA = time_testA / r;
        cout << "Times in milliseconds averaged over runs:\n";
        cout << "TestA " << time_testA << '\n';
    }
    else if(test_type == 3) {
        long time_testB = 0;
        struct timeval te1;
        struct timeval te2;

        for(int i = 0; i < r; i++) {
            gettimeofday(&te1,NULL);
            testB(b,n);
            gettimeofday(&te2,NULL);
            time_testB = time_testB + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        }

        if(time_testB > 0) time_testB = time_testB / r;
        cout << "Times in milliseconds averaged over runs:\n";
        cout << "TestB " << time_testB << '\n';
    }
    else if(test_type == 4) {
        long time_testC = 0;
        struct timeval te1;
        struct timeval te2;

        for(int i = 0; i < r; i++) {
            gettimeofday(&te1,NULL);
            testC(b,n);
            gettimeofday(&te2,NULL);
            time_testC = time_testC + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        }

        if(time_testC > 0) time_testC = time_testC / r;
        cout << "Times in milliseconds averaged over runs:\n";
        cout << "TestC " << time_testC << '\n';
    }
    else if(test_type == 5) {
        long time_testD = 0;
        struct timeval te1;
        struct timeval te2;

        for(int i = 0; i < r; i++) {
            gettimeofday(&te1,NULL);
            testD(b,n);
            gettimeofday(&te2,NULL);
            time_testD = time_testD + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        }

        if(time_testD > 0) time_testD = time_testD / r;
        cout << "Times in milliseconds averaged over runs:\n";
        cout << "TestD " << time_testD << '\n';
    }
    else if(test_type == 6) {
        test1();
    }
    else if(test_type = 7) {
        testAvsD(b,n);
    }
    //test1();

    return 0;
}