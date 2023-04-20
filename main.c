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
    printf(ANSI_YELLOW"\npresiones ENTER para continuar...."ANSI_RESET);
    getchar();
}

void limpiar_pantalla(){
    printf("\033[2J\033[1;1H");
    return;
}

int menu_caracteres()
{
    // pido por teclado el nivel de seguridad de cada contraseña
    int opc=-1;
    while (opc != 0 && opc != 1 && opc != 2 && opc != 3)
    {
        printf(ANSI_CYAN"Seleccione el nivel de seguridad de la clave: \n");
        printf("\t\t1- Sencilla (Numerica)\n");
        printf("\t\t2- Intermedia (AlfaNumerica)\n");
        printf("\t\t3- Segura (AlfaNumerica + Caracteres especiales)\n\n");
        printf(ANSI_RED"\t\t\t0- Salir\n");

        printf(ANSI_YELLOW"opcion: "ANSI_RESET);
        scanf("%d", &opc);

        vaciar_buffer();
    }
    pausa();
    limpiar_pantalla();
    
    return opc;
}
int Cant_char_per_contra(){
    // pido por teclado la cantidad de caracteres que van a poseer las contraseñas
    int cant=0;
    printf(ANSI_CYAN"ingrese la cantidad de caracteres que desee que tenga la contraseña (maximo 100 caracteres): "ANSI_RESET);
    int validador = scanf("%d", &cant);
    vaciar_buffer();
    while((cant<=0 || cant>100) || validador != 1){
        printf(ANSI_RED"-------- ERROR -------- \n"ANSI_RESET);
        
        if(validador!=1){
            printf(ANSI_YELLOW"Por favor igrese un numero entero, letras o caracteres especiales no son admitidos "ANSI_RESET);

        }
        else{
            printf(ANSI_YELLOW"la cantidada de caracteres tiene que ser entre 0 y 100, porfavor ingrese nuevamente:  "ANSI_RESET);
             
        }
        validador = scanf("%d", &cant);
        vaciar_buffer();
    }
    
    printf(ANSI_CYAN"Cantidad de caracteres a generar: "ANSI_bGREEN"%d\n"ANSI_RESET,cant);
    
    
    return cant;
}
void cargarRandom(int v[], int util, int numRand)
{
    // cargo de manera random un vector con numeros en base a la cantidad
    // de distintos valores unitarios de caracteres
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < util; i++)
    {
        v[i] = rand() % numRand;
    }
}

void Generar_clave(int vNumeros[], char vChar[FILAS][COLUM], int utilf, int utilc,int opc)
{
    // defino los 3 posibles diccionarios de caracteres que se usaran en base al nivel de seguridad seleccionado
    int f, c, i;
    
    char AlfabetoNum[10][1] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char AlfabetoAlfaNum [36][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                    "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char Alfabeto[45][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                               "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                               "!", "&", "+", "*", "<", ">", ",", ".", "?"};
    if (opc == 0)
    {
        printf(ANSI_GREEN"Gracias por usar la app <3 !!"ANSI_RESET);
        return;
    }
    
    else{
        int cant = Cant_char_per_contra();
        if (opc == 1){
            cargarRandom(vNumeros, cant,10);
            for (f = 0; f < cant; f++){
                for (c = 0; c < utilc; c++){
                    vChar[f][c] = AlfabetoNum[vNumeros[f]][c];
                }
            }
            return;
        }
        if (opc == 2){
            cargarRandom(vNumeros, cant,36);
            for (f = 0; f < cant; f++){
                for (c = 0; c < utilc; c++){
                    vChar[f][c] = AlfabetoAlfaNum[vNumeros[f]][c];
                    if (vNumeros[f] >= 0 && vNumeros[f] <= 27){
                        i = rand() % 2 + 1;
                        if (i == 1){
                            vChar[f][c] = vChar[f][c] - 32;
                        }
                    }
                }
            }
        }

        if (opc == 3){
            cargarRandom(vNumeros, cant,45);
            for (f = 0; f < cant; f++){
                for (c = 0; c < utilc; c++){
                    vChar[f][c] = Alfabeto[vNumeros[f]][c];
                    if (vNumeros[f] >= 0 && vNumeros[f] <= 27){
                        i = rand() % 2 + 1;
                        if (i == 1){
                            vChar[f][c] = vChar[f][c] - 32;
                        }
                    }
                }
            }
        }
    }
}


void MostrarMatriz(char matriz[FILAS][COLUM], int utilf, int utilc)
{
    int f, c;
    printf(ANSI_GREEN"\nContraseña: "ANSI_RESET);
    for (f = 0; f < utilf; f++)
    {
        
        for (c = 0; c < utilc; c++)
        {
            printf(ANSI_bGREEN"%c"ANSI_RESET, matriz[f][c]);
        }
    }
    printf("\n");
    pausa();
}


int main()
{
    int v[FILAS] = {};
    char vC[FILAS][COLUM] = {};
    int canta_claves,opc;
    int utilf = FILAS, utilc = 1;

    limpiar_pantalla();

    printf(ANSI_bBLUE"Ingrese la cantidad de calves que quiere generar (0- Salir): "ANSI_RESET);
    int validador = scanf("%d", &canta_claves);
    vaciar_buffer();
    

    while(canta_claves<=0 || validador!=1){
        
        if(validador!=1){
            printf(ANSI_RED"-------- ERROR -------- \n"ANSI_RESET);
            printf(ANSI_RED"No se admiten letras ni otro tipo de caracteres \n"ANSI_RESET);
            printf(ANSI_bBLUE"Ingrese la cantidad de claves que quiere generar (0- Salir): "ANSI_RESET);
            validador = scanf("%d", &canta_claves);
            vaciar_buffer();
        }
        else{
            printf(ANSI_RED"-------- ERROR -------- \n"ANSI_RESET);
            printf(ANSI_RED"Por favor ingresar numeros mayores a 0 \n"ANSI_RESET);
            printf(ANSI_bBLUE"Ingrese la cantidad de claves que quiere generar (0- Salir): "ANSI_RESET);
            validador = scanf("%d", &canta_claves);
            vaciar_buffer();
        }
    }
    limpiar_pantalla();
    opc = menu_caracteres();
        
    for (int i = 0; i < canta_claves; i++){
        printf("\n");
        Generar_clave(v, vC, utilf, utilc,opc);
        MostrarMatriz(vC, utilf, utilc);
        printf("\n");
        
    }
    printf(ANSI_RED" --------- ADVERTENCIA ---------\nAl darle al ENTER se BORRARAN las contraseñas generadas, asegurate de ya haberlas COPIADO"ANSI_RESET);
    pausa();
    limpiar_pantalla();
    printf(ANSI_bBLUE"Ingrese la cantidad de calves que quiere generar (0- Salir): "ANSI_RESET);
    validador = scanf("%d", &canta_claves);
    vaciar_buffer();
    
    printf(ANSI_GREEN"Gracias por usar la app <3 !!"ANSI_RESET);

    return 0;

    
}