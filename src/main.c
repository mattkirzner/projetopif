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

int x = 34, y = 12;
int pontuacao = 0;
int pontuacaoB = 0;
int incX = 1, incY = 1;
int velocidadeBall=50;

Paddles paddleA = { MAXX * 0.97, MAXY * 0.5 }; // direita
Paddles paddleB = { MINX + 2, MAXY * 0.5 };    // esquerda

void printPaddle(Paddles *p, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        screenGotoxy(p->x_paddle, p->y_paddle + i);
        printf(" ");
    }
    p->y_paddle = nextY;
    for (int i = 0; i < 4; i++) {
        screenGotoxy(p->x_paddle, p->y_paddle + i);
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
    screenGotoxy(65, 0);
    printf("Pontuação B: %d", pontuacaoB);
}

void printGolLines() {
    screenSetColor(RED, DARKGRAY);
    int y_middle = MAXY * 0.5;

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
                case 111: // tecla 'w' - paddleA (direita) sobe
                    if (paddleA.y_paddle > MINY + 1)
                        printPaddle(&paddleA, paddleA.y_paddle - 1);
                    break;
                case 108: // tecla 's' - paddleA desce
                    if (paddleA.y_paddle + 4 < MAXY - 1)
                        printPaddle(&paddleA, paddleA.y_paddle + 1);
                    break;
                case 119: // tecla 'o' - paddleB (esquerda) sobe
                    if (paddleB.y_paddle > MINY + 1)
                        printPaddle(&paddleB, paddleB.y_paddle - 1);
                    break;
                case 115: // tecla 'l' - paddleB desce
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
            if (newY >= MAXY - 1 || newY <= MINY + 1){
                if(velocidadeBall>15) velocidadeBall-=5; // Toda vez que o bola bater na barras Horizantais ela aumenta a velocidade
                timerInit(velocidadeBall);
                incY = -incY;
            }

            // Colisão com paddle vertical (x_paddle fixo, y_paddle variável com altura 4)
            if (newX == paddleA.x_paddle - 1 && newY >= paddleA.y_paddle && newY <= paddleA.y_paddle + 3) {
                timerInit(velocidadeBall=50); // toda vez que o Paddle bater na bola ele volta a velocidade normal
                incX = -incX; // inverte direção horizontal da bola
            }

            // Segundo Paddle.
            if (newX == paddleB.x_paddle + 1 && newY >= paddleB.y_paddle && newY <= paddleB.y_paddle + 3) {
                timerInit(velocidadeBall=50);
                incX = -incX;
            }

            // Verifica se a bola entrou no gol direito
            if (newX == MAXX - 2 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
                pontuacao++;
                incX = -incX;
                velocidadeBall=50; //Reseta a velocidade da bola
            }

            // Verifica se a bola entra no gol esquerdo 
            else if (newX == MINX + 1 && newY >= MAXY / 2 && newY < MAXY / 2 + 4) {
                pontuacaoB++;
                incX = -incX;
                velocidadeBall=50; //Reseta a velocidade da bola
            }

            // Rebater se bater fora da área do gol
            else if (newX >= MAXX - 1 || newX <= MINX + 1) {
                incX = -incX;
            }

            // Limita para não ultrapassar o campo visível
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
