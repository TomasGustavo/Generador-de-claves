#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "Headers.h"
#define FILAS 101
#define COLUM 1

int vaciar_buffer(void)
{
    char nada[200];
    fgets(nada, 200, stdin);
    return 0;
}

void pausa()
{
    printf(ANSI_YELLOW "\npresione ENTER para continuar...." ANSI_RESET);
    getchar();
}

void limpiar_pantalla()
{
    printf("\033[2J\033[1;1H");
    return;
}

void mostrar_menu(){

    printf(ANSI_CYAN "\t\tSeleccione el nivel de seguridad de la clave: \n\n");
    printf("\t\t1- Sencilla (Numérica)\n");
    printf("\t\t2- Intermedia (AlfaNumerica)\n");
    printf("\t\t3- Segura (AlfaNumerica + Caracteres especiales)\n\n");
    printf(ANSI_RED "\t\t\t0- Salir\n");
 
    printf(ANSI_YELLOW "opción: " ANSI_RESET);
}

int menu_caracteres()
{
    // pido por teclado el nivel de seguridad de cada contraseña 
    int opc = -1;
    mostrar_menu();
    scanf("%d", &opc);
    vaciar_buffer();

    while (opc != 0 && opc != 1 && opc != 2 && opc != 3)
    {
        printf(ANSI_RED "-------- ERROR -------- \n" ANSI_RESET);
        printf(ANSI_RED "Opción no valida, por favor seleccionar algunas de las opciones disponibles \n" ANSI_RESET);
        pausa();
        limpiar_pantalla();
        mostrar_menu();
        scanf("%d", &opc);
        vaciar_buffer();
        pausa();
        
        
    }
    

    return opc;
}


/// @brief Ingresa por teclado la cantidad de caracteres que va a tener cada contraseña
/// @return Int con la cantidad ingresada.
int Cant_char_per_contra()
{
    // pido por teclado la cantidad de caracteres que van a poseer las contraseñas
    int cant = 0;
    printf(ANSI_CYAN "ingrese la cantidad de caracteres que desee que tenga la contraseña (máximo 100 caracteres): " ANSI_RESET);
    int validador = scanf("%d", &cant);
    vaciar_buffer();
    while ((cant <= 0 || cant > 100) || validador != 1)
    {
        printf(ANSI_RED "-------- ERROR -------- \n" ANSI_RESET);

        if (validador != 1)
        {
            printf(ANSI_YELLOW "Por favor ingrese un numero entero, letras o caracteres especiales no son admitidos " ANSI_RESET);
        }
        else
        {
            printf(ANSI_YELLOW "la cantidad de caracteres tiene que ser entre 0 y 100, por favor ingrese nuevamente:  " ANSI_RESET);
        }
        validador = scanf("%d", &cant);
        vaciar_buffer();
    }

    printf(ANSI_CYAN "Cantidad de caracteres a generar: " ANSI_bGREEN "%d\n" ANSI_RESET, cant);

    return cant;
}


/// @brief Carga un vector con números generados aleatoriamente
/// @param v vector con los números a cargar
/// @param util Cantidad de números a cargar
/// @param numRand rango máximo de números a generar
void cargarRandom(int v[], int util, int numRand)
{
    // cargo de manera random un vector con números en base a la cantidad
    // de distintos valores unitarios de caracteres
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < util; i++)
    {
        v[i] = rand() % numRand;
    }
}



/// @brief Genera la contraseña y la guarda en una matriz
/// @param vNumeros Vector cargado de números aleatorios
/// @param vChar    Matriz donde se cargaran las contraseñas
/// @param utilf    Cantidad de filas utilizadas en la matriz
/// @param utilc    Cantidad de columnas utilizadas en la matriz (hardcodeado a 1)
/// @param opc      Nivel de seguridad de la contraseña
void Generar_clave(int vNumeros[], char vChar[FILAS][COLUM], int utilf, int utilc, int opc)
{
    // defino los 3 posibles diccionarios de caracteres que se usaran en base al nivel de seguridad seleccionado
    int f, c, i;

    char AlfabetoNum[10][1] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char AlfabetoAlfaNum[36][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                   "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char Alfabeto[45][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                            "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                            "!", "&", "+", "*", "<", ">", ",", ".", "?"};
    if (opc == 0)
    {
        printf(ANSI_GREEN "Gracias por usar la app <3 !!" ANSI_RESET);
        return;
    }

    else
    {
        int cant = Cant_char_per_contra();
        if (opc == 1)
        {
            cargarRandom(vNumeros, cant, 10);
            for (f = 0; f < cant; f++)
            {
                for (c = 0; c < utilc; c++)
                {
                    vChar[f][c] = AlfabetoNum[vNumeros[f]][c];
                }
            }
            return;
        }
        if (opc == 2)
        {
            cargarRandom(vNumeros, cant, 36);
            for (f = 0; f < cant; f++)
            {
                for (c = 0; c < utilc; c++)
                {
                    vChar[f][c] = AlfabetoAlfaNum[vNumeros[f]][c];
                    if (vNumeros[f] >= 0 && vNumeros[f] <= 27)
                    {
                        i = rand() % 2 + 1;
                        if (i == 1)
                        {
                            vChar[f][c] = vChar[f][c] - 32;
                        }
                    }
                }
            }
        }

        if (opc == 3)
        {
            cargarRandom(vNumeros, cant, 45);
            for (f = 0; f < cant; f++)
            {
                for (c = 0; c < utilc; c++)
                {
                    vChar[f][c] = Alfabeto[vNumeros[f]][c];
                    if (vNumeros[f] >= 0 && vNumeros[f] <= 27)
                    {
                        i = rand() % 2 + 1;
                        if (i == 1)
                        {
                            vChar[f][c] = vChar[f][c] - 32;
                        }
                    }
                }
            }
        }
    }
}


