#include "ControlMatrix.h"


ControlMatrix::ControlMatrix() {


}

std::string ControlMatrix::checkField(float x, float y) {

    //TEST:?????????????????




    int a = static_cast<int>(floor(x));
    int b = static_cast<int>(floor(y));

    std::string s;
    s += std::to_string(a);
    s += std::to_string(b);

    return s;
}


void ControlMatrix::showMatrix() {

    std::cout << "--------Control-Matrix--------" << std::endl << std::endl;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 13; j++) {
            std::cout << mx[j][i];
        }
        std::cout << std::endl;
    }

    std::cout << "------------------------------" << std::endl << std::endl << std::endl;
}

