#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "monstros.h"

#define MAPAX 27
#define CRIATURA 'K'
#define CIMA 'C'
#define BAIXO 'B'
#define ESQUERDA 'E'
#define DIREITA 'D'


void monstroMorto(Monstro *monstro)
{
    monstro->morto = true;
    monstro->x = 0;
    monstro->y = 0;
}


void movimentarMonstro(Monstro *monstro, char terreno[][MAPAX])
{
    int destino[2], teste;

    if(monstro->morto == false)
    {
        if(monstro->passoDado > 4)
        {
            monstro->movimento =  movimentoAleatorio();
            monstro->passoDado = 0;
        }

        switch(monstro->movimento)
        {
        case CIMA:
            destino[0] = monstro->x;
            destino[1] = monstro->y - 1;
            break;

        case BAIXO:
            destino[0] = monstro->x;
            destino[1] = monstro->y + 1;
            break;

        case ESQUERDA:
            destino[0] = monstro->x - 1;
            destino[1] = monstro->y;
            break;

        case DIREITA:
            destino[0] = monstro->x + 1;
            destino[1] = monstro->y;
            break;
        }

        if(movimentoPossivel(terreno, destino))
        {
            monstro->x = destino[0];
            monstro->y = destino[1];
        }
        else
        {
            monstro->movimento =  movimentoAleatorio();
            monstro->passoDado = 0;
            movimentarMonstro(monstro,terreno);
        }
    }
}


void resetarMonstro(Monstro *monstro)
{
    if(monstro->morto != true)
    {
        monstro->x = monstro->xInicial;
        monstro->y = monstro->yInicial;
    }
}
