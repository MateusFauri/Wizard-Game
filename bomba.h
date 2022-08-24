#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include <stdbool.h>
#include "raylib.h"
#include "mapa.h"

#define MAPAX 27
#define RAIOBOMBA 2

typedef struct
{
    int x,y;
    bool ativa;
    double tempoAtivacao;
}Bomba;


bool verificarExplosao(Bomba bomba, double tempo);


#endif // BOMBA_H_INCLUDED