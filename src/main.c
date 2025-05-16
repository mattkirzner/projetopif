/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

typedef struct 
{ 
    int x_paddle, y_paddle;
    
} Paddles;

typedef struct 
{
    int incX;
    int incY;
    int x,y;
    
} Ball;


int x = MAXX / 2, y = MAXY / 2;
int pontuacao = 0;
int pontuacaoB = 0;
Ball ball = {1, 1, MAXX / 2, MAXY / 2};        // Bola principal, com incrementos iniciais 1 e 1
//Ball extraBall = {-1, -1, MAXX / 2, MAXY / 2}; // Bola extra, inicialmente inativa (incX = incY = -1)
int velocidadeBall = 50;
int activateBall = 0;

Paddles paddleA = { MAXX - 3, 1+MAXY / 2 };   // direita (borda direita corrigida)
Paddles paddleB = { MINX + 2, 1+MAXY / 2 };   // esquerda (borda esquerda corrigida)

// Variável global para controlar o estado do jogo (pausado ou jogando)
int gameState = 0; // 0 em pausa, 1 jogando, o jogo começa pausado

void printPaddle(Paddles *p, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    for (int i = 0; i < 2; i++) {
        // Usando p-> para modificar diretamente a struct e não uma cópia
        screenGotoxy(p->x_paddle, p->y_paddle + i); // Apaga paddle antigo
        printf(" ");
    }
    p->y_paddle = nextY;
    for (int i = 0; i < 2; i++) {
        screenGotoxy(p->x_paddle, p->y_paddle + i); // Desenha paddle novo
        printf("|");
    }
}

void printBall(Ball *b, int newX, int newY) { // Passando a struct da bola e alterando como ponteiro para alterar diretamente a struct
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(b->x, b->y);
    printf(" ");
    b->x = newX;
    b->y = newY;
    screenGotoxy(b->x, b->y);
    printf("O");
}

void printResult(int pontuacao, int pontuacaoB) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    if (pontuacao > pontuacaoB)
    {
        printf("Player 1 Wins");
    }
    
    if (pontuacao < pontuacaoB)
    {
        printf("Player 2 Wins");
    }

    // screenGotoxy(34, 23);
    // printf("            ");
    
    // if (ch == 27) screenGotoxy(36, 23);
    // else screenGotoxy(39, 23);

    // printf("%d ", ch);
    // while (keyhit()) {
    //     printf("%d ", readch());
    // }
}

void printPontuacao() {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(20, 0);
    printf("Pontuação A:  %d", pontuacao);
}

void printPontuacaoB() {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(MAXX - 40, 0);
    printf("Pontuação B: %d", pontuacaoB);
}

void printGolLines() {
    screenSetColor(RED, DARKGRAY);
    int y_middle = MAXY / 2;

    // Gol line esquerda
    for (int i = 0; i < 4; i++) {
        screenGotoxy(MINX + 1, y_middle + i);
        printf("|");
    }

    // Gol line direita
    for (int i = 0; i < 4; i++) {
        screenGotoxy(MAXX - 2, y_middle + i);
        printf("|");
    }
}

// Função para atualizar a lógica da bola usando struct Ball
// Funcao principal de atualizacao do jogo.
void updateBall(Ball *b) {
    int newX = b->x + b->incX;
    int newY = b->y + b->incY;

    // Rebater nas bordas superior e inferior
    if (newY >= MAXY - 1 || newY <= MINY + 1) {
        if (velocidadeBall > 15) velocidadeBall -= 5; // Aumenta a velocidade da bola a cada batidada na horizontal
        timerInit(velocidadeBall);
        b->incY = -b->incY;
    }

    // Colisão com paddleA (direita)
    if (newX == paddleA.x_paddle - 1 && newY >= paddleA.y_paddle && newY <= paddleA.y_paddle + 3) {
        timerInit(velocidadeBall = 50); // Bola volta ao normal ao tocar no paddle
        b->incX = -b->incX;
    }

    // Colisão com paddleB (esquerda)
    if (newX == paddleB.x_paddle + 1 && newY >= paddleB.y_paddle && newY <= paddleB.y_paddle + 3) {
        timerInit(velocidadeBall = 50);
        b->incX = -b->incX;
    }

    // Gol direita
    if (newX == MAXX - 2 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
        pontuacao++;
        b->incX = -b->incX;
        timerInit(velocidadeBall = 50);
        newX = MAXX / 2; // manda a bola para o meio da tela
        newY = MAXY / 2;
        // Pause o jogo só se for a bola principal
        if (b == &ball) {
            gameState = 0;
        }
    }

    // Gol esquerda
    else if (newX == MINX + 1 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
        pontuacaoB++;
        b->incX = -b->incX;
        timerInit(velocidadeBall = 50);
        newX = MAXX / 2; // manda a bola para o meio da tela
        newY = MAXY / 2;
        // Pause o jogo só se for a bola principal
        if (b == &ball) {
            gameState = 0;
        }
    }

    // Rebater nas bordas laterais fora do gol
    else if (newX >= MAXX - 1 || newX <= MINX + 1) {
        b->incX = -b->incX;
    }

    // Corrige limites
    if (newX >= MAXX - 1) newX = MAXX - 2;
    if (newX <= MINX + 1) newX = MINX + 2;

    printBall(b, newX, newY);
}



int main() {
    static int ch = 0;
    static long timer = 0;
    // int gameState = 0; // Variável global já declarada

    screenInit(1);
    keyboardInit();
    timerInit(70);

    printBall(&ball, ball.x, ball.y);
    printPaddle(&paddleA, paddleA.y_paddle);
    printPaddle(&paddleB, paddleB.y_paddle);
    printPontuacao();
    printPontuacaoB();
    printGolLines(); // desenha as gol lines
    screenUpdate();

    while (ch != 10 && pontuacao < 13 && pontuacaoB < 13) // Enter para sair. O jogo também termina se um jogador
    {                                                       // conseguir mais de 13 pontos
        if (keyhit()) {
            ch = readch();

            switch (ch) {
                case 111: // tecla 'o' - paddleA (direita) sobe
                    if (paddleA.y_paddle > MINY + 1)
                        printPaddle(&paddleA, paddleA.y_paddle - 1);
                    break;
                case 108: // tecla 'l' - paddleA desce
                    if (paddleA.y_paddle + 4 < MAXY - 1)
                        printPaddle(&paddleA, paddleA.y_paddle + 1);
                    break;
                case 119: // tecla 'w' - paddleB (esquerda) sobe
                    if (paddleB.y_paddle > MINY + 1)
                        printPaddle(&paddleB, paddleB.y_paddle - 1);
                    break;
                case 115: // tecla 's' - paddleB desce
                    if (paddleB.y_paddle + 4 < MAXY - 1)
                        printPaddle(&paddleB, paddleB.y_paddle + 1);
                    break;
                case 32: // tecla espaço, jogo começa
                    gameState = 1;
                    break;
            }

            screenUpdate();
        }
       
        // LOGICA DO JOGO
        if (timerTimeOver() == 1 && gameState == 1) {
            updateBall(&ball);

        
            printPaddle(&paddleA, paddleA.y_paddle);
            printPaddle(&paddleB, paddleB.y_paddle);
            printPontuacao();
            printPontuacaoB();
            printGolLines(); // desenha as gol lines
            screenUpdate();
            timer++;
        }
    }

    printResult(pontuacao, pontuacaoB);
    screenGotoxy(32, 23);
    printf("Pressione ENTER para sair...");
    screenUpdate();
    while (readch() != 10); // While como barreira para o Jogador ler a Mensagem
    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}