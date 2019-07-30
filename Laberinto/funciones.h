#ifndef funciones_h
typedef struct
{
    char *nombre;
    int tiempo;
} jugador;

int guardarSeg; //variable global

void menu();
void juego(char n[100]);
void a_puntuacion(int t);
void mostrar_hist();
void Ocultar_Cursor();
void gotoxy(int x,int y);
void llenar(char tt[100][100], char nivel[100]);
void generar(char nivel[100]);
void menu_niveles();
//jugador * leer_archivo(char * nombre_archivo);
//int guardar_archivo(char * nombre_archivo, jugador * jug, int cant_jugador);
char * leer_archivo_texto(char * nombre_archivo);
void guardar_archivo_texto(char * nombre_archivo, char * contenido);
#endif // funciones_h
