#ifndef NBZ_BOX_H
#define NBZ_BOX_H


class Box {


public:
    Box(int x, int y);
    void renderBoxes();
    void destroyBox();


private:
    int x;
    int y;
    bool destroyed;


};


#endif
