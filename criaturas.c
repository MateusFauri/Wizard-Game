#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mapa.h"


#define MAPAX 27
#define CRIATURA 'K'
#define CIMA 'C'
#define BAIXO 'B'
#define ESQUERDA 'E'
#define DIREITA 'D'


void criaturaColetada(Criatura *criatura)
{
    criatura->pega = true;
    criatura->x = 0;
    criatura->y = 0;
}

bool todasCriaturasColetadas(Criatura criaturas[], int tamanho)
{
    int criatura;
    bool todasPegas = true;

    for(criatura = 0; criatura < tamanho; criatura++)
    {
        if(!criaturas[criatura].pega)
            todasPegas = false;
    }

    return todasPegas;
}

void resetarCriatura(Criatura *criatura)
{
    if(criatura->pega != true)
    {
        criatura->x = criatura->xInicial;
        criatura->y = criatura->yInicial;
    }
}

void movimentarCriatura(Criatura *criatura, char terreno[][MAPAX])
{
    int destino[2];

    if(criatura->pega == false)
    {
        if(criatura->passoDado > 4)
        {
            criatura->movimento =  movimentoAleatorio();
            criatura->passoDado = 0;
        }

        switch(criatura->movimento)
        {
        case CIMA:
            destino[0] = criatura->x;
            destino[1] = criatura->y - 1;
            break;

        case BAIXO:
            destino[0] = criatura->x;
            destino[1] = criatura->y + 1;
            break;

        case ESQUERDA:
            destino[0] = criatura->x - 1;
            destino[1] = criatura->y;
            break;

        case DIREITA:
            destino[0] = criatura->x + 1;
            destino[1] = criatura->y;
            break;
        }

        if(movimentoPossivel(terreno, destino))
        {
            criatura->x = destino[0];
            criatura->y = destino[1];
        }
        else
        {
            criatura->movimento =  movimentoAleatorio();
            criatura->passoDado = 0;
            movimentarCriatura(criatura, terreno);
        }
    }
}

