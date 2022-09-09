#include "raylib.h"
#include "jogo.h"
#include "desenho.h"
#include <stdio.h>
#include <stdlib.h>

#define P 80
#define B 66
#define TEMPOBOMBA 3
#define POCAOCOLETADA 50
#define MONSTRODESTRUIDO 100
#define OBSTACULODESTRUIDO 10
#define CRIATURACOLETADA 10
#define PERDERVIDA -100
#define NOVAVIDA 1000
#define VIDAS 3

// Name: atualizarJogo
// Type: Function
// Inputs:
//      Jogo *jogo
// Output:  modifica todas as structs.
// Return:  None.
// Description: A função que traz toda a logica do jogo, vendo a cada frame se o mago esta vivo, se passou de fase, se morreu e etc.
void atualizarJogo(Jogo *jogo);

static Jogo jogo;
static int framesCounter = 0;

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

void atualizarJogo(Jogo *jogo)
{
    const int keyParada = P;
    int criatura, monstro, bomba, posMago[2], bufferPontos;
    bool continuarRodando;
    char botaoPressionado;

    bufferPontos = 0;

    continuarRodando = jogo->tela == TELAJOGO && !WindowShouldClose();

    while(continuarRodando)
    {
        botaoPressionado = GetKeyPressed();

        if(verificarPocao(jogo->mago, jogo->mapa.terreno))
        {
            aumentarPontuacao(&jogo->mago, POCAOCOLETADA);
            bufferPontos += POCAOCOLETADA;
        }

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
                bufferPontos += CRIATURACOLETADA;
                criaturaColetada(&jogo->mapa.criaturas[criatura]);
            }

        for(monstro = 0; monstro < jogo->mapa.numeroMonstros; monstro++)
            if(!jogo->mapa.monstros[monstro].morto)
                if(verificarMonstro(jogo->mago, jogo->mapa.monstros[monstro]))
                {
                    aumentarPontuacao(&jogo->mago, PERDERVIDA);
                    bufferPontos += PERDERVIDA;
                    resetarMapa(&jogo->mago, &jogo->mapa);
                }

        if(jogo->mago.quantidadeBombas < BOMBAS)
            for(bomba = 0; bomba < jogo->mago.quantidadeBombas; bomba++)
                if(jogo->mago.bombas[bomba].ativa)
                    if(verificarExplosao(jogo->mago.bombas[bomba], GetTime()))
                    {
                        if(explodir(&jogo->mago.bombas[bomba], &jogo->mapa, posMago))
                        {
                            aumentarPontuacao(&jogo->mago, PERDERVIDA);
                            bufferPontos += PERDERVIDA;
                            resetarMapa(&jogo->mago, &jogo->mapa);
                        }
                        else
                        {
                            if(jogo->mapa.paredesDestruidas != 0)
                            {
                                aumentarPontuacao(&jogo->mago, OBSTACULODESTRUIDO);
                                bufferPontos += OBSTACULODESTRUIDO;
                                jogo->mapa.paredesDestruidas = 0;
                            }
                            if(jogo->mapa.monstrosDestruidos != 0)
                            {
                                aumentarPontuacao(&jogo->mago, MONSTRODESTRUIDO);
                                bufferPontos += MONSTRODESTRUIDO;
                                jogo->mapa.monstrosDestruidos = 0;
                            }
                            jogo->mago.quantidadeBombas += 1;
                        }
                    }

        if(botaoPressionado == B)
            colocarBomba(&jogo->mago, &jogo->mapa);

        if(bufferPontos >= NOVAVIDA)
        {
            jogo->mago.vidas += 1;
            bufferPontos = 0;
        }

        desenharJogo(jogo);

        if(jogo->mago.vivo)
        {
            movimentoPersonagem(&jogo->mago, jogo->mapa.terreno);

            posMago[0] = jogo->mago.x;
            posMago[1] = jogo->mago.y;

            if(botaoPressionado == keyParada) jogo->tela = TELAPAUSE;
            if(jogo->gameOver) jogo->tela = TELAINICIO;

            framesCounter++;

            if(todasCriaturasColetadas(jogo->mapa.criaturas, jogo->mapa.numeroCriaturas))
            {
                jogo->fase += 1;
                passarFase(jogo);
                if(!jogo->venceu)
                    desenharJogo(jogo);
                else
                    jogo->tela = TELAVITORIA;
            }
        }
        else
        {
            jogo->gameOver = true;
            jogo->tela = TELADERROTA;
        }

        if(WindowShouldClose())
            jogo->fecharJogo = true;

        continuarRodando = (jogo->tela == TELAJOGO && !jogo->fecharJogo) ;
    }


}

