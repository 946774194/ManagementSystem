#pragma once
// pair<int, float>
typedef struct Pairif{
    int i;
    float f;
} Pairif;

Pairif *newPairif(int i, float f);

int getI(Pairif *pairif);

float getF(Pairif *pairif);