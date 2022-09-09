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

// Name: movimentoPersonagem
// Type: Function
// Inputs:
//      Player *mago
//      char terreno[][MAPAX]
// Output: None.
// Return: None.
// Description: Verifica se alguma tecla foi clicada para que o personagem se movimentasse.
//      Usa a funcao movimentar caso alguma tecla foi chamada.
void movimentoPersonagem(Player *mago, char terreno[][MAPAX]);

// Name: movimentar
// Type: Function
// Inputs:
//      Player *mago
//      char terreno[][MAPAX]
//      int destino[] : posicao de destino do mago
// Output:  Modifica o estado do personagem
// Return: None.
// Description: Modifica a posicao do mago conforme possivel no terreno.
//          Usa a funcao movimentoPossivel (do mapa) para verificar se o mago pode fazer o movimento requerido
void movimentar(Player *mago, char terreno[][MAPAX], int destino[]);

// Name: aumentarPontuacao
// Type: Function
// Inputs:
//      Player *mago
//      int ponto : quantidade de pontos para aumentar no mago
// Output: modifica o estado do mago
// Return: None.
// Description: modifica a pontuacao do mago
void aumentarPontuacao(Player *mago, int ponto);

// Name: resetarPersonagem
// Type: Function
// Inputs:
//      Player *mago
// Output: Modifica o estado do mago
// Return: None.
// Description: Volta o mago para sua posicao inicial do mapa
void resetarPersonagem(Player *mago);

// Name: perderVida
// Type: Function
// Inputs:
//      Player *mago
// Output: Modifica o estado do mago
// Return:  None.
// Description: Tira uma vida do mago caso possa, se nao modifica o atributo vivo do mago para falso
void perderVida(Player *mago);

// Name: verificarCriatura
// Type: Function
// Inputs:
//      Player mago
//      Criatura criatura
// Output: None.
// Return: Retorna um booleano caso o mago estiver na mesma posicao que uma criatura
// Description: Verifica se o mago esta na mesma posicao do terreno que uma criatura
bool verificarCriatura(Player mago, Criatura criatura);


// Name: verificarMonstro
// Type: Function
// Inputs:
//      Player mago
//      Monstro monstro
// Output: None.
// Return: Retorna um booleano caso o mago estiver na mesma posicao que um monstro
// Description: Verifica se o mago esta na mesma posicao do terreno que um monstro
bool verificarMonstro(Player mago, Monstro monstro);

// Name: verificarPocao
// Type: Function
// Inputs:
//      Player mago
//      char terreno[][MAPAX]
// Output: None.
// Return: Retorna um booleano caso o mago estiver na mesma posicao que uma poção
// Description: Verifica se o mago esta na mesma posicao do terreno que uma poção
bool verificarPocao(Player mago, char terreno[][MAPAX]);

// Name: colocarBomba
// Type: Function
// Inputs:
//      Player *mago
//      Mapa *mapa
// Output:  Modifica o estado do mago, das bomba e do mapa.
// Return: None.
// Description: Coloca uma bomba no mapa se for possivel (nao estiver em cima de alguma criatura/monstro, ou em na parade)
void colocarBomba(Player *mago, Mapa *mapa);



#endif // PLAYER_H_INCLUDED
