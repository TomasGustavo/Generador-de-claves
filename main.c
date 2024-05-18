#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "Headers.h"
#include <stdbool.h>
#define FILAS 101
#define COLUM 1

/// @brief crea un archivo binario, si esta creado indica que existe ya uno, sino lo crea
void crear_archivo_binario()
{
    FILE *archivo = fopen("claves.dat", "rb");
    
    if (archivo == NULL) {
        archivo = fopen("claves.dat", "wb");
        
        if (archivo == NULL) {
            printf("No se pudo crear el archivo.\n");
            fclose(archivo);
            return;
        }
        else{
            printf("Archivo creado exitosamente.\n");
            fclose(archivo);    
            return;
        }
    } 
    else {
        printf("El archivo ya existe.\n");
        fclose(archivo);
        return;
    }
}


/// @brief copia el contenido de la matriz con claves en la estructura.
/// @param matrizOriginal matriz con los caracteres a copiar
/// @param contra estructura donde serán copiados los datos
/// @param filas cantidad de filas de la matriz
/// @param columnas cantidad de columnas de la matriz
void copiarMatriz(char matrizOriginal[FILAS][COLUM], clave contra, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            contra->contrasenia[i][j] = matrizOriginal[i][j];
        }
    }
}

void menu(int n){

    printf("\n");
    printf(ANSI_BLUE "  ============================================================================\n");
    printf(" |                           Generador de claves v0.%d                        |\n",n);
    printf("  ============================================================================\n");
    printf("\n");
    printf("  1   Generar nuevas claves\n");
    printf("  2   Mostrar claves guardadas\n");
    printf("  3   Modificar nombre de clave\n");
    printf("  4   Eliminar clave guardada\n");
    printf("\n");
    printf(ANSI_bRED"  0   Salir\n"ANSI_BLUE);
    printf("\n");
    printf(" ------------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Por favor seleccione una opción: " ANSI_YELLOW);

}

