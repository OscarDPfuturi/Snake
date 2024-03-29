#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

using namespace std;

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);//manipulador, para visualizar los cambios en pantalla

    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hCon,dwPos);//define una posicion en pantalla
}

class Snake{
public:
    int x,y;
    int dx,dy;
    char cuerpo;
};

class Fruta{
public:
    int x,y;
    char cuerpo=254;//codigo ASCII
};

class Juego{
public:
        void main();
private:
        int score,nivel,velocidad;
        Snake snake[100];
        Fruta fruta;
        int tam=4;
        int c=21,f=64;
        bool gameover=false;
        void tablero();
        void genFruta();
        void genSnake();
        void loop();
        void tecla();
        void actualizar();
        void imprimir();
        void cfruta();
        void muerte();
        void puntos();
        void portada();
        void muerte2();

};

void Juego::tablero(){//imprimira los limites del area en el que se movera la serpiente
        char t=178;
        for(int i=1 ; i<f ; i++){
                gotoxy(i,1);
                cout<<t;
                gotoxy(i,c);
                cout<<t;
        }
        for(int i=1 ; i<=c ; i++){
                gotoxy(1,i);
                cout<<t;
                gotoxy(f,i);
                cout<<t;
        }
}

void Juego::genFruta(){//genera y muestra la comida de forma aleatoria
    fruta.x = 2+( rand() % (f-2) );
    fruta.y = 2+(rand() % (c-2));
    gotoxy(fruta.x,fruta.y);
    cout<<fruta.cuerpo;
}

void Juego::genSnake(){//inicia la serpiente
    int i;
    snake[0].x=30;
    snake[0].y=10;
    snake[0].dx=1;
    snake[0].dy=0;
    snake[0].cuerpo=157;

    for(i=1;i < tam; i++){
        snake[i].x=snake[i-1].x-1;
        snake[i].y=snake[i-1].y;
        snake[i].cuerpo=184;
    }

    for(i=0; i<tam; i++){
        gotoxy(snake[i].x,snake[i].y);
        cout<<snake[i].cuerpo;
    }
}

void Juego::loop(){
        while(!gameover){
            cfruta();
            puntos();
            actualizar();
            imprimir();
            tecla();
            tecla();
            tecla();
            muerte();
            Sleep(velocidad);
        }
}

void Juego::tecla(){//leera los botones de direccion por codigo ASCII
    char key;

    if (!gameover){
        if (kbhit()==1){//espera a que se presiones un boton
                key=getch();
        }
        if((key==72) && snake[0].dy !=1){//arriba
                snake[0].dx=0;
                snake[0].dy=-1;
        }
        if((key==80) && snake[0].dy !=-1){//abajo
                snake[0].dx=0;
                snake[0].dy=1;
        }
        if((key==75) && snake[0].dx !=1){//izquierda
                snake[0].dx=-1;
                snake[0].dy=0;
        }
        if((key==77) && snake[0].dx !=-1){//derecha
                snake[0].dx=1;
                snake[0].dy=0;
        }
    }
}

void Juego::portada(){
        system("cls");
        int c=24,f=79;
        char t=178;
        for(int i=0 ; i<f ; i++){
                gotoxy(i,0);
                cout<<t;
                gotoxy(i,c);
                cout<<t;
        }
        for(int i=0 ; i<=c ; i++){
                gotoxy(0,i);
                cout<<t;
                gotoxy(f,i);
                cout<<t;
        }
        gotoxy(23,23);
        cout<<"Presione ENTER para empezar";
        system("pause>dsdsd");
}

void Juego::puntos(){
        gotoxy(f+2,2);
        cout<<"Score: "<<(score-1)*10;
        gotoxy(f+2,4);
        cout<<"Level: "<<nivel;
        gotoxy(f+2,6);
        cout<<"Length: "<<tam;
}

void Juego::muerte(){// si la serpiente toca los limites del area de juego o a si mismo, termina el juego
    if(snake[0].x==1 || snake[0].x==f || snake[0].y==1 || snake[0].y==c)
        gameover=true;

    for(int i=1;i<tam && gameover==false;i++){
        if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
            gameover=true;
        }
    }
}

void Juego::muerte2(){//opciones para seguir jugando o salir
        system("cls");
        int c=24,f=79,r;
        char key;
        char t=178;
        for(int i=0 ; i<f ; i++){
                gotoxy(i,0);
                cout<<t;
                gotoxy(i,c);
                cout<<t;
        }
        for(int i=0 ; i<=c ; i++){
                gotoxy(0,i);
                cout<<t;
                gotoxy(f,i);
                cout<<t;
        }

        char g4meover[]="GAME OVER!!!";
        r=2;
        gotoxy(15,r);
        for(int i=0;i<12;i++){
            cout<<g4meover[i];
        }

        gotoxy(33,r);
        cout<<"Score: "<<score;
        r++;
        gotoxy(33,r);
        cout<<"Level: "<<nivel;
        gotoxy(8,23);
        cout<<"Presione ESC para salir o cualquier otra tecla para seguir jugando";
        key=getch();
        if(key==27) exit(1);
}

void Juego::cfruta(){//comer la fruta
    if(snake[0].x==fruta.x && snake[0].y==fruta.y){
        genFruta();
        tam+=1;
        snake[tam-1].cuerpo=184;
        score+=1;
        if(tam%10==0){
            nivel++;
            velocidad-=20;
        }
    }
}

void Juego::actualizar(){//actualiza el tama�o de la serpiente
        int i;
        gotoxy(snake[tam-1].x,snake[tam-1].y);
        cout<<" ";

    for (i= tam-1; i>0; i--){
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
    snake[0].x += snake[0].dx;
    snake[0].y += snake[0].dy;
}

void Juego::imprimir(){// muestra la serpiente
        int i;
        for(i= tam-1; i>=0; i--){
            gotoxy(snake[i].x,snake[i].y);
            cout<<snake[i].cuerpo;
        }
}


void Juego::main(){//inicia el juego
        system("color 0b");//color de la pantalla y contenido
        gameover=false;
        portada();
        system("cls");
        score=1;
        velocidad=110;
        tam=4;
        nivel=1;
        tablero();
        srand(time(NULL));
        genSnake();
        genFruta();
        loop();
        muerte2();
        main();
}

int main(){
        Juego j;
        j.main();
}
