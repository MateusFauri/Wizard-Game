#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include <stdbool.h>
#include "raylib.h"

#define MAPAX 27

typedef struct
{
    int x,y;
    bool ativa;
    Color color;
}Bomba;



#endif // BOMBA_H_INCLUDED
