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
#define VIDAS 3
#define BOMBAS 3
#define TOTALFASES 3

void novoJogo(Jogo *jogo)
{
    int bomba;

    jogo->totalFases = TOTALFASES;
    jogo->fase = 1;
    jogo->gameOver = false;
    jogo->venceu = false;

    if(inicializarMapa(&jogo->mapa, jogo->fase))
    {
        jogo->mago.pontos = 0;
        jogo->mago.vidas = VIDAS;
        jogo->mago.color = PURPLE;
        jogo->mago.vivo = true;
        jogo->mago.quantidadeBombas = BOMBAS;
        for(bomba=0; bomba < BOMBAS; bomba++)
            jogo->mago.bombas[bomba].ativa = false;

        jogo->mago.x = jogo->mago.xInicial = jogo->mapa.posicaoXInicialJogador;
        jogo->mago.y = jogo->mago.yInicial = jogo->mapa.posicaoYInicialJogador;

    }
    else
    {
        printf("Voce venceu! \n");
        jogo->venceu = true;
    }

}

void passarFase(Jogo* jogo)
{
    if(jogo->fase > jogo->totalFases)
        jogo->venceu = true;
    else
    {
        if(inicializarMapa(&jogo->mapa, jogo->fase))
        {
            jogo->mago.x = jogo->mago.xInicial = jogo->mapa.posicaoXInicialJogador;
            jogo->mago.y = jogo->mago.yInicial = jogo->mapa.posicaoYInicialJogador;
        }
         else
            printf("Falha ao carregar novo mapa!");
    }
}

void resetarMapa(Player *mago, Mapa *mapa)
{
    int criatura, monstro, bomba;

    resetarPersonagem(mago);

    for(bomba = 0; bomba < mago->quantidadeBombas; bomba++)
    {
        if(mago->bombas[bomba].ativa)
        {
            mago->bombas[bomba].ativa = false;
            mapa->terreno[mago->bombas[bomba].y][mago->bombas[bomba].x] = ' ';
        }
    }

    for(criatura = 0; criatura < mapa->numeroCriaturas; criatura++)
        resetarCriatura(&mapa->criaturas[criatura]);

    for(monstro = 0; monstro < mapa->numeroMonstros; monstro++)
        resetarMonstro(&mapa->monstros[monstro]);
}

void gameOver(Jogo *jogo)
{
    jogo->gameOver = true;
}

bool salvarJogo(Jogo *jogo)
{
    FILE *salvar;
    char caminhoCompleto[] = "Saves/";
    char nome[50];

    printf("Digite o nome do Arquivo: ");
    scanf("%s", &nome);

    strcat(caminhoCompleto,nome);

    salvar = fopen(caminhoCompleto, "wb");

    if(!salvar)
    {
        fclose(salvar);
        return false;
    }
    if(fwrite(jogo, sizeof(Jogo), 1, salvar) != 1)
    {
        fclose(salvar);
        return false;
    }

    fclose(salvar);
    return true;
}

bool carregarJogo(Jogo *jogo)
{
    FILE *carregar;
    char caminhoCompleto[] = "Saves/";
    char nome[50];

    printf("Digite o nome do Arquivo: ");
    scanf("%s", &nome);

    strcat(caminhoCompleto,nome);

    carregar = fopen(caminhoCompleto, "rb");

    if(!carregar)
    {
        fclose(carregar);
        return false;
    }
    if(fread(jogo, sizeof(Jogo), 1, carregar) != 1)
    {
        fclose(carregar);
        return false;
    }

    fclose(carregar);
    return true;
}
