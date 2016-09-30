//
// Created by martin on 9/28/16.
//

#include <sstream>
#include <queue>
#include "Part3.h"
#include "InputStreamD.h"
#include "OutputStreamD.h"
#include "BinElement.h"
#include "Binary.h"


Part3::Part3(int N, int M, int d, char* file) {

    int div = N/M;
    InputStreamD* is = new InputStreamD(32768, N);
    is->open(file);

    // Placer div antal filer på disken.
    vector<string> vs(div+1);
    int internalArray[M];

    int j = 0;
    int r = 0;
    for(int i = 0; i < N; i++) {
        internalArray[j] = is->readNext();
        j++;

        if(j == M) {

            // SORTER!


            OutputStreamD* os = new OutputStreamD(32768, M);
            ostringstream oss;
            oss << r;
            string s = "part3" + oss.str();
            char test[s.size()];
            strncpy(test, s.c_str(), s.size());
            vs[r] = test;
            os->create(test);

            for(int j = 0; j < M; j++) {
                int temp = internalArray[j];
                os->write(&temp);
            }

            r++;
            j=0;
        }



        if(i == N-1) {
            // Eventuel rest

            // SORTER!

            OutputStreamD* os = new OutputStreamD(32768, N%div);
            ostringstream oss;
            oss << r;
            string s = "part3" + oss.str();
            char test[s.size()];
            strncpy(test, s.c_str(), s.size());
            vs[r] = test;
            os->create(test);

            for(int j = 0; j < N&div; j++) {
                int temp = internalArray[j];
                os->write(&temp);
            }

            r++;
        }
    }


    /*for(int i = 0; i < div; i++) {

        for(int j = 0; j < M; j++) {
            internalArray[j] = is->readNext();


        }

        // sorter internalArray

        OutputStreamD* os = new OutputStreamD(32768, M);
        ostringstream oss;
        oss << i;
        string s = "part3" + oss.str();
        char test[s.size()];
        strncpy(test, s.c_str(), s.size());
        vs[i] = test;
        os->create(test);

        for(int j = 0; j < M; j++) {
            int temp = internalArray[j];
            os->write(&temp);
        }

    }*/


    // Merge
    char test[] = "part3out";
    merge(d, div, M, vs, test, 1);

}

Part3::~Part3() {
    // TODO Auto-generated destructor stub
}

void Part3::merge(int d, int count, int n, vector<string> vs, char* out, int depth) {
    if(count > d) {
        int r = 0;
        int j = 0;
        vector<string> vs2(n/d); // Til at sende strings videre med
        vector<string> vs3(n/d+1); // De strings vi får tilbage
        // Divide
        for(int i = 0; i < n; i++) {
            vs2[r] = vs[i];
            j++;
            if(j == d) {
                ostringstream oss;
                oss << r;
                ostringstream oss2;
                oss2 << depth;
                string s = oss2.str() + "part" + oss.str();
                char test[s.size()];
                strncpy(test, s.c_str(), s.size());
                vs3[r] = test;
                merge(d, count/d, n, vs2, test, depth+1);
                r++;
                j=0;
            }
            else if(i == n-1) {
                // Til at behandle en eventuel rest mængde
                ostringstream oss;
                oss << r;
                ostringstream oss2;
                oss2 << depth;
                string s = oss2.str() + "part" + oss.str();
                char test[s.size()];
                strncpy(test, s.c_str(), s.size());
                vs3[r] = test;
                merge(d, count%(count/d), n, vs2, test, depth+1);
                r++;
            }
        }

        // Merge sammen igen



    }
    else {
        // Conquor!

    }
}


void Part3::dwaymerging(int d, int n, vector<string> vs, char* out) {

    int org_d = d;


    //char test[] = "test2";
    InputStream* istreams[d];
    for(int i = 0; i < d; i++) {
        istreams[i] = new InputStreamD(32768, n);
        ostringstream oss;
        oss << d+i;
        string s = "type3" + oss.str();
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
    os->create(out);

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
        // delete(binArray[i+1]);
    }
    //delete(binArray);
    delete(binary);

    os->close();
    delete(os);

}