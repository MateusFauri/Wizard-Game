#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "mapa.h"
#include "bomba.h"

#define MAPAX 27
#define BOMBAS 3

typedef struct{
    int pontos, vidas, quantidadeBombas;
    int x, y;
    int xInicial,yInicial;
    char direcaoAtual;
    bool vivo;
    Color color;
    Bomba bombas[BOMBAS];
}Player;

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void movimentoPersonagem(Player *mago, char terreno[][MAPAX]);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void movimentar(Player *mago, char terreno[][MAPAX], int destino[]);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void aumentarPontuacao(Player *mago, int ponto);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void resetarPersonagem(Player *mago);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void perderVida(Player *mago);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
bool verificarCriatura(Player mago, Criatura criatura);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
bool verificarMonstro(Player mago, Monstro monstro);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
bool verificarPocao(Player mago, char terreno[][MAPAX]);

// Name:
// Type: Function
// Inputs:
// Output:
// Return:
// Description:
void colocarBomba(Player *mago, Mapa *mapa);



#endif // PLAYER_H_INCLUDED
