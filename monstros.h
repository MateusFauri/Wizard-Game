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

// Name: monstroMorto
// Type: Function
// Inputs:
//      Monstro *monstro: vetor para uma struct monstro
// Output:
// Return: modifica o atributo do monstro morto para verdadeiro.
// Description: Modifica o atributo do monstro morto para verdadeiro, avisando que aquele monstro não esta mais naquela fase
void monstroMorto(Monstro *monstro);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void resetarMonstro(Monstro *monstro);

// Name: MovimentoAleatorio
// Type: Function
// Inputs:
// Output:
// Return: um caracter aleatorio dentro desta lista ['C','B','D','E']
// Description: Retorna uma direção aleatoria para o movimento dos personagens ou criaturas
void movimentarMonstro(Monstro *monstro, char terreno[][MAPAX]);

#endif // MONSTROS_H_INCLUDED
