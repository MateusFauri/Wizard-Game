#ifndef DESENHO_H_INCLUDED
#define DESENHO_H_INCLUDED

#include "raylib.h"
#include "jogo.h"

#define TELAINICIO 'I'
#define TELAJOGO 'J'
#define TELAPAUSE 'P'
#define TELASALVAR 'S'
#define TELACARREGAR 'C'
#define TELADERROTA 'D'
#define TELAVITORIA 'V'
#define MAPAX 27
#define MAPAY 11
#define PASSO 40
#define LARGURA MAPAX*PASSO
#define ALTURA MAPAY*PASSO
#define TEMPO 60

// Name: desenhar
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Envia a struct jogo para uma das funções abaixo.
// Return:  None.
// Description: Ve qual é a tela atual do jogo e o manda para a uma das funções desenhar adequada.
void desenhar(Jogo *jogo);

// Name: desenharInicio
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Muda a tela do jogo caso o usuario clicar em um dos texto da tela
// Return:  None.
// Description: Exibe a tela inicial do jogo e fica nela ate que o usuario decida qual opção ira usar, mudando o estado da tela do jogo.
void desenharInicio(Jogo *jogo);

// Name: desenharPause
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Muda a tela do jogo caso o usuario clicar em um dos texto da tela
// Return:  None.
// Description: Pausa o jogo e muda para a tela de pause, ate que o usuario decida continuar, salvar ou sair do jogo.
void desenharPause(Jogo *jogo);

// Name: desenharCarregar
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Vai para a tela de carregamento, mudando o estado da tela do jogo
// Return:  None.
// Description: chama a função carregar do jogo.
void desenharCarregar(Jogo *jogo);

// Name: desenharSalvar
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Vai para a tela de salvamento, mudando o estado da tela do jogo
// Return:  None.
// Description: chama a função salvar do jogo.
void desenharSalvar(Jogo *jogo);

// Name: desenharJogo
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Atualiza a tela do jogo.
// Return:  None.
// Description: atualiza a tela do jogo com os novos outputs gerados (geralmente) pela função  atualizarJogo.
void desenharJogo(Jogo *jogo);

// Name: desenharDerrota
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Modifica a tela do jogo
// Return:  None.
// Description: Desenha a tela de derrota
void desenharDerrota(Jogo *jogo);

// Name: desenharVitoria
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  Modifica a tela do jogo
// Return:  None.
// Description: Desenha a tela de vitoria.
void desenharVitoria(Jogo *jogo);


#endif // DESENHO_H_INCLUDED
