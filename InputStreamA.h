/*
 * InputStream.h
 *
 *  Created on: 16/09/2016
 *      Author: Martin
 */


#ifndef INPUTSTREAM_H_
#define INPUTSTREAM_H_

using namespace std;

class InputStreamA {
public:
	int filedesc;
	InputStreamA();
	virtual ~InputStreamA();
	int open(char* s);
	int readNext();
	bool endOfStream();
	void close();
};

#endif /* INPUTSTREAM_H_ */