void main_modificar(){
    FILE *archivo = fopen("claves.dat", "r+b");
    clave contra = (clave) malloc(sizeof(struct claveRep));
    char nom[FILAS];
    int i=0;
    mostrar_lista_contra();
    printf(ANSI_BLUE"Indique el nombre de la clave que quiere modificar: "ANSI_bYELLOW);    
    fgets(nom,FILAS,stdin);
    nom[strcspn(nom, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    fseek(archivo, 0, SEEK_SET);
    fread(contra,sizeof(struct claveRep),1,archivo);
    while(!feof(archivo)){
        if(strcmp(contra->nombre,nom)==0){
            i++;
            printf(ANSI_BLUE"Indique nuevo nombre para la clave: "ANSI_bYELLOW);    
            fgets(nom,FILAS,stdin);
            nom[strcspn(nom, "\n")] = '\0'; // Eliminar el carácter de nueva línea
            fseek(archivo, -((long)sizeof(struct claveRep)), SEEK_CUR);
            strcpy(contra->nombre,nom);
            fwrite(contra, sizeof(struct claveRep), 1, archivo);
            printf(ANSI_bGREEN"\n\tNombre cambiado con éxito!");
            pausa();
            break;
        }
        fread(contra,sizeof(struct claveRep),1,archivo);
    }
    if(i!=1){
        printf(ANSI_bRED"\n\tNo existe ninguna clave con ese nombre!\n"ANSI_RESET);
        pausa();
    }

    fclose(archivo);
}

void main_eliminar(){
    FILE *archivo = fopen("claves.dat", "r+b");
    clave contra = (clave) malloc(sizeof(struct claveRep));
    char nom[20];
    int i=0;
    mostrar_lista_contra();
    printf(ANSI_BLUE"Indique el nombre de la clave que quiere eliminar: "ANSI_bYELLOW);
    fgets(nom,20,stdin);
    nom[strcspn(nom, "\n")] = '\0'; // Eliminar el carácter de nueva línea

    fseek(archivo, 0, SEEK_SET);
    fread(contra,sizeof(struct claveRep),1,archivo);
    while(!feof(archivo)){
        if(strcmp(contra->nombre,nom)==0){
            i++;
            fseek(archivo, -((long)sizeof(struct claveRep)), SEEK_CUR);
            contra->estado = false;
            fwrite(contra, sizeof(struct claveRep), 1, archivo);
            printf(ANSI_bGREEN"\n\tBaja lógica exitosa!\n"ANSI_RESET);
            pausa();
            break;
        }
        fread(contra,sizeof(struct claveRep),1,archivo);
    }
    if(i!=1){
        printf(ANSI_bRED"\n\tNo existe ninguna clave con ese nombre!\n"ANSI_RESET);
        pausa();
    }

    fclose(archivo);
}

void menu_guardar(){
    printf("\n");
    printf(ANSI_BLUE "  ============================================================================\n");
    printf(" |                                 Guardado de claves                                |\n");
    printf("  ============================================================================\n");
    printf("\n");
    printf("  1   Guardar nueva clave\n");
    printf("\n");
    printf("  0   No guardar (Salir)\n");
    printf("\n");
    printf(" ------------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Por favor seleccione una opción: " ANSI_YELLOW);
}

/// @brief guarda la estructura de datos con la contraseña y el nombre dado en un archivo binario
/// @param vC matriz con la contraseña generada
void main_menu_guardar(char vC[FILAS][COLUM]){
   
    clave contra = (clave) malloc(sizeof(struct claveRep));

    menu_guardar();

    int opc;
    int validador = scanf("%d",&opc);
    vaciar_buffer();
    while(validador!=1 || opc != 1 && opc != 0 ){
        printf(ANSI_bRED"Dato incorrecto, por favor seleccionar una de las opciones [1 - 0]: ");
        validador = scanf("%d",&opc);
        vaciar_buffer();
        limpiar_pantalla();
    }

    if(opc == 1){
        FILE *archivo = fopen("claves.dat", "r+b");

        copiarMatriz(vC,contra,FILAS,COLUM);
        printf(ANSI_GREEN "Ingrese Nombre que le asignara a la contraseña: " ANSI_YELLOW);
        fgets(contra->nombre, FILAS, stdin);
        contra->nombre[strcspn(contra->nombre, "\n")] = '\0'; // Eliminar el carácter de nueva línea
        contra->estado = true;
        fseek(archivo, 0, SEEK_END);
        fwrite(contra, sizeof(struct claveRep), 1, archivo);
        
        fclose(archivo);
        printf(ANSI_bGREEN"\n\tContraseña guardada con éxito!\n");
    }
    else{
        printf(ANSI_bMAGENTA"La contraseña no fue guardada!");
    }
}


/// @brief toma la cantidad de claves a generar y llama a las funciones que que la generan y guardan.
void menu_generar_claves(){
    int v[FILAS] = {};
    char vC[FILAS][COLUM] = {};
    int canta_claves=-1, opc;
    int utilf = FILAS, utilc = 1;

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

        if (canta_claves != 0){
            limpiar_pantalla();
            opc = menu_caracteres();

            for (int i = 0; i < canta_claves; i++)
            {
                printf("\n");
                Generar_clave(v, vC, utilf, utilc, opc);
                MostrarMatriz(vC, utilf, utilc);
                printf("\n");
                main_menu_guardar(vC);
                pausa();
                limpiar_pantalla();
            }
            limpiar_pantalla();
        }
    }
}

/// @brief limpia el buffer del teclado
int vaciar_buffer(void)
{
    char nada[200];
    fgets(nada, 200, stdin);
    return 0;
}


/// @brief una pausa para que el usuario vea lo que se imprimio
void pausa()
{
    printf(ANSI_YELLOW "\npresione ENTER para continuar...." ANSI_RESET);
    getchar();
}

/// @brief borra lo que haya impreso en la pantalla
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

/// @brief toma que tipo de seguridad va a tener la contraseña
/// @return retorna la opción seleccionada
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


/// @brief muestra el contenido del archivo con las claves y nombres.
void mostrar_lista_contra(){
    FILE *archivo = fopen("claves.dat","r+b");
    clave contra = (clave)malloc(sizeof(struct claveRep));

    // corrobora que el archivo este vacio
    fseek(archivo,0,SEEK_END);
    long file_long = ftell(archivo);

    if(file_long == 0){
        printf(ANSI_RED "\nNo hay ninguna clave guardada\n");
    } else{
        printf(ANSI_bCYAN "\nCONTENIDO ALMACENADO EN claves.dat\n");
        fseek(archivo, 0, SEEK_SET);
        fread(contra, sizeof(struct claveRep), 1, archivo);
        while(!feof(archivo)){
            if(contra->estado == true){
                printf(ANSI_bYELLOW "\n%s: " ANSI_GREEN "%s\t \n",contra->nombre,contra->contrasenia);
            }
            fread(contra, sizeof(struct claveRep), 1, archivo);
        }
    }
    pausa();
    fclose(archivo);
}

/// @brief funcion principal que llama al menú principal y a las funciones para generar las claves
/// @param contador variable que indica que versión del programa es
void inicio(int contador){
    int x;
    menu(contador);
    int validador = scanf("%d",&x);
    vaciar_buffer();
    while(validador!=1 || (x != 1 && x != 0 && x!=2 && x!=3 && x!=4)){
        printf(ANSI_bRED"----- ERROR -----: ");
        menu(contador);
        validador = scanf("%d",&x);
        vaciar_buffer();
        limpiar_pantalla();
    }
    switch (x){
    case 1:
        menu_generar_claves();
        limpiar_pantalla();
        inicio(contador);
        break;
    case 2:
        mostrar_lista_contra();
        limpiar_pantalla();
        inicio(contador);
        break;
    case 3:
        main_modificar();
        limpiar_pantalla();
        inicio(contador);
        break;
    case 4:
        main_eliminar();
        limpiar_pantalla();
        inicio(contador);
        break;

    case 0:
        printf(ANSI_GREEN "\nHasta la próxima!" ANSI_RESET);
        printf(ANSI_GREEN "\nGracias por usar la app <3 !!" ANSI_RESET);
        break;
    default:
        break;
    }
    
}
// hacer función para para que pueda guardar las claves generadas con nombre en un archivo y opción para mostrarlas en vez de generarlas.

int main(){
    crear_archivo_binario();
    int contador=000;

    limpiar_pantalla();
    
    // Guardo en la variable contador el numero que hay y cierro el archivo.
    FILE *archivo = fopen("contador.txt", "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d", &contador);
        fclose(archivo);
    }

    inicio(contador);
    
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