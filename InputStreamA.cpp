/*
 * InputStream.cpp
 *
 *  Created on: 16/09/2016
 *      Author: Martin
 */

#include "InputStreamA.h"
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

InputStreamA::InputStreamA() {
	filedesc = -1;
}

InputStreamA::~InputStreamA() {
	// TODO Auto-generated destructor stub
}

int InputStreamA::open(char* s) {
	filedesc = ::open(s, O_RDONLY);
	return filedesc;
}

int InputStreamA::readNext() {
	int ret;
	::read(filedesc, &ret , 4);
	return ret;
}

bool InputStreamA::endOfStream() {
	bool b = false;
	int val;
	::read(filedesc, &val , 4);
	if (val == 0) b = true;
	lseek(filedesc, -4, SEEK_CUR );
	return b;
}

void InputStreamA::close() {
	::close(filedesc);
}
