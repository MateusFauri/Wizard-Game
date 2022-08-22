#ifndef CRIATURAS_H_INCLUDED
#define CRIATURAS_H_INCLUDED

#include "raylib.h"

#define MAPAX 27

typedef struct{
    int xInicial, yInicial;
    int x,y, passoDado;
    bool pega;
    char movimento;
    Color color;
}Criatura;


// Name: criaturaColetada
// Type: Function
// Inputs:
//      Criatura *criatura
// "Invariant": Modifica estado de criaturas.
// Output: None.
// Return: None.
// Description: Modificar o estado da criatura para pega.
void criaturaColetada(Criatura *criatura);

bool todasCriaturasColetadas(Criatura criatura[], int tamanho);

void resetarCriatura(Criatura *criatura);

void movimentarCriatura(Criatura *criatura, char terreno[][MAPAX]);


#endif // CRIATURAS_H_INCLUDED
