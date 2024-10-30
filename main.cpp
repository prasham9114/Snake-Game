#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

// general variables
bool gameOver;
const int width = 40;
const int height = 20;
int x, y , fruitX, fruitY, score;
enum eDirection {STOP =0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];
int ntail;

void setup()
{
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand()%width; // random bw 0 to width - 1
    fruitY = rand()%height; // random bw 0 to height -1 
    score = 0;
}

void draw()
{
    // step 1 is to clear the screen
    system("cls");

    for(int i =0 ; i<width+2; i++){
        cout << "#" ; 
    }
    cout << endl;
    
    for(int i=0 ; i<height; i++){
        for(int j=0; j<width; j++){
            if (j==0){
                cout <<"#";
            }
            if(i == y && j ==x){
                cout << "O";
            }
            else if(j == fruitX && i == fruitY){
                cout << "F";
            }
            else
            {
                bool print = false;
                for(int k = 0 ; k < ntail ; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o"; 
                        print = true;    
                    }
                }
                    if(!print){
                        cout << " ";
                    }
            }

            if (j == width-1){
                cout<< "#";
            }
        }cout << endl;
    }
    
    for(int i =0 ; i<width+2; i++){
        cout << "#" ; 
    }
    cout << endl;
    cout << "\nScore : " << score;
}

void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a': 
                if (dir != RIGHT) dir = LEFT;  
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if(dir != UP) dir = DOWN;
                break;
            case 'x' :
                gameOver = true;
                break;
        }
    }    
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x ; 
    tailY[0] = y;
    for (int i = 1; i<ntail ; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir){
        case UP:
            y-- ;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;   
            break;
        default:
            break;
    }

    
    if (x>width){
        x=0;
    }
    else if (x<0){
        x = width-1;
    }

    if (y>height){
        y=0;
    }
    else if (y<0){
        y = height-1;
    }
    
    for (int i =0; i<ntail ; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY){
        score +=10;
        fruitX = rand() % width ;
        fruitY = rand() % height ;
        ntail++;    
    }
}


int main()
{
    cout<< "The Snake Game";
    cout<< "\nPress 1 to Play\nPress 2 to Exit\n";
    cout << "select: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    setup();

    while(!gameOver)
    {
        draw();
        input();
        logic();    
        Sleep(10);
    }   
    if(gameOver){
        system("cls");
        cout << "\nGame Over";
        system("pause");
    }
    return 0;
}