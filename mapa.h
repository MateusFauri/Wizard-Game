#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "criaturas.h"
#include "monstros.h"

#define COLUNAS 27
#define LINHAS 11
#define PATH 30
#define MONSTROS 50
#define CRIATURAS 50

typedef struct
{
    char terreno[LINHAS][COLUNAS];
    int numeroCriaturas;
    int numeroMonstros;
    Criatura criaturas[CRIATURAS];
    Monstro monstros[MONSTROS];
}Mapa;


// Name: LerMapa
// Type: Function
// Inputs:
//      Mapa *mapa: um mapa
// Output: terreno do mapa preenchido conforme o arquivo .txt daquele mapa
// Return: um booleano validando se o arquivo .txt conseguiu ser aberto ou não.
// Description: Le o arquivo de texto contendo o mapa e passa para a matriz terreno da struct MAPA.
bool lerMapa(Mapa *mapa);
bool movimentoPossivel(char terreno[][COLUNAS], int destino[]);
char movimentoAleatorio();

#endif // MAPA_H_INCLUDED
