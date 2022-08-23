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
//      Mapa *mapa: um ponteiro para uma struct Mapa
// Output: terreno do mapa preenchido conforme o arquivo .txt daquele mapa
// Return: um booleano validando se o arquivo .txt conseguiu ser aberto ou não.
// Description: Le o arquivo de texto contendo o mapa e passa para a matriz terreno da struct MAPA.
bool lerMapa(Mapa *mapa);

// Name: MovimentoPossivel
// Type: Function
// Inputs:
//      char terreno[][COLUNAS]: uma matriz de caracteres que repesenta o terreno (mapa) do jogo
//      int destino[]: um vetor de inteiros representando o passo na direcao x e y
// Output:
// Return: retorna um valor booleano caso o bloco do destino esta livre para poder andar
// Description: Esta função verifica se é possivel ou não dar um passo adiante no terreno
bool movimentoPossivel(char terreno[][COLUNAS], int destino[]);

// Name: MovimentoAleatorio
// Type: Function
// Inputs:
// Output:
// Return: um caracter aleatorio dentro desta lista ['C','B','D','E']
// Description: Retorna uma direção aleatoria para o movimento dos personagens ou criaturas
char movimentoAleatorio();

#endif // MAPA_H_INCLUDED
