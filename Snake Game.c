#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int height = 20, width = 20, x, y, fruitX, fruitY, obstX, obstY, obstX2, obstY2, obstX3, obstY3;
int dir, gameend, score;
int tailX[100], tailY[100];
int piece = 0;

void generateObstacle() {
    label5:
    obstX = rand() % 20;
    if (obstX == 0)
        goto label5;

    label6:
    obstY = rand() % 20;
    if (obstY == 0)
        goto label6;
}

void generateSecondObstacle() {
    label7:
    obstX2 = rand() % 20;
    if (obstX2 == 0 || obstX2 == obstX)
        goto label7;

    label8:
    obstY2 = rand() % 20;
    if (obstY2 == 0 || obstY2 == obstY)
        goto label8;
}

void generateThirdObstacle() {
    label9:
    obstX3 = rand() % 20;
    if (obstX3 == 0 || obstX3 == obstX || obstX3 == obstX2)
        goto label9;

    label10:
    obstY3 = rand() % 20;
    if (obstY3 == 0 || obstY3 == obstY || obstY3 == obstY2)
        goto label10;
}

void logic()
{
	int i;
	int prevX, prevY, prev2X, prev2Y;
	prevX=tailX[0];
	prevY=tailY[0];
	tailX[0]=x;
	tailY[0]=y;
	for ( i = 1 ; i <= piece ; i++){
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(dir){
		
		case 1:
			x--;
			break;
			
		case 2:
			x++;
			break;
			
		case 3:
			y--;
			break;
			
		case 4:
			y++;
			break;
						
	}
	if (x==0){
		x=height;
	}
	else if (x==height){
		x=0;
	}
	if (y==0){
		y=width;
	}
	else if (y==width){
		y=0;
	}
	
	if ( x==fruitX && y==fruitY){
		label3:
			fruitX=rand()%20;
			if(fruitX==0)
			goto label3;
				
		label4:
			fruitY=rand()%20;
			if(fruitY==0)
			goto label4;
			score+=10;	
			piece++;
	}
	
    //Check for collision with the first obstacle
    if (x == obstX && y == obstY) {
        gameend = 1;
    }

    // Check for collision with the second obstacle
    if (x == obstX2 && y == obstY2) {
        gameend = 1;
    }

    // Check for collision with the third obstacle
    if (x == obstX3 && y == obstY3) {
        gameend = 1;
    }
}

void input() {
    if (kbhit()) {         //kbhit is keyboardhit key
        switch (getch()) {  //getch takes input of char without displaying
            case 'w':
                dir = 1;
                break;

            case 's':
                dir = 2;
                break;

            case 'a':
                dir = 3;
                break;

            case 'd':
                dir = 4;
                break;
        }
    }
}

void setup() {
    x = height / 2;
    y = width / 2;

    label1:
    fruitX = rand() % 20;
    if (fruitX == 0)
        goto label1;

    label2:
    fruitY = rand() % 20;
    if (fruitY == 0)
        goto label2;

    gameend = 0;
    score = 0;

    generateObstacle();
    generateSecondObstacle();
    generateThirdObstacle();
}

void draw() {
    system("cls"); //clears screen
    int i, j, k;
    for (i = 0; i <= height; i++) {
        for (j = 0; j <= width; j++) {
            if (i == 0 || i == height || j == 0 || j == width) {
                printf("*");
            } 
			else {
                if (i == x && j == y) {
                    printf("0");
                } 
				else if (i == fruitX && j == fruitY) {
                    printf("@");
                } 
				else if (i == obstX && j == obstY) {
                    printf("[]");
                } 
				else if (i == obstX2 && j == obstY2) {
                    printf("[]");
                } 
				else if (i == obstX3 && j == obstY3) {
                    printf("[]");
                } 
				else {
                    int ch = 0; // Check for tail
                    for (k = 0; k < piece; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            ch = 1;
                        }
                    }
                    if (ch == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("The score is %d", score);
}

int main() {
    setup();
    while (gameend != 1) {
        draw();
        input();
        logic();
        Sleep(100); // delay of 100ms using windows header file
    }
    return 0;
}
