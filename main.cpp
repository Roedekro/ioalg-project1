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
#include <sstream>
#include <cstring>
#include "OutputStream.h"
#include "Binary.h"
#include "BinElement.h"
#include "Quicksort.h"
#include "Part3.h"

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

void testWrites(int n) {

    long time_testA = 0;
    long time_testB = 0;
    long time_testC = 0;
    long time_testD = 0;
    struct timeval te1;
    struct timeval te2;
    int r = 10;

    for(int i = 0; i < r; i++) {
        cout << "Run " << i+1 << '\n';

        /*gettimeofday(&te1,NULL);
        OutputStreamA* osA = new OutputStreamA();
        char testA[] = "testWA";
        osA->create(testA);
        for(int j = 0; j < n; j++) {
            osA->write(&j);
        }
        osA->close();
        gettimeofday(&te2,NULL);
        time_testA = time_testA + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
*/
        /*gettimeofday(&te1,NULL);
        OutputStreamB* osB = new OutputStreamB();
        char testB[] = "testWB";
        osB->create(testB);
        for(int j = 0; j < n; j++) {
            osB->write(&j);
        }
        osB->close();
        gettimeofday(&te2,NULL);
        time_testB = time_testB + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;

        cout << "Test B Completed\n"; */
        gettimeofday(&te1,NULL);
        OutputStreamC* osC = new OutputStreamC(131072);
        char testC[] = "testWC";
        osC->create(testC);
        for(int j = 0; j < n; j++) {
            osC->write(&j);
        }
        osC->close();
        gettimeofday(&te2,NULL);
        time_testC = time_testC + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;

        /*gettimeofday(&te1,NULL);
        OutputStreamD* osD = new OutputStreamD(32768, n);
        char testD[] = "testWD";
        osD->create(testD);
        for(int j = 0; j < n; j++) {
            osD->write(&j);
        }
        osD->close();
        gettimeofday(&te2,NULL);
        time_testD = time_testD + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
         */
    }

    if(time_testA > 0) time_testA = time_testA / r;
    if(time_testB > 0) time_testB = time_testB / r;
    if(time_testC > 0) time_testC = time_testC / r;
    if(time_testD > 0) time_testD = time_testD / r;

    cout << "Write test. Times in milliseconds averaged over runs:\n";
    cout << "TestA " << time_testA << '\n';
    cout << "TestB " << time_testB << '\n';
    cout << "TestC " << time_testC << '\n';
    cout << "TestD " << time_testD << '\n';
}

void testReads(int n) {

    long time_testA = 0;
    long time_testB = 0;
    long time_testC = 0;
    long time_testD = 0;
    struct timeval te1;
    struct timeval te2;
    int r = 10;

    for(int i = 0; i < r; i++) {
        cout << "Run " << i+1 << '\n';

        /*gettimeofday(&te1,NULL);
        InputStreamA* isA = new InputStreamA();
        char testA[] = "testWA";
        isA->open(testA);
        for(int j = 0; j < n; j++) {
            isA->readNext();
        }
        isA->close();
        gettimeofday(&te2,NULL);
        time_testA = time_testA + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        cout << "Test A Completed\n";
*/
        /*gettimeofday(&te1,NULL);
        InputStreamB* isB = new InputStreamB();
        char testB[] = "testWB";
        isB->open(testB);
        for(int j = 0; j < n; j++) {
            isB->readNext();
        }
        isB->close();
        gettimeofday(&te2,NULL);
        time_testB = time_testB + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        cout << "Test B Completed\n";
*/
        gettimeofday(&te1,NULL);
        InputStreamC* isC = new InputStreamC(131072);
        char testC[] = "testWC";
        isC->open(testC);
        for(int j = 0; j < n; j++) {
            isC->readNext();
        }
        isC->close();
        gettimeofday(&te2,NULL);
        time_testC = time_testC + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
        cout << "Test C Completed\n";

        /*gettimeofday(&te1,NULL);
        InputStreamD* isD = new InputStreamD(32768,n);
        char testD[] = "testWD";
        isD->open(testD);
        for(int j = 0; j < n; j++) {
            isD->readNext();
        }
        isD->close();
        gettimeofday(&te2,NULL);
        time_testD = time_testD + (te2.tv_sec - te1.tv_sec) * 1000 + (te2.tv_usec - te1.tv_usec) / 1000;
         */
    }

    if(time_testA > 0) time_testA = time_testA / r;
    if(time_testB > 0) time_testB = time_testB / r;
    if(time_testC > 0) time_testC = time_testC / r;
    if(time_testD > 0) time_testD = time_testD / r;

    cout << "Read test. Times in milliseconds averaged over runs:\n";
    cout << "TestA " << time_testA << '\n';
    cout << "TestB " << time_testB << '\n';
    cout << "TestC " << time_testC << '\n';
    cout << "TestD " << time_testD << '\n';
}

