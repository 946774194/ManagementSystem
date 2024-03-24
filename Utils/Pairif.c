#include <stdlib.h>
#include "Pairif.h"

Pairif *newPairif(int i, float f){
    Pairif *pairif = (Pairif *)malloc(sizeof(Pairif));
    pairif->i = i;
    pairif->f = f;
    return pairif;
}

int getI(Pairif *pairif){
    return pairif->i;
}

float getF(Pairif *pairif){
    return pairif->f;
}