#include "bomba.h"
#include <math.h>

#define TEMPOBOMBA 3


bool verificarExplosao(Bomba bomba, double tempo)
{
    if(tempo >= bomba.tempoAtivacao + TEMPOBOMBA)
        return true;
    return false;
}

/*
void explodir(Bomba *bomba, Mapa *mapa)
{
    int quadradosAtingidos;

    if(bomba.x >= RAIOBOMBA && bomba->x <= LINHAS - RAIOBOMBA)
        if(bomba.y >= RAIOBOMBA && bomba->y <= COLUNAS - RAIOBOMBA)
            quadradosAtingidos = ;
        else
            if(bomba.y == RAIOBOMBA - 1 || bomba.y == LINHAS - RAIOBOMBA + 1)
                quadradosAtingidos = ;
            else if(bomba.y == 0 || bomba.y == LINHAS)
                quadradosAtingidos =




}
*/
