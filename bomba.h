#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include <stdbool.h>
#include "raylib.h"
#include "mapa.h"

#define MAPAX 27
#define MAPAY 10
#define RAIOBOMBA 3

typedef struct
{
    int x,y;
    bool ativa;
    double tempoAtivacao;
}Bomba;


bool verificarExplosao(Bomba bomba, double tempo);

void verificarPerimetroExplosao(int posicaoBomba[], int perimetroExplosao[]);

void explodir(Bomba *bomba, Mapa *mapa);

#endif // BOMBA_H_INCLUDED
