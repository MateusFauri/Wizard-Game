#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mapa.h"

#define PAREDE 'W'
#define PAREDEDESTRUTIVEL 'D'
#define POCAO 'P'
#define MAGO 'J'
#define MONSTRO 'M'
#define CRIATURA 'K'
#define BOMBA 'B'
#define CIMA 'C'
#define BAIXO 'B'
#define ESQUERDA 'E'
#define DIREITA 'D'


bool lerMapa(Mapa *mapa)
{
    FILE *file;
    int coluna, linha;
    char caracter;
    char path[] = "Mapas/mapaA.txt";

    linha = coluna = 0;

    file = fopen(path,"r");

    if(file == NULL)
        return false;
    do
    {
        caracter = fgetc(file);
        if(caracter != '\n')
        {
            mapa->terreno[linha][coluna] = caracter;

            coluna +=  1;
            if(coluna == COLUNAS)
            {
                linha += 1;
                coluna = 0;
            }
        }
    }while(caracter != EOF);
    fclose(file);
    return true;
}

bool movimentoPossivel(char terreno[][COLUNAS], int destino[])
{
    int x,y;
    bool limitesX, limitesY, parede, bomba;

    x = destino[0];
    y = destino[1];

    limitesX = x >= 0 && x < COLUNAS;
    limitesY = y >= 0 && y < LINHAS;
    parede = terreno[y][x] == PAREDE || terreno[y][x] == PAREDEDESTRUTIVEL;
    bomba = terreno[y][x] == BOMBA;

    if(!limitesX || !limitesY || parede || bomba)
        return false;

    return true;
}


char movimentoAleatorio()
{
    char movimento[] = { CIMA, BAIXO, ESQUERDA, DIREITA};
    int posicaoAleatoria ;

    posicaoAleatoria = GetRandomValue(0,3);

    return movimento[posicaoAleatoria];
}


