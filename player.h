#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "raylib.h"
#include "mapa.h"

#define MAPAX 27

typedef struct{
    int pontos;
    int vidas;
    int x;
    int y;
    int xInicial;
    int yInicial;
    Color color;
}Player;

void movimentoPersonagem(Player *mago, char terreno[][MAPAX]);
void movimentar(Player *mago, char terreno[][MAPAX], int destino[]);
void aumentarPontuacao(Player *mago, int ponto);
void resetarPersonagem(Player *mago);
void perderVida(Player *mago);
bool verificarCriatura(Player mago, Criatura criatura);
bool verificarMonstro(Player mago, Monstro monstro);
bool verificarPocao(Player mago, char terreno[][MAPAX]);

#endif // PLAYER_H_INCLUDED
