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
    /* data */
} Paddles;

int x = MAXX / 2, y = MAXY / 2;
int pontuacao = 0;
int pontuacaoB = 0;
int incX = 1, incY = 1;
int velocidadeBall = 50;

Paddles paddleA = { MAXX - 3, MAXY / 2 };   // direita (borda direita corrigida)
Paddles paddleB = { MINX + 2, MAXY / 2 };   // esquerda (borda esquerda corrigida)

void printPaddle(Paddles *p, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        //Usando p-> para modificar diratamente a struct e nao uma copia
        screenGotoxy(p->x_paddle, p->y_paddle + i); // Apaga paddle antigo
        printf(" ");
    }
    p->y_paddle = nextY;
    for (int i = 0; i < 4; i++) {
        screenGotoxy(p->x_paddle, p->y_paddle + i); // Desenha paddle novo
        printf("|");
    }
}

void printBall(int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("O");
}

void printKey(int ch) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit()) {
        printf("%d ", readch());
    }
}

void printPontuacao() {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(0, 0);
    printf("Pontuação A:  %d", pontuacao);
}

void printPontuacaoB() {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(MAXX - 20, 0);
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

int main() {
    static int ch = 0;
    static long timer = 0;

    screenInit(1);
    keyboardInit();
    timerInit(70);

    printBall(x, y);
    printPaddle(&paddleA, paddleA.y_paddle);
    printPaddle(&paddleB, paddleB.y_paddle);
    printPontuacao();
    printPontuacaoB();
    printGolLines(); // desenha as gol lines
    screenUpdate();

    while (ch != 10) // Enter para sair
    {
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
            }

            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            int newY = y + incY;

            // Rebater nas bordas superior e inferior
            if (newY >= MAXY - 1 || newY <= MINY + 1) {
                if (velocidadeBall > 15) velocidadeBall -= 5; // Aumenta a velocidade da bola a cada batidada na horizantal
                timerInit(velocidadeBall);
                incY = -incY;
            }

            // Colisão com paddleA (direita)
            if (newX == paddleA.x_paddle - 1 && newY >= paddleA.y_paddle && newY <= paddleA.y_paddle + 3) {
                timerInit(velocidadeBall = 50); //Bola volta ao normal ao tocar no paddle
                incX = -incX;
            }

            // Colisão com paddleB (esquerda)
            if (newX == paddleB.x_paddle + 1 && newY >= paddleB.y_paddle && newY <= paddleB.y_paddle + 3) {
                timerInit(velocidadeBall = 50);
                incX = -incX;
            }

            // Gol direita
            if (newX == MAXX - 2 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
                pontuacao++;
                incX = -incX;
                velocidadeBall = 50;
            }

            // Gol esquerda
            else if (newX == MINX + 1 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
                pontuacaoB++;
                incX = -incX;
                velocidadeBall = 50;
            }

            // Rebater nas bordas laterais fora do gol
            else if (newX >= MAXX - 1 || newX <= MINX + 1) {
                incX = -incX;
            }

            // Corrige limites
            if (newX >= MAXX - 1) newX = MAXX - 2;
            if (newX <= MINX + 1) newX = MINX + 2;

            printBall(newX, newY);
            printPaddle(&paddleA, paddleA.y_paddle);
            printPaddle(&paddleB, paddleB.y_paddle);
            printPontuacao();
            printPontuacaoB();
            printGolLines(); // desenha as gol lines
            screenUpdate();
            timer++;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}