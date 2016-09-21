/*
 * BinElement.h
 *
 *  Created on: 29/09/2015
 *      Author: Martin
 */

#ifndef BINELEMENT_H_
#define BINELEMENT_H_

class BinElement {
public:
    BinElement(int id, int value);
    virtual ~BinElement();
    int id;
    int value;
};

#endif /* BINELEMENT_H_ */

