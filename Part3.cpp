//
// Created by martin on 9/28/16.
//

#include <sstream>
#include <cstring>
#include "Part3.h"
#include "InputStreamD.h"
#include "OutputStreamD.h"

Part3::Part3(int N, int M, int d, char* file) {

    int div = N/M;
    InputStreamD* is = new InputStreamD(32768, N);
    is->open(file);

    OutputStreamD* os = new OutputStreamD(32768, div);
    int internalArray[M];
    for(int i = 0; i < div; i++) {

        for(int j = 0; j < M; j++) {
            internalArray[j] = is->readNext();


        }

        // sorter internalArray

        OutputStreamD* os = new OutputStreamD(32768, div);
        ostringstream oss;
        oss << i;
        string s = "test3" + oss.str();
        char test[s.size()];
        strncpy(test, s.c_str(), s.size());
        os->create(test);

        for(int j = 0; j < M; j++) {
            int temp = internalArray[j];
            os->write(&temp);
        }

    }


}