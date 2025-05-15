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
{ int x_paddle,y_paddle;
    /* data */
}Paddles;


int x = 34, y = 12;
int pontuacao = 0;
int pontuacaoB = 0;
int x_paddle = MAXX *0.97;  // paddle na direita
int y_paddle = MAXY * 0.5;  // paddle começa no meio vertical
int x_paddleT = MINX + 2; 
int y_paddleT = MAXY * 0.5;
int incX = 1, incY = 1;

void printPaddle(int nextY) {
    screenSetColor(CYAN, DARKGRAY);

    // Apaga paddle antigo
    for (int i = 0; i < 4; i++) {
        screenGotoxy(x_paddle, y_paddle + i);
        printf(" ");
    }

    y_paddle = nextY;

    // Desenha paddle novo
    for (int i = 0; i < 4; i++) {
        screenGotoxy(x_paddle, y_paddle + i);
        printf("|");
    }
}

void printPaddleTwo(int nextY) {
    screenSetColor(CYAN, DARKGRAY);

    // Apaga paddle antigo
    for (int i = 0; i < 4; i++) {
        screenGotoxy(x_paddleT, y_paddleT + i);
        printf(" ");
    }

    y_paddleT = nextY;

    // Desenha paddle novo
    for (int i = 0; i < 4; i++) {
        screenGotoxy(x_paddleT, y_paddleT + i);
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
    printPaddleTwo(y_paddleT);
    printPaddle(y_paddle);
    printPontuacao();
    printPontuacaoB();
    printGolLines(); // desenha as gol lines
    screenUpdate();

    while (ch != 10) // Enter para sair
    {
        if (keyhit()) {
            ch = readch();
            

            switch (ch) {
                case 111: // tecla 'w' - mover paddle para cima
                    if (y_paddle > MINY + 1) // limite superior
                        printPaddle(y_paddle - 1);
                    break;

                case 108: // tecla 's' - mover paddle para baixo
                    if (y_paddle + 4 < MAXY - 1) // limite inferior (4 é tamanho do paddle)
                        printPaddle(y_paddle + 1);
                    break;
                    
                case 119: // tecla 'o' - paddle esquerdo sobe
                    if (y_paddleT > MINY + 1)
                        printPaddleTwo(y_paddleT - 1);
                    break;
                case 115: // tecla 'l' - paddle esquerdo desce
                     if (y_paddleT + 4 < MAXY - 1)
                         printPaddleTwo(y_paddleT + 1);
                    break;
            
                }


            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            int newY = y + incY;

            // Rebater nas bordas superior e inferior
            if (newY >= MAXY - 1 || newY <= MINY + 1){
                timerInit(30); // Toda vez que o bola bater na barras Horizantais ela aumenta a velocidade
                incY = -incY;

            }

            // Colisão com paddle vertical (x_paddle fixo, y_paddle variável com altura 4)
            if (newX == x_paddle - 1 && newY >= y_paddle && newY <= y_paddle + 4) {
                timerInit(70); // toda vez que o Paddle bater na bola ele volta a velocidade normal
                incX = -incX; // inverte direção horizontal da bola
            }
            // Segundo Paddle.
            if (newX == x_paddleT + 1 && newY >= y_paddleT && newY <= y_paddleT + 4) {
                timerInit(70);
                incX = -incX;
            }

            //Verifica se a bola entrou no gol direito
            if (newX == MAXX - 2 && newY >= MAXY/2 && newY < MAXY/2 + 4) {
                 pontuacao++;
                 incX = -incX;
            }

                // Verifica se a bola entra no gol esquerdo 
            else if (newX == MINX + 1 && newY >= MAXY/2 && newY < MAXY/2 + 4) {
                pontuacaoB++;
                incX = -incX;
            }

              // Rebater se bater fora da área do gol
            else if (newX >= MAXX - 1 || newX <= MINX + 1) {
                incX = -incX;
            }
             // Limita para não ultrapassar o campo visível
            if (newX >= MAXX - 1) newX = MAXX - 2;
            if (newX <= MINX + 1) newX = MINX + 2;

            

            printBall(newX, newY);
            printPaddle(y_paddle);
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