#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

//declaracion de funciones
void mostrarMenu();
void iniciarJuego();
void crearTablero(char tablero[12][12]);
void mostrarTablero(char tablero[12][12]);
void colocarBarcosaleatoriamente(char tablero[12][12]);
void colocarBarco(char tablero[12][12], int tamaño, char simbolo);
void iniciarPartida(char tablero[12][12]);
void obtenerdisparo(int *fila, int *columna);
void procesarDisparo(char tablero[12][12], int fila, int columna);
void finJuego(char tablero[12][12]);

int main(){
    mostrarMenu();
    return 0;
}

//definicion de funciones
void mostrarMenu() {
    int opcion;
    do {
        printf("=== Menu de Hundir la Flota ===\n");
        printf("1. Iniciar Juego\n");
        printf("2. ver mejores puntajes\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                iniciarJuego();
                break;
            case 2:
                printf("Mostrando mejores puntajes...\n");
                break;
            case 3:2
                printf("Saliendo del juego. ¡Hasta luego!\n");
                break;
            default:
                printf("Opcion invalida. Por favor, intente de nuevo.\n");
        }
    } while (opcion != 3);
}

void iniciarJuego() {
    char jugador[12][12];
    char enemigo[12][12];
    crearTablero(jugador);
    crearTablero(enemigo);
    colocarBarcosaleatoriamente(jugador);
    colocarBarcosaleatoriamente(enemigo);
    printf("Tablero del jugador.\n");
    mostrarTablero(jugador);
    printf("Tablero del enemigo.\n");
    mostrarTablero(enemigo);
    iniciarPartida(enemigo);

}

void crearTablero(char tablero[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            tablero[i][j] = '~'; // Agua
        }
    }
}

void mostrarTablero(char tablero[12][12]) {
    printf("  ");
    for (int j = 0; j < 12; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < 12; i++) {
        printf("%d ", i);
        for (int j = 0; j < 12; j++) {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

void colocarBarcosaleatoriamente(char tablero[12][12]) {
    srand(time(NULL));
    colocarBarco(tablero, 4, 'P'); // Portaaviones
    colocarBarco(tablero, 3, 'C'); // crucero
    colocarBarco(tablero, 3, 'C'); // segundo crucero
    colocarBarco(tablero, 2, 'T'); // patrullero
    colocarBarco(tablero, 2, 'T'); // segundo patrullero
    colocarBarco(tablero, 2, 'T'); // tercer patrullero
}

void colocarBarco(char tablero[12][12], int tamaño, char simbolo) {
    int fila, columna, direccion, colocado = 0;
    while (!colocado) {
        fila = rand() % 12;
        columna = rand() % 12;
        direccion = rand() % 2; // 0: horizontal, 1: vertical

        int puedeColocar = 1;
        for (int i = 0; i < tamaño; i++) {
            int f = fila + (direccion == 1 ? i : 0);
            int c = columna + (direccion == 0 ? i : 0);
            if (f >= 12 || c >= 12 || tablero[f][c] != '~') {
                puedeColocar = 0;
                break;
            }
        }

        if (puedeColocar) {
            for (int i = 0; i < tamaño; i++) {
                int f = fila + (direccion == 1 ? i : 0);
                int c = columna + (direccion == 0 ? i : 0);
                tablero[f][c] = simbolo;
            }
            colocado = 1;
        }
    }
}

void iniciarPartida(char tablero[12][12]) {
    int fila, columna;
    while (1) {
        obtenerdisparo(&fila, &columna);
        procesarDisparo(tablero, fila, columna);
        finJuego(tablero);
    }
}

void obtenerdisparo(int *fila, int *columna) {
    printf("Ingrese la fila y columna para disparar (separados por espacio): ");
    scanf("%d %d", fila, columna);
}

void procesarDisparo(char tablero[12][12], int fila, int columna) {
    if (tablero[fila][columna] == '~') {
        printf("Agua!\n");
        tablero[fila][columna] = 'O'; // Marca de agua
    } else if (tablero[fila][columna] == 'O' || tablero[fila][columna] == 'X') {
        printf("Ya has disparado aqui. Intenta de nuevo.\n");
    } else {
        printf("¡Tocado!\n");
        tablero[fila][columna] = 'X'; // Marca de barco tocado
    }
}

void finJuego(char tablero[12][12]) {
    int barcosRestantes = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (tablero[i][j] != '~' && tablero[i][j] != 'O' && tablero[i][j] != 'X') {
                barcosRestantes++;
            }
        }
    }
    if (barcosRestantes == 0) {
        printf("¡Felicidades! Has hundido todos los barcos enemigos.\n");
        exit(0);
    }
}