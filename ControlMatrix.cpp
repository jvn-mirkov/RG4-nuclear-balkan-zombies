#include "ControlMatrix.h"


ControlMatrix::ControlMatrix() {
}


std::string ControlMatrix::checkField(float x, float y) {

    //TODO: cesta ponavljanja trunc nad koordinatama se mogu izdvojiti ovde u buducnosti

    return nullptr;
}

//prikaz trenutnog stanja matrice u konzoli, ispis mozda nije previse lep, sluzi samo za debagovanje
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