/// @brief Muestra una Matriz
/// @param matriz Matriz a mostrar
/// @param utilf  Cantidad de filas utilizadas en la matriz
/// @param utilc  Cantidad de columnas utilizadas en la matriz (hardcodeado a 1)
void MostrarMatriz(char matriz[FILAS][COLUM], int utilf, int utilc)
{
    int f, c;
    printf(ANSI_GREEN "\nContraseña: " ANSI_RESET);
    for (f = 0; f < utilf; f++)
    {

        for (c = 0; c < utilc; c++)
        {
            printf(ANSI_bGREEN "%c" ANSI_RESET, matriz[f][c]);
        }
    }
    printf("\n");
    pausa();
}

int main()
{
    int v[FILAS] = {};
    char vC[FILAS][COLUM] = {};
    int canta_claves=-1, opc;
    int utilf = FILAS, utilc = 1;
    int contador=0;

    limpiar_pantalla();

    
    // Guardo en la variable contador el numero que hay y cierro el archivo.
    FILE *archivo = fopen("contador.txt", "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d", &contador);
        fclose(archivo);
    }

    while (canta_claves != 0){

        printf(ANSI_bBLUE "Ingrese la cantidad de calves que quiere generar (0- Salir): " ANSI_RESET);
        int validador = scanf("%d", &canta_claves);
        vaciar_buffer();

        while (canta_claves < 0 || validador != 1){

            if (validador != 1){
                printf(ANSI_RED "-------- ERROR -------- \n" ANSI_RESET);
                printf(ANSI_RED "No se admiten letras ni otro tipo de caracteres \n" ANSI_RESET);
                printf(ANSI_bBLUE "Ingrese la cantidad de claves que quiere generar (0- Salir): " ANSI_RESET);
                validador = scanf("%d", &canta_claves);
                vaciar_buffer();
            }
            else{
                printf(ANSI_RED "-------- ERROR -------- \n" ANSI_RESET);
                printf(ANSI_RED "Por favor ingresar números mayores a 0 \n" ANSI_RESET);
                printf(ANSI_bBLUE "Ingrese la cantidad de claves que quiere generar (0- Salir): " ANSI_RESET);
                validador = scanf("%d", &canta_claves);
                vaciar_buffer();
            }
        }

        if (canta_claves == 0){
            printf(ANSI_GREEN "\nHasta la próxima!" ANSI_RESET);
            printf(ANSI_GREEN "\nGracias por usar la app <3 !!" ANSI_RESET);
        }

        else{
            limpiar_pantalla();
            opc = menu_caracteres();

            for (int i = 0; i < canta_claves; i++)
            {
                printf("\n");
                Generar_clave(v, vC, utilf, utilc, opc);
                MostrarMatriz(vC, utilf, utilc);
                printf("\n");
            }
            printf(ANSI_RED " --------- ADVERTENCIA ---------\nAl darle al ENTER se BORRARAN las contraseñas generadas, asegúrate de ya haberlas COPIADO" ANSI_RESET);
            pausa();
            limpiar_pantalla();
            printf(ANSI_bBLUE "Ingrese la cantidad de calves que quiere generar (0- Salir): " ANSI_RESET);
            validador = scanf("%d", &canta_claves);
            vaciar_buffer();
        }
    }
    contador++;

    // Una vez finalmente ejecutado el programa (sumado a la variable contador +1 previamente) vuelvo
    // a abrir el archivo y guardo el numero modificado.
    archivo = fopen("contador.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%d", contador);
        fclose(archivo);
    }

    

    return 0;
}