void generateDwaymergingFiles(int n, int d) {

    char ourString[] = "test2";

    //char test[] = "test2";
    for(int i = 0; i < d; i++) {
        //test = "test2" + i;
       // stringstream ss;
        //ss << ourString << i;
       // test = ss.str().c_str();

        OutputStreamD* os = new OutputStreamD(32768, n);
        ostringstream oss;
        oss << i;
        string s = "test2" + oss.str();
        char test[s.size()];
        strncpy(test, s.c_str(), s.size());
        //cout << "Creating " << test << "\n";
        os->create(test);
        for(int j = 0; j < n; j++) {
            os->write(&j);
            //cout << "Writing " << j << "\n";
        }
        os->close();
    }

    /*InputStreamD* is = new InputStreamD(32768, 10);
    char test[] = "test23";
    is->open(test);
    cout << "Reading " << is->readNext() << "\n";
    cout << "Reading " << is->readNext() << "\n";
    cout << "Reading " << is->readNext() << "\n";
    cout << "Reading " << is->readNext() << "\n";
    is->close();*/
}


void dwaymerging(int d, int n) {

    int org_d = d;

    char ourString[] = "test2";

    //char test[] = "test2";
    InputStream* istreams[d];
    for(int i = 0; i < d; i++) {
        istreams[i] = new InputStreamD(32768, n);
        ostringstream oss;
        oss << i;
        string s = "test2" + oss.str();
        char test[s.size()];
        strncpy(test, s.c_str(), s.size());
        istreams[i]->open(test);
    }

    BinElement* binArray[d+2];
    Binary* binary = new Binary();

    for(int i = 0; i < d; i++) {
        BinElement* temp = new BinElement(i, istreams[i]->readNext());
        binArray[i+1] = temp;
    }

    binary->setheap(binArray, d);

    OutputStreamD* os = new OutputStreamD(32768, n);
    char test[] = "test2out";
    os->create(test);

    bool running = true;

    while(running) {

        if(d == 0) {
            running = false;
        }
        else {
            BinElement* binOut = binary->outheap(binArray, d);
            int out = binOut->value;
            os->write(&out);
            //cout << "Value = " << binOut->value << "\n";

            if(!istreams[binOut->id]->endOfStream()) {
                binOut->value = istreams[binOut->id]->readNext();
                //cout << "Inserting = " << binOut->value << "\n";
                binary->inheap(binArray, d, binOut);
            }
            else {
                d--;
            }
        }
    }

    d = org_d;

    for(int i = 0; i < d; i++) {
        istreams[i]->close();
        delete(istreams[i]);
    }
    //delete(istreams);

    for(int i = 0; i < org_d; i++) {
       //delete(binArray[i+1]); Kan vi ikke da vi har tømt binarray
    }
    //delete(binArray);
    delete(binary);

    os->close();
    delete(os);

}

void testQuick() {

    int a[10];
    a[0] = 2;
    a[1] = 4;
    a[2] = 5;
    a[3] = 7;
    a[4] = 8;
    a[5] = 9;
    a[6] = 1;
    a[7] = 10;
    a[8] = 6;
    a[9] = 3;

    Quicksort* q = new Quicksort();
    q->sort(a,0,9);

    for(int i = 0; i < 10; i++) {
        cout << a[i] << "\n";
    }
}

void testPart3() {
    char test[] = "testPart3Input";
    OutputStreamB* os = new OutputStreamB();
    os->create(test);
    int j = 2;
    os->write(&j);
    j= 4;
    os->write(&j);
    j= 5;
    os->write(&j);
    j= 7;
    os->write(&j);
    j= 8;
    os->write(&j);
    j= 9;
    os->write(&j);
    j= 1;
    os->write(&j);
    j= 10;
    os->write(&j);
    j= 6;
    os->write(&j);
    j= 3;
    os->write(&j);

    os->close();

    Part3* p3 = new Part3(10,8,2,test);

    char test2[] = "part3out";
    InputStreamB* is = new InputStreamB();
    is->open(test2);
    for(int i = 0; i < 10; i++) {
        cout << is->readNext() << "\n";
    }
    is->close();
}

void testPart32(int n, int m, int d) {
    char test[] = "testPart3Input";
    OutputStreamB *os = new OutputStreamB();
    os->create(test);
    for(int i = 0; i < n; i++) {
        int x = rand() % 1000000;
        os->write(&x);
    }
    os->close();

    Part3 *p3 = new Part3(n, m, d, test);

    char test2[] = "part3out";
    InputStreamB *is = new InputStreamB();
    is->open(test2);
    int prev = 0;
    for (int i = 0; i < 10; i++) {
        int x = is->readNext();
        if(x < prev) {
            cout << "Test Part3-2 failed " << x << " " << prev << "\n";
        }
        prev = x;
    }
    is->close();
}



int main(int argc, char* argv[]) {

    int test_type, b, n ,r;
    if(argc == 1) {
        test_type = 2; // v1.2
        b = 4096;
        n = 1000000;
        r = 10;
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
    else if(test_type == 7) {
        testAvsD(b,n);
    }
    else if(test_type == 8) {
        generateDwaymergingFiles(n, 4);
        dwaymerging(4,n);
    }
    else if(test_type == 9) {
        testWrites(n);
    }
    else if(test_type == 10) {
        testReads(n);
    }
    else if(test_type == 11) {
        testQuick();
    }
    else if(test_type == 12) {
        testPart3();
    }
    else if(test_type == 13) {
        testPart32(n,b,r);
    }
    //test1();

    return 0;
}