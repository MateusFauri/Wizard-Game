#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "desenho.h"

#define NUMEROPECAS 50
#define PATHSAVE 100
#define BACKSPACE 3
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
    case TELACARREGAR:
        desenharCarregar(jogo);
        break;
    case TELADERROTA:
        desenharDerrota(jogo);
        break;
    case TELAVITORIA:
        desenharVitoria(jogo);
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
    bool mouseEmNovoJogo,mouseEmCarregar, mouseEmSair ,continuarRodando;

    ShowCursor();
    continuarRodando = jogo->tela == TELAINICIO && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmSair = (posMouse.x > 20 && posMouse.x < 66) && (posMouse.y > 400 && posMouse.y < 417);
        mouseEmNovoJogo = (posMouse.x > 20 && posMouse.x < 140) && (posMouse.y > 150 && posMouse.y < 165);
        mouseEmCarregar = (posMouse.x > 20 && posMouse.x < 192) && (posMouse.y > 200 && posMouse.y < 215);

        if(IsMouseButtonPressed(botaoDireito))
        {
            if(mouseEmNovoJogo)
            {
                novoJogo(jogo);
                jogo->tela = TELAJOGO;
            }

            if(mouseEmCarregar)
                jogo->tela = TELACARREGAR;

            if(mouseEmSair)
                jogo->fecharJogo = true;

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
    bool  mouseEmContinuarJogo, mouseEmSair, continuarRodando, mouseEmSalvar;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELAPAUSE && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmContinuarJogo = (posMouse.x > 20 && posMouse.x < 200) && (posMouse.y > 150 && posMouse.y < 165);
        mouseEmSalvar = (posMouse.x > 20 && posMouse.x < 160) && (posMouse.y > 200 && posMouse.y < 216);
        mouseEmSair = (posMouse.x > 20 && posMouse.x < 66) && (posMouse.y > 400 && posMouse.y < 417);

        if(IsMouseButtonPressed(botaoDireito))
        {
            if(mouseEmContinuarJogo)
                jogo->tela = TELAJOGO;

            if(mouseEmSalvar)
                jogo->tela = TELASALVAR;

            if(mouseEmSair)
                jogo->fecharJogo = true;

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

void desenharDerrota(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posSairY = 400;
    bool  mouseEmSair, continuarRodando;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELADERROTA && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmSair = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 402 && posMouse.y < 415);

        if(IsMouseButtonPressed(botaoDireito) && mouseEmSair)
            jogo->tela = TELAINICIO;

        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(TextFormat("VOCE PERDEU!"), 330 , 200, 50, LIGHTGRAY);
            DrawText(TextFormat("SAIR"), LARGURA / 2, posSairY, 20, LIGHTGRAY);

        EndDrawing();

        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELADERROTA && !jogo->fecharJogo;
    }

}

void desenharVitoria(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posSairY = 400;
    bool  mouseEmSair, continuarRodando;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELAVITORIA && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmSair = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 402 && posMouse.y < 415);

        if(IsMouseButtonPressed(botaoDireito) && mouseEmSair)
            jogo->tela = TELAINICIO;

        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(TextFormat("VOCE GANHOU!"), 330 , 200, 50, LIGHTGRAY);
            DrawText(TextFormat("SAIR"), LARGURA / 2, posSairY, 20, LIGHTGRAY);

        EndDrawing();

        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELAVITORIA && !jogo->fecharJogo;
    }

}

void desenharCarregar(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posX = 20 ;
    const int posNomeArquivoY = 150;
    const int posCarregarJogoY = 350;
    const int posSairY = 400;
    bool  mouseEmCarregar, mouseEmVoltar, continuarRodando;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELACARREGAR && !WindowShouldClose();

    while(continuarRodando)
    {
        posMouse = GetMousePosition();

        mouseEmCarregar = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 348 && posMouse.y < 366);
        mouseEmVoltar = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 402 && posMouse.y < 415);

        if(IsMouseButtonPressed(botaoDireito))
        {
            if(mouseEmCarregar)
            {
                carregarJogo(jogo);
                jogo->tela = TELAJOGO;
            }

            if(mouseEmVoltar)
                jogo->tela = TELAINICIO;
        }

        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(TextFormat("NOME DO ARQUIVO:"), posX, posNomeArquivoY, 20, LIGHTGRAY);
            DrawText(TextFormat("Carregar"), LARGURA / 2, posCarregarJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("VOLTAR"), LARGURA / 2, posSairY, 20, LIGHTGRAY);

        EndDrawing();


        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELACARREGAR && !jogo->fecharJogo;
    }

}

void desenharSalvar(Jogo *jogo)
{
    const int botaoDireito = 0 ;
    const int posX = 20 ;
    const int posNomeArquivoY = 150;
    const int posSalvarJogoY = 350;
    const int posSairY = 400;
    bool  mouseEmSalvar,mouseEmVoltar, continuarRodando;
    char key;
    char path[PATHSAVE] = "Saves/";
    int tamanhoPath;
    Vector2 posMouse;

    ShowCursor();
    continuarRodando = jogo->tela == TELASALVAR && !WindowShouldClose();
    key = 0;

    while(continuarRodando)
    {
        posMouse = GetMousePosition();
        key = GetKeyPressed();
        tamanhoPath = strlen(path);

        mouseEmSalvar = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 348 && posMouse.y < 366);
        mouseEmVoltar = (posMouse.x > 540 && posMouse.x < 622) && (posMouse.y > 402 && posMouse.y < 415);

        if(IsMouseButtonPressed(botaoDireito))
        {
            if(mouseEmSalvar)
            {
                salvarJogo(jogo, path);
                jogo->tela = TELAPAUSE;
            }

            if(mouseEmVoltar)
                jogo->tela = TELAPAUSE;
        }

        BeginDrawing();

            ClearBackground(BLACK);
            DrawText(TextFormat("NOME DO ARQUIVO:"), posX, posNomeArquivoY, 20, LIGHTGRAY);

            if(key != 0)
            {
                if(key == BACKSPACE)
                    path[tamanhoPath - 1] = '\0';
                else
                    strcat(path, &key);
            }

            DrawText(TextFormat("%s", &path[6]), posX + 250, posNomeArquivoY, 20, LIGHTGRAY);
            DrawText(TextFormat("SALVAR"), LARGURA / 2, posSalvarJogoY, 20, LIGHTGRAY);
            DrawText(TextFormat("VOLTAR"), LARGURA / 2, posSairY, 20, LIGHTGRAY);

        EndDrawing();


        if(WindowShouldClose())
            jogo->fecharJogo = true;
        continuarRodando = jogo->tela == TELASALVAR && !jogo->fecharJogo;
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
        DrawText(TextFormat("Fase: %i", jogo->fase), 450, 0, 20, LIGHTGRAY);

    EndDrawing();
}
