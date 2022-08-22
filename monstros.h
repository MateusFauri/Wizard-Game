#ifndef MONSTROS_H_INCLUDED
#define MONSTROS_H_INCLUDED

#include "raylib.h"

#define MAPAX 27

typedef struct{
    int xInicial, yInicial;
    int x, y, passoDado;
    bool morto;
    char movimento;
    Color color;
}Monstro;

void monstroMorto(Monstro *monstro);
void resetarMonstro(Monstro *monstro);
void movimentarMonstro(Monstro *monstro, char terreno[][MAPAX]);

#endif // MONSTROS_H_INCLUDED
