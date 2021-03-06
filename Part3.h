//
// Created by martin on 9/28/16.
//

#ifndef IOALG_PROJECT1_PART3_H
#define IOALG_PROJECT1_PART3_H

#include <cstring>
#include <vector>
#include <string>

class Part3 {

public:
    Part3(int N, int M, int d, const char* file);
    virtual ~Part3();
    void merge(int d, int n, std::vector<std::string> vs, const char* out, int depth);
    void dwaymerging(int d, std::vector<std::string> vs, const char* out);

};


#endif //IOALG_PROJECT1_PART3_H
