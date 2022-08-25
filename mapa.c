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
#define ASCII 64


bool inicializarMapa(Mapa *mapa, int fase)
{
    int linha, coluna, criatura, monstro;
    char peca;

    mudarPath(mapa, fase);

    if(!lerMapa(mapa))
        return false;
    printf("%s\n",mapa->path);

    criatura = monstro = 0;

    for(linha = 0; linha < LINHAS; linha++)
    {
        for(coluna = 0; coluna < COLUNAS; coluna++)
        {
            peca = mapa->terreno[linha][coluna];

            switch(peca)
            {
            case MAGO:
                mapa->posicaoXInicialJogador = coluna;
                mapa->posicaoYInicialJogador = linha;
                break;
            case CRIATURA:
                mapa->criaturas[criatura].xInicial = mapa->criaturas[criatura].x = coluna;
                mapa->criaturas[criatura].yInicial = mapa->criaturas[criatura].y = linha;
                mapa->criaturas[criatura].pega = false;
                mapa->criaturas[criatura].passoDado = 0;
                mapa->criaturas[criatura].movimento = movimentoAleatorio();
                criatura += 1;
                break;
            case MONSTRO:
                mapa->monstros[monstro].xInicial = mapa->monstros[monstro].x = coluna;
                mapa->monstros[monstro].yInicial = mapa->monstros[monstro].y = linha;
                mapa->monstros[monstro].morto = false;
                mapa->monstros[monstro].passoDado = 0;
                mapa->monstros[monstro].movimento = movimentoAleatorio();
                monstro += 1;
                break;
            }
        }
    }
    mapa->numeroCriaturas = criatura;
    mapa->numeroMonstros = monstro;

    return true;
}

void mudarPath(Mapa *mapa, int fase)
{
    char path[] = "Mapas/mapa_.txt";

    path[10] = (char) (ASCII + fase);

    strcpy(mapa->path, path);
}

bool lerMapa(Mapa *mapa)
{
    FILE *file;
    int coluna, linha;
    char caracter;

    linha = coluna = 0;

    file = fopen(mapa->path,"r");

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


bool verificarPosicaoBomba(Mapa mapa, int destino[])
{
    int criatura, monstro;

    for(criatura = 0; criatura < mapa.numeroCriaturas; criatura++)
        if(mapa.criaturas[criatura].x == destino[0] && mapa.criaturas[criatura].y == destino[1])
            return false;

    for(monstro = 0; monstro < mapa.numeroMonstros; monstro++)
        if(mapa.monstros[monstro].x == destino[0] && mapa.monstros[monstro].y == destino[1])
            return false;

    if(!movimentoPossivel(mapa.terreno,destino))
        return false;

    return true;
}

