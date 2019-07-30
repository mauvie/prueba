#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

#define Arriba 72
#define Abajo 80
#define Izquierda 75
#define Derecha 77

void gotoxy(int x,int y)   /* Mueve el cursor del texto a la posicion segun las coordenadas especificadas por los argumentos x y y */
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void Ocultar_Cursor()
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;   //Tamano del cursor
    cci.bVisible = FALSE;  //no me permite que se vea
    SetConsoleCursorInfo(hcon, &cci);
}

void menu()
{

    int opcion, a;
    system("color f0");

    printf("\tJuego de Laberinto.\n");
    printf("\n");
    printf("Menu del laberinto\n\n");
    printf("Seleccione la opcion a desear\n\n ");
    printf("1) Nivel\n");
    printf(" 2) Historial\n");
    printf(" 3) Salir\n");
    printf("\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    system("cls");

    switch (opcion)
    {

    case 1:
        menu_niveles();
        break;

    case 2:
        mostrar_hist();
        break;

    case 3:
        printf("Seguro que desea salir? Si o No\n");
        printf("\n");
        printf("1- Si\n");
        printf("2- No\n");
        printf("\n");
        printf("Opcion: ");
        scanf("%i", &a);
        printf("\n");
        if (a==1)
        {
            printf("Has salido correctamente\n");
        }
        else
        {
           return menu();

        }
        break;

    default:
        printf("\n");
        printf("Has seleccionado una opcion incorrecta. Vuelva a intentarlo");
        printf("\n");
    }
}

void menu_niveles(){

    int opcion;
    char * nivel;
    system("color f0");

    printf("Seleccione el nivel\n\n ");
    printf("1) Nivel 1\n");
    printf(" 2) Nivel 2\n");
    printf(" 3) Nivel 3\n");
    printf(" 4) Nivel 4\n");
    printf(" 5) Nivel 5\n");
    printf("\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    system("cls");

    switch (opcion)
    {

    case 1:
        nivel = "Nivel1.txt";
        break;

    case 2:
        nivel = "Nivel2.txt";
        break;

    case 3:
        nivel = "Nivel3.txt";
        break;
    case 4:
        nivel = "Nivel4.txt";
        break;
    case 5:
        nivel = "Nivel5.txt";
        break;
    default:
        printf("\n");
        printf("Has seleccionado una opcion incorrecta. Vuelva a intentarlo");
        printf("\n");
    }

    juego(nivel);
    a_puntuacion(guardarSeg);
}
void llenar(char tt[100][100], char nivel[100])
{
    FILE *arc;
    arc = fopen(nivel,"r");
    char s;
    int f=0;
    int c=0;

    while (s!=-1)
    {
        s=getc(arc);

        if(s!='\n')
        {
            tt[f][c] = s;
            f+=1;
        }
        else
        {
            c+=1;
            f=0;
        }
    }
}

void generar(char nivel[100])
{

    char s[100][100];
    llenar(s,nivel);

    for(int f=0; f<10; f++)
    {
        for(int c=0; c<37; c++)
        {
            if(s[c][f]=='#')
            {
                printf("\xDB");
            }
            else if(s[c][f]=='*')
            {
                printf(" ");
            }
            else if(s[c][f]=='I')
            {
                printf("I");
            }
            else if(s[c][f]=='F')
            {
                printf("F");
            }
        }
        printf("\n");
    }
}

void juego(char n[100])
{
    char tablero[100][100];
    llenar(tablero,n);

    Ocultar_Cursor();
    generar(n);

    int x = 0, y = 5;
    int seg=0;

    gotoxy(x,y);
    system("color f0"); //color blanco
    printf("%c", 227); //objeto usado

    bool game_over = false; //solo devuelve true o false
    while(!game_over)
    {
        if(kbhit())
        {

            char tecla = getch();
            gotoxy(x,y);
            printf(".");
            if(tablero[x+1][y]!='#')
            {
                if (tecla == Derecha)
                    x++;
            }

            if(tablero[x-1][y]!='#')
            {
                if (tecla == Izquierda)
                    x--;
            }

            if(tablero[x][y+1]!='#')
            {
                if (tecla == Abajo)
                    y++;
            }

            if(tablero[x][y-1]!='#')
            {
                if (tecla == Arriba)
                    y--;
            }
            if(tablero[x][y]=='F')
            {
                game_over=TRUE;
                guardarSeg = seg;
                gotoxy(36,9);
                printf("\nHas logrado llegar a la meta");

            }
            gotoxy(x,y);
            printf("%c", 227);

        }
        Sleep(10);

        seg +=10;
        if(seg%1000==0)
        {
            gotoxy(1,12);
            printf("Tiempo: %d",seg/1000);
        }
    }
}

void a_puntuacion(int t)
{

    FILE *punt;
    jugador jug;

    punt = fopen("Historial.txt","a+");
    gotoxy(1,13);

    printf("Ingrese su nombre:  ");
    scanf("%s", &jug.nombre);

    jug.tiempo = t;
    fwrite(&jug, sizeof(jug), 1, punt);
    fclose(punt);
}

//void mostrar_hist()
//{
//    FILE *hist;
//    jugador juga;
//    hist = fopen("Historial.txt", "r");
//    char a;
//
//    while (a!=-1) // es lo mismo que EOF, recuerda preguntar si el archivo existe...
//    {
//
//        printf("\n Nombre\t\tTiempo\n");
//        fread(&juga, sizeof(juga), 1, hist);
//        printf(" %s\t%d", juga.nombre, juga.tiempo);
//
//    }
//
//    fclose(hist);
//}

void mostrar_hist()//funcion modificada por William
{
    FILE *hist;
    //jugador juga;
    hist = fopen("Historial.txt", "r");
    char a;

    while (a!=-1) // es lo mismo que EOF, recuerda preguntar si el archivo existe...
    {

        printf("\n Nombre\t\tTiempo\n");
        //Aquí extraes todo el texto y       lo metes en la variable char a
        fgets(a,15*15,hist);

//Aquí va a imprimir todo el texto y en orden, todo depende de cómo lo ingreses
        printf("%s",a);

    }

    fclose(hist);
}

//jugador * leer_archivo(char * nombre_archivo){
//
//    int cant_jugad;
//    char buff[500];
//    jugador* mis_jugadores;
//
//    FILE * p = fopen(nombre_archivo, "r");
//
//    if (p==NULL){
//        return NULL;
//    }
//
//    fread(&cant_jugad, sizeof(int), 1, p);
//    mis_jugadores = malloc(cant_jugad* sizeof(jugador));
//    fread(mis_jugadores, sizeof(jugador), cant_jugad, p);
//
////    while((fgets(buff,1024, (FILE*)p))!= EOF){
////        printf("%s", buff);
////    }
//
//    for (int i = 0; i < cant_jugad; ++i) {
//        mis_jugadores[i].nombre = calloc(500, sizeof(char));
//        fread(buff, sizeof(char), 500, p);
//        strcpy(mis_jugadores[i].nombre, buff);  //arreglo temporal
//
//}
//
//    fclose(p);
//    return mis_jugadores;
//
//}
//
//int guardar_archivo(char * nombre_archivo, jugador * jug, int cant_jugador){
//
//    FILE * p;
//    p = fopen(nombre_archivo, "w");
//    char buff[200];
//
//    if (p==NULL){
//        return 0;
//
//    }
//
//    fprintf(&cant_jugador, sizeof(int), 1, p);
//    fprintf(cant_jugador, sizeof(jugador), cant_jugador, p);
//
//    for (int i = 0; i < cant_jugador; ++i) {
//        strcpy(buff, jug[i].nombre);
//        fprintf(buff, sizeof(char), 200, p);
//    }
//
//    fclose(p);
//    return 1;
//
//}

char * leer_archivo_texto(char * nombre_archivo){
FILE * fp;
char * texto = NULL;
int i = 0;
char c;
    fp = fopen("C:\\tmp\\mis_calculos.hola", "r");
if (fp==NULL){
printf("Error abriendo el archivo",stderr);
return NULL;
    }
while ((c=fgetc(fp))!=EOF){
if (texto==NULL){
            texto = (char*) calloc(i+2, sizeof(char));
        } else{
            texto = (char*) realloc(texto, (i+2)* sizeof(char));
        }
if (texto==NULL){
printf("Error reservando memoria para el string", stderr);
return NULL;
        }
        texto[i++]=c;
    }
fclose(fp);
    texto[i]='\0';
return texto;
}

void guardar_archivo_texto(char * nombre_archivo, char * contenido){

FILE * p;

    p = fopen(contenido, "a+t");
if (p==NULL){
return 0;
    }
fputs("Esto es un ejemplo", p);
fclose(p);
return 1;
}
