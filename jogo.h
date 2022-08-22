#ifndef JOGOS_H_INCLUDED
#define JOGOS_H_INCLUDED

#include "player.h"
#include "mapa.h"

typedef struct{
    int fase;
    bool telaInicial;
    Mapa mapa;
    Player mago;
}Jogo;


// Name: novoJogo
// Type: Function
// Inputs:
//      Jogo *jogo: a referencia para um objeto (assim dizer) jogo
// Output: Tem muitos.... atualizar isso!
// Return: Um booleano que informa se conseguimos criar um novo jogo ou nao.
// Description: Inicializar um novo jogo, carregando mapas, personagens, criaturas e monstros.
bool novoJogo(Jogo *jogo);

// Name:
// Type:
// Inputs:
//
// Output:
// Return:
// Description:
void passarFase();

void resetarMapa(Player *mago, Mapa *mapa);


#endif // JOGOSS_H_INCLUDED
