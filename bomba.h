#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED

#include <stdbool.h>
#include "raylib.h"
#include "mapa.h"

#define MAPAX 27
#define MAPAY 10
#define RAIOBOMBA 3

typedef struct
{
    int x,y;
    bool ativa;
    double tempoAtivacao;
}Bomba;

// Name: verificarExplosao
// Type: Function
// Inputs:
//      Bomba bomba
//      Double tempo : o valor em segundos do tempo em que a bomba foi colocada no jogo
// Output: None.
// Return: Retorna um booleano se ja passou o tempo de explosao da bomba (3 segundos)
// Description: Verifica se ja passou 3 segundos desde que a bomba foi colocada no campo.
bool verificarExplosao(Bomba bomba, double tempo);

// Name: verificarPerimetroExplosao
// Type: Function
// Inputs:
//      int posicaoBomba[] : vetor da posicao da bomba no terreno
//      int perimetroExplosao[] :  vetor do perimetro que a bomba ira cobrir no terreno
// Output: Modifica o vetor perimetroExplosao[], colocando todos os limites possiveis da explosao no lugar em que a bomba foi posta
//       [0] - cima; [1] - baixo; [2] - direita; [3] - esquerda;
// Return: None.
// Description: Muda o vetor de inteiros perimetroExplosao para que ele só acesse os campos corretos da explosao - dado a posicao da bomba.
void verificarPerimetroExplosao(int posicaoBomba[], int perimetroExplosao[]);

// Name: explodir
// Type: Function
// Inputs:
//      Bomba *bomba
//      Mapa *mapa
//      int posMago[] : vetor com a posicao x,y do mago no momento da explosao
// Output: Modifica a struct mapa nos seguintes campos:
//          terreno - tira tudo o que puder dentro do raio da explosao (apenas parede nao destrutivel sobrevive)
//          Montros montro[] - verifica se algum monstro esta no raio da explosao, caso esteja ele é morto.
//         Alem disso, verifica se o mago esta no raio da explosao (é passado um vetor de inteiros com a posciao do mago no momento da explosao)
// Return: Retorna um booleano se o mago estava ou nao no raio da explosao.
// Description: Elimina tudo que é possivel no raio da explosao e retorna se o mago estava ou nao no raio da explosao.
bool explodir(Bomba *bomba, Mapa *mapa,int posMago[]);

#endif // BOMBA_H_INCLUDED
