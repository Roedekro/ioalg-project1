

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

