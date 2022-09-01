#include "bomba.h"
#include <math.h>

#define TEMPOBOMBA 3
#define LADOS 4
#define PAREDE 'W'

bool verificarExplosao(Bomba bomba, double tempo)
{
    if(tempo >= bomba.tempoAtivacao + TEMPOBOMBA)
        return true;
    return false;
}

void verificarPerimetroExplosao(int posicaoBomba[], int perimetroExplosao[])
{
    int x, y, i;
    bool perimetroAmplo, perimetroReduzidoX, perimetroReduzidoY;

    x = posicaoBomba[0];
    y = posicaoBomba[1];

    perimetroAmplo = (x >= RAIOBOMBA && x <= MAPAX - RAIOBOMBA) && (y >= RAIOBOMBA && y <= MAPAY - RAIOBOMBA);
    perimetroReduzidoX = !(x >= RAIOBOMBA && x <= MAPAX - RAIOBOMBA);
    perimetroReduzidoY = !(y >= RAIOBOMBA && y <= MAPAY - RAIOBOMBA);

    if(perimetroAmplo)
    {
        for(i = 0; i < 4; i++)
            perimetroExplosao[i] = RAIOBOMBA;
    }
    else
    {
        if(perimetroReduzidoX)
        {
            if(perimetroReduzidoY)
            {
                switch(y)
                {
                case 1:
                    perimetroExplosao[0] = 1;
                    perimetroExplosao[1] = RAIOBOMBA;
                    break;
                case 2:
                    perimetroExplosao[0] = 2;
                    perimetroExplosao[1] = RAIOBOMBA;
                    break;
                case MAPAY - 1:
                    perimetroExplosao[0] = RAIOBOMBA;
                    perimetroExplosao[1] = 1;
                    break;
                case MAPAY - 2:
                    perimetroExplosao[0] = RAIOBOMBA;
                    perimetroExplosao[1] = 2;
                    break;
                }
                switch(x)
                {
                case 1:
                    perimetroExplosao[2] = RAIOBOMBA;
                    perimetroExplosao[3] = 1;
                    break;
                case 2:
                    perimetroExplosao[2] = RAIOBOMBA;
                    perimetroExplosao[3] = 2;
                    break;
                case MAPAX - 1:
                    perimetroExplosao[2] = 1;
                    perimetroExplosao[3] = RAIOBOMBA;
                    break;
                case MAPAX - 2:
                    perimetroExplosao[2] = 2;
                    perimetroExplosao[3] = RAIOBOMBA;
                    break;
                }
            }
            else
            {
                perimetroExplosao[0] = RAIOBOMBA;
                perimetroExplosao[1] = RAIOBOMBA;
                switch(x)
                {
                case 1:
                    perimetroExplosao[2] = RAIOBOMBA;
                    perimetroExplosao[3] = 1;
                    break;
                case 2:
                    perimetroExplosao[2] = RAIOBOMBA;
                    perimetroExplosao[3] = 2;
                    break;
                case MAPAX - 1:
                    perimetroExplosao[2] = 1;
                    perimetroExplosao[3] = RAIOBOMBA;
                    break;
                case MAPAX - 2:
                    perimetroExplosao[2] = 2;
                    perimetroExplosao[3] = RAIOBOMBA;
                    break;
                }
            }
        }
        else
        {
            perimetroExplosao[2] = RAIOBOMBA;
            perimetroExplosao[3] = RAIOBOMBA;
            switch(y)
            {
            case 0:
                perimetroExplosao[0] = 0;
                perimetroExplosao[1] = RAIOBOMBA;
                break;
            case 1:
                perimetroExplosao[0] = 1;
                perimetroExplosao[1] = RAIOBOMBA;
                break;
            case 2:
                perimetroExplosao[0] = 2;
                perimetroExplosao[1] = RAIOBOMBA;
                break;
            case MAPAY - 1:
                perimetroExplosao[0] = RAIOBOMBA;
                perimetroExplosao[1] = 1;
                break;
            case MAPAY - 2:
                perimetroExplosao[0] = RAIOBOMBA;
                perimetroExplosao[1] = 2;
                break;
            }
        }
    }

}

bool explodir(Bomba *bomba, Mapa *mapa, int posMago[])
{
    int perimetroExplosao[LADOS], posicaoBomba[2] = { bomba->x, bomba->y};
    int linha, coluna, monstro;
    bool magoExplodido = false;

    verificarPerimetroExplosao(posicaoBomba, perimetroExplosao);

    for(linha = bomba->y - perimetroExplosao[0]; linha <= bomba->y + perimetroExplosao[1]; linha++)
    {
        for(coluna = bomba->x - perimetroExplosao[3]; coluna <= bomba->x + perimetroExplosao[2]; coluna++)
        {
            if(mapa->terreno[linha][coluna] != PAREDE)
                mapa->terreno[linha][coluna] = ' ';

            if(posMago[0] == coluna && posMago[1] == linha)
                magoExplodido = true;

            for(monstro = 0; monstro < mapa->numeroMonstros; monstro++)
            {
                if(mapa->monstros[monstro].x == coluna && mapa->monstros[monstro].y == linha)
                    mapa->monstros[monstro].morto = true;
            }

        }
    }

    bomba->ativa = false;
    mapa->terreno[bomba->y][bomba->x] = ' ';

    if(magoExplodido)
        return true;
    else
        return false;

}
