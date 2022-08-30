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
#define P 80
#define TEMPOBOMBA 3
#define TELAINICIO 'I'
#define TELAJOGO 'J'
#define TELAPAUSE 'P'
#define TELASALVAR 'S'

static int framesCounter = 0;
static Jogo jogo;

static void desenhar(Jogo *jogo);
static void desenharInicio(Jogo *jogo);
static void desenharPause(Jogo *jogo);
static void atualizarJogo(Jogo *jogo);
static void desenharJogo(Jogo *jogo);


int main(void){
    jogo.tela = TELAINICIO;
    jogo.fecharJogo = false;

    InitWindow(LARGURA, ALTURA, "Jogo");
    SetTargetFPS(TEMPO);

    while(!jogo.fecharJogo)
        desenhar(&jogo);

    CloseWindow();
    return 0;
}

void desenhar(Jogo *jogo)
{
    char tela;

    tela = jogo->tela;

    switch(tela)
    {
    case TELAINICIO:
        desenharInicio(jogo);
        break;
    case TELAJOGO:
        atualizarJogo(jogo);
        break;
    case TELAPAUSE:
        desenharPause(jogo);
        break;
    case TELASALVAR:
        desenharSalvar(jogo);
        break;
    }
}

void desenharInicio(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posX = 20 ;
    const int posNomeJogoY = 20;
    const int posNovoJogoY = 150;
    const int posCarregarJogoY = 200;
    const int posSairY = 400;
    Vector2 posMouse;
    bool mouseEmNovoJogo, continuarRodando;

    ShowCursor();
    continuarRodando = jogo->tela == TELAINICIO && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();
        mouseEmNovoJogo = (posMouse.x > 20 && posMouse.x < 140) && (posMouse.y > 150 && posMouse.y < 165);

        if(IsMouseButtonPressed(botaoDireito) && mouseEmNovoJogo)
        {
            novoJogo(jogo);
            jogo->tela = TELAJOGO;
        }

        BeginDrawing();

            ClearBackground(BLACK);

            DrawText(TextFormat("NOME DO JOGO"), posX, posNomeJogoY, 40, LIGHTGRAY);
            DrawText(TextFormat("NOVO JOGO"), posX, posNovoJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("CARREGAR JOGO"), posX, posCarregarJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("SAIR"), posX, posSairY, 20, LIGHTGRAY);

        EndDrawing();

        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELAINICIO && !jogo->fecharJogo;

    }

}

void desenharPause(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posX = 20 ;
    const int posNovoJogoY = 150;
    const int posSalvarJogoY = 200;
    const int posSairY = 400;
    bool  mouseEmContinuarJogo, continuarRodando, mouseEmSalvar;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELAPAUSE && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmContinuarJogo = (posMouse.x > 20 && posMouse.x < 200) && (posMouse.y > 150 && posMouse.y < 165);
        mouseEmSalvar = (posMouse.x > 20 && posMouse.x < 160) && (posMouse.y > 200 && posMouse.y < 216);

        if(IsMouseButtonPressed(botaoDireito))
        {
            if(mouseEmContinuarJogo)
                jogo->tela = TELAJOGO;
            if(mouseEmSalvar)
            {
                jogo->tela = TELASALVAR;
                //mudar isso aqui em baixo para dentro da outra tela
                salvarJogo(jogo, sizeof(*jogo));
            }
        }


        BeginDrawing();

            ClearBackground(BLACK);

            DrawText(TextFormat("CONTINUAR JOGO"), posX, posNovoJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("SALVAR JOGO"), posX, posSalvarJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("SAIR"), posX, posSairY, 20, LIGHTGRAY);

        EndDrawing();

        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELAPAUSE && !jogo->fecharJogo;
    }

}

void desenharSalvar(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posX = 20 ;
    const int posNovoJogoY = 150;
    const int posSalvarJogoY = 200;
    const int posSairY = 400;
    bool  mouseEmConcluido, continuarRodando;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELASALVAR && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(TextFormat("NOME DO ARQUIVO:"), posX, posNovoJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("SALVAR"), posX, posSalvarJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("VOLTAR"), posX, posSairY, 20, LIGHTGRAY);

        EndDrawing();

        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELASALVAR && !jogo->fecharJogo;
    }

}

void atualizarJogo(Jogo *jogo)
{
    const int keyParada = P;
    int criatura, monstro, bomba;
    bool continuarRodando;
    char botaoPressionado;

    continuarRodando = jogo->tela == TELAJOGO && !WindowShouldClose();

    while(continuarRodando)
    {
        botaoPressionado = GetKeyPressed();

        if(verificarPocao(jogo->mago, jogo->mapa.terreno))
            aumentarPontuacao(&jogo->mago, POCAOCOLETADA);

        if(framesCounter % TEMPO == 0)
        {
            for(criatura = 0; criatura < jogo->mapa.numeroCriaturas; criatura++)
                movimentarCriatura( &jogo->mapa.criaturas[criatura], jogo->mapa.terreno);
            for(monstro = 0; monstro < jogo->mapa.numeroMonstros; monstro++)
                movimentarMonstro( &jogo->mapa.monstros[monstro], jogo->mapa.terreno);
        }

        for(criatura = 0; criatura < jogo->mapa.numeroCriaturas; criatura++)
            if(verificarCriatura(jogo->mago, jogo->mapa.criaturas[criatura]))
            {
                aumentarPontuacao(&jogo->mago, CRIATURACOLETADA);
                criaturaColetada(&jogo->mapa.criaturas[criatura]);
            }

        for(monstro = 0; monstro < jogo->mapa.numeroMonstros; monstro++)
            if(verificarMonstro(jogo->mago, jogo->mapa.monstros[monstro]))
            {
                if(jogo->mago.vidas > 1)
                {
                    resetarMapa(&jogo->mago, &jogo->mapa);
                    perderVida(&jogo->mago);
                }
                else
                    gameOver(jogo);
            }

        if(jogo->mago.quantidadeBombas < BOMBAS)
            for(bomba = 0; bomba < jogo->mago.quantidadeBombas; bomba++)
                if(jogo->mago.bombas[bomba].ativa)
                    if(verificarExplosao(jogo->mago.bombas[bomba], GetTime()))
                    {
                        explodir(&jogo->mago.bombas[bomba], &jogo->mapa);
                        jogo->mago.quantidadeBombas++;
                    }

        if(botaoPressionado == B)
        {
            colocarBomba(&jogo->mago, &jogo->mapa);
        }

        desenharJogo(jogo);
        movimentoPersonagem(&jogo->mago, jogo->mapa.terreno);

        if(botaoPressionado == keyParada) jogo->tela = TELAPAUSE ;
        if(jogo->gameOver) jogo->tela = TELAINICIO;

        framesCounter++;

        if(todasCriaturasColetadas(jogo->mapa.criaturas, jogo->mapa.numeroCriaturas))
        {
            jogo->fase += 1;
            printf("%d\n",jogo->fase);
            passarFase(jogo);
            desenharJogo(jogo);
        }

        if(WindowShouldClose())
            jogo->fecharJogo = true;

        continuarRodando = (jogo->tela == TELAJOGO && !jogo->fecharJogo) ;
    }


}

void desenharJogo(Jogo *jogo)
{
    int linha, coluna, posicaoX, posicaoY, criatura, monstro, bomba;
    char caracter;

    BeginDrawing();

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
                DrawRectangle(jogo->mago.bombas[bomba].x * PASSO, jogo->mago.bombas[bomba].y * PASSO, PASSO, PASSO, BLACK);
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


    EndDrawing();
}
