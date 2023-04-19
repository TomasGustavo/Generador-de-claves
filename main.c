#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define FILAS 45
#define COLUM 1

int vaciar_buffer(void)
{
    char nada[200];
    fgets(nada, 200, stdin);
    return 0;
}

void pausa()
{
    printf("presiones ENTER para continuar....");
    getchar();
}


int menu_caracteres()
{
    // pido por teclado el nivel de seguridad de cada contraseña
    int opc=-1;
    while (opc != 0 && opc != 1 && opc != 2 && opc != 3)
    {
        printf("seleccione el nivel de seguridad de la clave: \n");
        printf("1- Sencilla (Numerica)\n");
        printf("2- Intermedia (AlfaNumerica)\n");
        printf("3- Segura (AlfaNumerica + Caracteres espaciales)\n\n");
        printf("0- Salir\n");

        printf("opcion: ");
        scanf("%d", &opc);

        vaciar_buffer();
    }
    return opc;
}
int Cant_char_per_contra(){
    // pido por teclado la cantidad de caracteres que van a poseer las contraseñas
    int cant;
    printf("ingrese la cantidad de caracteres que desee que tenga la contraseña: \n");
    scanf("%d", &cant);
    vaciar_buffer();
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
    int cant = Cant_char_per_contra();
    char AlfabetoNum[10][1] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char AlfabetoAlfaNum [36][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                    "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    char Alfabeto[45][1] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                               "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                               "!", "&", "+", "*", "<", ">", ",", ".", "?"};
    if (opc == 0)
    {
        printf("Gracias por usar la app  =)");
        return;
    }
    else{
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

void mostrar(int v[], int util)
{
    int i;
    for (i = 0; i < util; i++)
    {
        printf("%i\t", v[i]);
    }
}
void MostrarMatriz(char matriz[FILAS][COLUM], int utilf, int utilc)
{
    int f, c;
    for (f = 0; f < utilf; f++)
    {
        
        for (c = 0; c < utilc; c++)
        {
            printf("%c", matriz[f][c]);
        }
    }
    printf("\n");
}


int main()
{
    int v[FILAS] = {};
    char vC[FILAS][COLUM] = {};
    int canta_claves,opc;
    int utilf = FILAS, utilc = 1;
    int util = FILAS;

    printf("Ingrese la cantidad de calves que quiere generar: ");
    scanf("%d", &canta_claves);
    vaciar_buffer();
    opc = menu_caracteres();

    for (int i = 0; i < canta_claves; i++)
    {
        printf("\n");
        Generar_clave(v, vC, utilf, utilc,opc);
        MostrarMatriz(vC, utilf, utilc);
        printf("\n");
        _sleep(1000);
    }
}