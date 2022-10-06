#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"

#define PAREDE 'W'
#define PAREDEDESTRUTIVEL 'D'
#define POCAO 'P'
#define MAGO 'J'
#define MONSTRO 'M'
#define CRIATURA 'K'
#define BOMBA 'B'
#define POCAOCOLETADA 50
#define MONSTRODESTRUIDO 100
#define OBSTACULODESTRUIDO 10
#define PERDERVIDA -100
#define NOVAVIDA 1000
#define VIDAS 3
#define CRIATURACOLETADA 10
#define CIMA 'C'
#define BAIXO 'B'
#define ESQUERDA 'E'
#define DIREITA 'D'


void movimentoPersonagem(Player *mago, char terreno[][MAPAX])
{
    int destino[2];
    if (IsKeyPressed(KEY_RIGHT))
    {
        destino[0] = mago->x + 1;
        destino[1] = mago->y;
        mago->direcaoAtual = DIREITA;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        destino[0] = mago->x - 1;
        destino[1] = mago->y;
        mago->direcaoAtual = ESQUERDA;
    }
    if (IsKeyPressed(KEY_UP))
    {
        destino[0] = mago->x;
        destino[1] = mago->y - 1;
        mago->direcaoAtual = CIMA;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        destino[0] = mago->x;
        destino[1] = mago->y + 1;
        mago->direcaoAtual = BAIXO;
    }
    movimentar(mago, terreno, destino);
}


void movimentar(Player *mago, char terreno[][MAPAX], int destino[])
{
    if(movimentoPossivel(terreno ,destino))
    {
        mago->x = destino[0];
        mago->y = destino[1];
    }
}

void aumentarPontuacao(Player *mago, int ponto)
{
    mago->pontos += ponto;
}

void resetarPersonagem(Player *mago)
{
    mago->x = mago->xInicial;
    mago->y = mago->yInicial;
    mago->quantidadeBombas = BOMBAS;

    perderVida(mago);
}

void perderVida(Player *mago)
{
    if(mago->vidas > 1)
        mago->vidas -= 1;
    else
        mago->vivo = false;
}

bool verificarCriatura(Player mago, Criatura criatura)
{
    if(mago.x == criatura.x  && mago.y == criatura.y)
        return true;

    return false;
}


bool verificarMonstro(Player mago, Monstro monstro)
{
    if(mago.x == monstro.x  && mago.y == monstro.y)
        return true;

    return false;
}

bool verificarPocao(Player mago, char terreno[][MAPAX])
{
    if(terreno[mago.y][mago.x] == POCAO)
    {
        terreno[mago.y][mago.x] = ' ';
        return true;
    }

    return false;
}


bool colocarBomba(Player *mago, Mapa *mapa)
{
    int bomba, destino[2] = { 0 };

    switch(mago->direcaoAtual)
    {
    case CIMA:
        destino[0] = mago->x;
        destino[1] = mago->y - 1;
        break;
    case BAIXO:
        destino[0] = mago->x;
        destino[1] = mago->y + 1;
        break;
    case ESQUERDA:
        destino[0] = mago->x - 1;
        destino[1] = mago->y;
        break;
    case DIREITA:
        destino[0] = mago->x + 1;
        destino[1] = mago->y;
        break;
    }

    if(mago->quantidadeBombas > 0)
    {
        if(verificarPosicaoBomba(*mapa, destino))
        {
            bomba = BOMBAS - mago->quantidadeBombas;
            mago->quantidadeBombas -= 1;
            mago->bombas[bomba].x = destino[0];
            mago->bombas[bomba].y = destino[1];
            mago->bombas[bomba].ativa = true;
            mago->bombas[bomba].tempoAtivacao = GetTime();
            mapa->terreno[destino[1]][destino[0]] = BOMBA;
            return true;
        }
    }

    return false;
}



