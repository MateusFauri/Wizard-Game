#ifndef MONSTROS_H_INCLUDED
#define MONSTROS_H_INCLUDED

#include "raylib.h"

#define MAPAX 27

typedef struct{
    int xInicial, yInicial;
    int x, y, passoDado;
    bool morto;
    char movimento;
}Monstro;

// Name: monstroMorto
// Type: Function
// Inputs:
//      Monstro *monstro: vetor para uma struct monstro
// Output: modifica o estado do monstro
// Return: None.
// Description: Modifica o atributo do monstro morto para verdadeiro
void monstroMorto(Monstro *monstro);

// Name: resetarMontro
// Type: Function
// Inputs:
//      Monstro *monstro
// Output:  modifica o estado do monstro
// Return: None.
// Description: Volta todos os monstros vivos para sua posicao inicial
void resetarMonstro(Monstro *monstro);

// Name: MovimentoAleatorio
// Type: Function
// Inputs:
//      Monstro *monstro
//      char terreno[][MAPAX]
// Output: modifica o estado do monstro
// Return: None.
// Description: Retorna uma direção aleatoria para o movimento dos personagens ou criaturas
void movimentarMonstro(Monstro *monstro, char terreno[][MAPAX]);

#endif // MONSTROS_H_INCLUDED
