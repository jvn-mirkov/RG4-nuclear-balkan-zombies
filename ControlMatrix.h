#ifndef NBZ_CONTROLMATRIX_H
#define NBZ_CONTROLMATRIX_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

class ControlMatrix {

private:


public:
    char mx[13][15] = {{'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z'},
                       {'Z', '0', '0', '0', '0', 'B', 'B', 'B', 'B', 'B', '0', '0', '0', '0', 'Z'},
                       {'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', 'B', 'Z', '0', 'Z', '0', 'Z'},
                       {'Z', '0', 'B', '0', '0', 'B', 'B', '0', 'B', 'B', 'B', '0', 'B', '0', 'Z'},
                       {'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', 'B', 'Z'},
                       {'Z', 'B', 'B', 'B', 'B', 'B', 'B', '0', 'B', '0', '0', 'B', 'B', 'B', 'Z'},
                       {'Z', 'B', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', 'B', 'Z'},
                       {'Z', 'B', '0', '0', '0', 'B', 'B', 'B', 'B', 'B', 'B', 'B', '0', 'B', 'Z'},
                       {'Z', 'B', 'Z', '0', 'Z', '0', 'Z', 'B', 'Z', '0', 'Z', '0', 'Z', 'B', 'Z'},
                       {'Z', '0', 'B', '0', '0', 'B', 'B', '0', 'B', '0', 'B', '0', 'B', '0', 'Z'},
                       {'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z', '0', 'Z'},
                       {'Z', '0', '0', '0', 'B', 'B', 'B', '0', '0', 'B', 'B', '0', '0', '0', 'Z'},
                       {'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z', 'Z'}};

    ControlMatrix();

    std::string checkField(float x, float y);

    void showMatrix();

};


#endif
