#ifndef CRIATURAS_H_INCLUDED
#define CRIATURAS_H_INCLUDED

#include "raylib.h"

#define MAPAX 27

typedef struct{
    int xInicial, yInicial;
    int x,y, passoDado;
    bool pega;
    char movimento;
}Criatura;


// Name: criaturaColetada
// Type: Function
// Inputs:
//      Criatura *criatura
// Output: Modifica o estado da criatura
// Return: None.
// Description: Modificar o estado da criatura para pega.
void criaturaColetada(Criatura *criatura);

// Name: todasCriaturasColetadas
// Type: Function
// Inputs:
//      Criatura criatura[] : vetor de criaturas do mapa
//      int tamanho :  tamanho do vetor de criaturas
// Output: None.
// Return: Retorna um booleano se todas as criaturas foram coletadas ou nao
// Description: Percorre todas as criaturas, vendo todas tem o atributo pega como verdadeiro.
bool todasCriaturasColetadas(Criatura criatura[], int tamanho);

// Name: resetarCriatura
// Type: Function
// Inputs:
//      Criatura *criatura
// Output:  modifica o estado de todas as criaturas que tenham o atributo pega falso.
// Return:  None.
// Description: Volta todas as criaturas nao pegas para a posicao inicial.
void resetarCriatura(Criatura *criatura);

// Name: movimentarCriatura
// Type: Function
// Inputs:
//      Criatura *criatura
//      char terreno[][MAPAX]
// Output: modifica o estado das criaturas que tenham o atributo pega falso.
// Return:  None.
// Description: Movimenta todas as criaturas com movimentos aleatorios.
void movimentarCriatura(Criatura *criatura, char terreno[][MAPAX]);


#endif // CRIATURAS_H_INCLUDED
