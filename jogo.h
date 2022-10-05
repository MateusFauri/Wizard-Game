#ifndef JOGOS_H_INCLUDED
#define JOGOS_H_INCLUDED

#include "player.h"
#include "mapa.h"

typedef struct{
    int fase, totalFases;
    char tela;
    bool fecharJogo;
    bool gameOver, venceu;
    Mapa mapa;
    Player mago;
}Jogo;


// Name: novoJogo
// Type: Function
// Inputs:
//      Jogo *jogo
// Output: Modofica todas as structs para "inicial"
// Return: None.
// Description: Inicializar um novo jogo, carregando mapas, personagens, criaturas e monstros.
void novoJogo(Jogo *jogo);

// Name: passarFase
// Type: Function
// Inputs:
//       Jogo *jogo
// Output:  Modifica o jogo e o mapa
// Return:  None.
// Description: Passa de fase caso houver uma nova, se não modifica o jogo para venceu.
void passarFase(Jogo* jogo);

// Name: resetarMapa
// Type: Function
// Inputs:
//      Player *mago
//      Mapa *mapa
// Output:  Modifica a posicão dos objetos dinamicos do mapa e do jogador.
// Return:  None.
// Description: volta a posicão inicial de todas as structs do mapa (objetos dinamicos do mapa) e o a posição inicial do mago também.
void resetarMapa(Player *mago, Mapa *mapa);

// Name: gameOver
// Type: Function
// Inputs:
//      Jogo *jogo
// Output: modifica o estado do jogo
// Return: None.
// Description: modifica o atributo gameOver do jogo
void gameOver(Jogo *jogo);

// Name: salvarJogo
// Type: Function
// Inputs:
//      Jogo *jogo
//      char path[]  Caminho para salvar o arquivo
// Output: um arquivo com todas as informações do jogo salvas.
// Return: Retornar um booleno caso sucesso da função
// Description: salva o estado do jogo atual
bool salvarJogo(Jogo *jogo, char path[]);

// Name: carregarJogo
// Type: Function
// Inputs:
//      Jogo *jogo
// Output: muda todos os atributos do jogo e suas structs encadeadas
// Return: Retornar um booleno caso sucesso da função
// Description: Le um arquivo salvo para carregar o jogo de onde parou.
bool carregarJogo(Jogo *jogo);

#endif // JOGOSS_H_INCLUDED
