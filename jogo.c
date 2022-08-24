#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogo.h"

#define COLUNAS 27
#define LINHAS 11
#define PASSO 40
#define NUMEROPECAS 50
#define LARGURA jogoX*PASSO
#define ALTURA jogoY*PASSO
#define PAREDE 'W'
#define PAREDEDESTRUTIVEL 'D'
#define POCAO 'P'
#define MAGO 'J'
#define MONSTRO 'M'
#define CRIATURA 'K'
#define CIMA 'C'
#define BAIXO 'B'
#define ESQUERDA 'E'
#define DIREITA 'D'
#define CONVERSORASCII 64
#define VIDAS 3
#define BOMBAS 3


void telaInicial()
{
    ShowCursor();

    ClearBackground(BLACK);
    DrawText(TextFormat("Nome do Jogo"), 300, 50, 80, RED);
    DrawText(TextFormat("Novo Jogo"), 140, 180, 40, RED);
    DrawText(TextFormat("Carregar Jogo"), 140, 220, 40, RED);
    DrawText(TextFormat("Salvar Jogo"), 140, 260, 40, RED);
    DrawText(TextFormat("Creditos"), 140, 300, 40, RED);
    DrawText(TextFormat("Exit"), 140, 380, 40, RED);
}

bool novoJogo(Jogo *jogo)
{
    int linha, coluna, criatura, monstro, bomba;
    char peca;

    criatura = monstro = 0;

    jogo->fase = 1;

    if(!lerMapa(&(jogo->mapa)))
        return false;

    for(linha = 0; linha < LINHAS; linha++)
    {
        for(coluna = 0; coluna < COLUNAS; coluna++)
        {
            peca = jogo->mapa.terreno[linha][coluna];

            switch(peca)
            {
            case MAGO:
                jogo->mago.xInicial = jogo->mago.x = coluna;
                jogo->mago.yInicial = jogo->mago.y = linha;
                jogo->mago.pontos = 0;
                jogo->mago.vidas = VIDAS;
                jogo->mago.color = PURPLE;
                jogo->mago.direcaoAtual = DIREITA;
                jogo->mago.quantidadeBombas = BOMBAS;
                for(bomba=0; bomba < BOMBAS; bomba++)
                    jogo->mago.bombas[bomba].ativa = false;
                break;
            case CRIATURA:
                jogo->mapa.criaturas[criatura].xInicial = jogo->mapa.criaturas[criatura].x = coluna;
                jogo->mapa.criaturas[criatura].yInicial = jogo->mapa.criaturas[criatura].y = linha;
                jogo->mapa.criaturas[criatura].pega = false;
                jogo->mapa.criaturas[criatura].passoDado = 0;
                jogo->mapa.criaturas[criatura].movimento = movimentoAleatorio();
                jogo->mapa.criaturas[criatura].color = GREEN;
                criatura += 1;
                break;
            case MONSTRO:
                jogo->mapa.monstros[monstro].xInicial = jogo->mapa.monstros[monstro].x = coluna;
                jogo->mapa.monstros[monstro].yInicial = jogo->mapa.monstros[monstro].y = linha;
                jogo->mapa.monstros[monstro].morto = false;
                jogo->mapa.monstros[monstro].passoDado = 0;
                jogo->mapa.monstros[monstro].movimento = movimentoAleatorio();
                jogo->mapa.monstros[monstro].color = RED;
                monstro += 1;
                break;
            }
        }
    }
    jogo->mapa.numeroCriaturas = criatura;
    jogo->mapa.numeroMonstros = monstro;

    return true;
}

void resetarMapa(Player *mago, Mapa *mapa)
{
    int criatura, monstro;

    resetarPersonagem(mago);

    for(criatura = 0; criatura < mapa->numeroCriaturas; criatura++)
        resetarCriatura(&mapa->criaturas[criatura]);

    for(monstro = 0; monstro < mapa->numeroMonstros; monstro++)
        resetarMonstro(&mapa->monstros[monstro]);
}

