#ifndef Headers_h
#define Headers_h

#include <stdbool.h>

#define ANSI_RED "\e[31m"
#define ANSI_GREEN "\e[32m"
#define ANSI_YELLOW "\e[33m"
#define ANSI_BLUE "\e[34m"
#define ANSI_MAGENTA "\e[35m"
#define ANSI_CYAN "\e[36m"
#define ANSI_bRED "\e[91m"
#define ANSI_bGREEN "\e[92m"
#define ANSI_bYELLOW "\e[93m"
#define ANSI_bBLUE "\e[94m"
#define ANSI_bMAGENTA "\e[95m"
#define ANSI_bCYAN "\e[96m"
#define ANSI_RESET "\e[0m"
#define FILAS 101
#define COLUM 1

struct claveRep{
    char contrasenia[FILAS][COLUM];
    char nombre[FILAS];
    bool estado;
};
typedef struct claveRep *clave;


int vaciar_buffer(void);

void pausa();

void limpiar_pantalla();

int menu_caracteres();

int Cant_char_per_contra();

void cargarRandom(int v[], int util, int numRand);

void Generar_clave(int vNumeros[], char vChar[FILAS][COLUM], int utilf, int utilc,int opc);

void MostrarMatriz(char matriz[FILAS][COLUM], int utilf, int utilc);

void mostrar_lista_contra();


#endif // Headers_h