//
// Created by martin on 9/28/16.
//

#include <sstream>
#include <queue>
#include <iostream>
#include "Part3.h"
#include "BinElement.h"
#include "Binary.h"
#include "InputStreamC.h"
#include "InputStreamC.h"
#include "OutputStreamC.h"
#include "Quicksort.h"


Part3::Part3(int N, int M, int d, char* file) {

    int div = N/M;
    InputStreamC* is = new InputStreamC(8192);
    is->open(file);

    // Placer div antal filer på disken.
    vector<string> vs(div+1);
    int internalArray[M];
    Quicksort* q = new Quicksort();

    int j = 0;
    int r = 0;
    for(int i = 0; i < N; i++) {
        internalArray[j] = is->readNext();
        j++;

        if(j == M) {

            // SORTER!
            q->sort(internalArray,0,M-1);

            OutputStreamC* os = new OutputStreamC(8192);
            ostringstream oss;
            oss << r;
            string s = "part3" + oss.str();
            char test[s.size()];
            strncpy(test, s.c_str(), s.size());
            vs[r] = test;
            os->create(test);

            for(int x = 0; x < M; x++) {
                int temp = internalArray[x];
                os->write(&temp);
                //cout << "Writing: " << temp << "\n";
            }

            os->close();
            r++;
            j=0;
        }



        else if(i == N-1 && N%M != 0) {
            // Eventuel rest

            // SORTER!
            q->sort(internalArray,0,(N%M)-1);

            OutputStreamC* os = new OutputStreamC(8192);
            ostringstream oss;
            oss << r;
            string s = "part3" + oss.str();
            char test[s.size()];
            strncpy(test, s.c_str(), s.size());
            vs[r] = test;
            os->create(test);

            for(int x = 0; x < N%M; x++) {
                int temp = internalArray[x];
                os->write(&temp);
                //cout << "Writing: " << temp << "\n";
            }

            r++;
            os->close();
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
    merge(d, r, vs, test, 1);

}

Part3::~Part3() {
    // TODO Auto-generated destructor stub
}

void Part3::merge(int d, int n, vector<string> vs, char* out, int depth) {
    if(n > d) {
        int r = 0;
        int j = 0;
        vector<string> vs2(n/d); // Til at sende strings videre med
        vector<string> vs3(d+1); // De strings vi får tilbage
        // Divide
        for(int i = 0; i < n; i++) {
            vs2[j] = vs[i];
            j++;
            if(j == n/d) {
                ostringstream oss;
                oss << r;
                ostringstream oss2;
                oss2 << depth;
                string s = "p" + oss2.str() + "part" + oss.str();
                //cout << s << "\n";
                char test[s.size()];
                strncpy(test, s.c_str(), s.size());
                vs3[r] = test;
                merge(d, n/d, vs2, test, depth+1);
                r++;
                j=0;
            }
            else if(i == n-1 && n%d != 0) {
                // Til at behandle en eventuel rest mængde
                ostringstream oss;
                oss << r;
                ostringstream oss2;
                oss2 << depth;
                string s = "p" + oss2.str() + "part" + oss.str();
                char test[s.size()];
                strncpy(test, s.c_str(), s.size());
                vs3[r] = test;
                merge(d, n%d, vs2, test, depth+1);
                r++;
            }
        }

        // Merge sammen igen
        dwaymerging(r,vs3, out);


    }
    else {
        // Conquor!
        dwaymerging(n,vs, out);
    }
}


void Part3::dwaymerging(int d, vector<string> vs, char* out) {

    //cout << "Dway merging " << d << " in " << out << "\n";

    int org_d = d;


    //char test[] = "test2";
    InputStreamC* istreams[d];
    for(int i = 0; i < d; i++) {
        istreams[i] = new InputStreamC(8192);
        string s = vs[i];
        char test[s.size()];
        strncpy(test, s.c_str(), s.size());
        istreams[i]->open(test);
    }

    BinElement* binArray[d+2];
    Binary* binary = new Binary();

    for(int i = 0; i < d; i++) {
        BinElement* temp = new BinElement(i, istreams[i]->readNext());
        binArray[i+1] = temp;
        //cout << "Put " << temp->value << "\n";
    }

    binary->setheap(binArray, d);

    OutputStreamC* os = new OutputStreamC(8192);
    os->create(out);


    int count = d;
    bool running = true;

    while(running) {

        if(d == 0) {
            running = false;
        }
        else {
            BinElement* binOut = binary->outheap(binArray, d);
            int outInt = binOut->value;
            os->write(&outInt);
            //cout << out << " Value = " << binOut->value << "\n";

            if(!istreams[binOut->id]->endOfStream()) {
                binOut->value = istreams[binOut->id]->readNext();
                //cout << "Inserting = " << binOut->value << "\n";
                binary->inheap(binArray, d-1, binOut);
                count++;
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

    //cout << "Count was " << count << "\n";
}