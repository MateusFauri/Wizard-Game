#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogo.h"

#define MAPAX 27
#define MAPAY 11
#define PASSO 40
#define NUMEROPECAS 50
#define LARGURA MAPAX*PASSO
#define ALTURA MAPAY*PASSO
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
#define POCAOCOLETADA 50
#define MONSTRODESTRUIDO 100
#define OBSTACULODESTRUIDO 10
#define CRIATURACOLETADA 10
#define PERDERVIDA -100
#define NOVAVIDA 1000
#define VIDAS 3
#define TEMPO 60
#define B 66
#define TAB 9
#define TEMPOBOMBA 3

static int framesCounter = 0;
static Jogo jogo;

void desenhar(Jogo *jogo);

int main(void){
    int  criatura, monstro;

    if(!novoJogo(&jogo))
        return 1;

    framesCounter = 0;

    InitWindow(LARGURA, ALTURA, "Jogo");
    SetTargetFPS(TEMPO);

    while(!WindowShouldClose())
    {
        if(verificarPocao(jogo.mago, jogo.mapa.terreno))
            aumentarPontuacao(&jogo.mago, POCAOCOLETADA);

        if(framesCounter % TEMPO == 0)
        {
            for(criatura = 0; criatura < jogo.mapa.numeroCriaturas; criatura++)
                movimentarCriatura( &jogo.mapa.criaturas[criatura], jogo.mapa.terreno);
            for(monstro = 0; monstro < jogo.mapa.numeroMonstros; monstro++)
                movimentarMonstro( &jogo.mapa.monstros[monstro], jogo.mapa.terreno);
            //if(framesCounter % (TEMPO * TEMPOBOMBA) == 0 )
            //      explodirBomba()
        }

        for(criatura = 0; criatura < jogo.mapa.numeroCriaturas; criatura++)
        {
            if(verificarCriatura(jogo.mago, jogo.mapa.criaturas[criatura]))
            {
                aumentarPontuacao(&jogo.mago, CRIATURACOLETADA);
                criaturaColetada(&jogo.mapa.criaturas[criatura]);
            }
        }

        for(monstro = 0; monstro < jogo.mapa.numeroMonstros; monstro++)
        {
            if(verificarMonstro(jogo.mago, jogo.mapa.monstros[monstro]))
            {
                resetarMapa(&jogo.mago, &jogo.mapa);
                perderVida(&jogo.mago);
            }
        }

        if(todasCriaturasColetadas(jogo.mapa.criaturas, jogo.mapa.numeroCriaturas))
        {
            jogo.fase+= 1;
            if(!novoJogo(&jogo))
            {
                printf("Nao deu certo\n");
                return 1;
            }
        }

        if(GetKeyPressed() == B)
            colocarBomba(&jogo.mago, jogo.mapa.terreno);

        desenhar(&jogo);
        movimentoPersonagem(&jogo.mago, jogo.mapa.terreno);

        framesCounter++;
    }

    CloseWindow();
    return 0;
}

void desenhar(Jogo *jogo)
{
    int linha, coluna, posicaoX, posicaoY, criatura, monstro, bomba;
    char caracter;

    BeginDrawing();

        if(jogo->telaInicial == true)
        {
            //telaInicial();
            printf("tela inicial\n");
        }
        else
        {
            HideCursor();
            ClearBackground(RAYWHITE);

            for(linha = 0; linha < MAPAY; linha++)
            {
                posicaoY = linha * PASSO;
                for(coluna = 0; coluna < MAPAX; coluna++)
                {
                    posicaoX = coluna * PASSO;
                    caracter = jogo->mapa.terreno[linha][coluna];

                    if (caracter == PAREDE)
                        DrawRectangle(posicaoX, posicaoY, PASSO, PASSO, BROWN);
                    if (caracter == PAREDEDESTRUTIVEL)
                        DrawRectangle(posicaoX, posicaoY, PASSO, PASSO, BROWN);
                    if (caracter == POCAO)
                        DrawRectangle(posicaoX, posicaoY, PASSO, PASSO, BLUE);
                }
            }

            DrawRectangle(jogo->mago.x * PASSO, jogo->mago.y * PASSO, PASSO, PASSO, jogo->mago.color);

            for(bomba = 0; bomba < BOMBAS; bomba++)
            {
                if(jogo->mago.bombas[bomba].ativa)
                {
                    DrawRectangle(jogo->mago.bombas[bomba].x * PASSO, jogo->mago.bombas[bomba].y * PASSO, PASSO, PASSO, YELLOW);
                }
            }


            for(criatura = 0; criatura < jogo->mapa.numeroCriaturas; criatura++)
            {
                if(!jogo->mapa.criaturas[criatura].pega)
                {
                    DrawRectangle(jogo->mapa.criaturas[criatura].x * PASSO, jogo->mapa.criaturas[criatura].y * PASSO, PASSO, PASSO, GREEN);
                }
            }

            for(monstro = 0; monstro < jogo->mapa.numeroMonstros; monstro++)
            {
                if(!jogo->mapa.monstros[monstro].morto)
                    DrawRectangle(jogo->mapa.monstros[monstro].x * PASSO, jogo->mapa.monstros[monstro].y * PASSO, PASSO, PASSO, RED);
            }


            DrawText(TextFormat("Vidas: %i", jogo->mago.vidas), 10, 0, 20, LIGHTGRAY);
            DrawText(TextFormat("Pontos: %i", jogo->mago.pontos), 140, 0, 20, LIGHTGRAY);
            DrawText(TextFormat("Bombas: %i", jogo->mago.quantidadeBombas), 300, 0, 20, LIGHTGRAY);
        }

    EndDrawing();
}
