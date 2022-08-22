#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"

#define MAPAX 27
#define PAREDE 'W'
#define PAREDEDESTRUTIVEL 'D'
#define POCAO 'P'
#define MAGO 'J'
#define MONSTRO 'M'
#define CRIATURA 'K'
#define POCAOCOLETADA 50
#define MONSTRODESTRUIDO 100
#define OBSTACULODESTRUIDO 10
#define PERDERVIDA -100
#define NOVAVIDA 1000
#define VIDAS 3
#define CRIATURACOLETADA 10


void movimentoPersonagem(Player *mago, char terreno[][MAPAX])
{
    int destino[2];
    if (IsKeyPressed(KEY_RIGHT))
    {
        destino[0] = mago->x + 1;
        destino[1] = mago->y;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        destino[0] = mago->x - 1;
        destino[1] = mago->y;
    }
    if (IsKeyPressed(KEY_UP))
    {
        destino[0] = mago->x;
        destino[1] = mago->y - 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        destino[0] = mago->x;
        destino[1] = mago->y + 1;
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

    if(mago->pontos >= NOVAVIDA)
    {
        mago->vidas += 1;
        mago->pontos = 0;
    }
}

void resetarPersonagem(Player *mago)
{
    mago->x = mago->xInicial;
    mago->y = mago->yInicial;
}

void perderVida(Player *mago)
{
    mago->vidas -= 1;
    if(mago->vidas == 0)
    {
        printf("Game Over\n");
        //gamerOver();
    }

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
