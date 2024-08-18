#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILAS 100
#define MAX_COLUMNAS 100

typedef struct s_mapa {
    char **maps2;  // Matriz de caracteres para el mapa
    int height;    // Número de filas del mapa
    int width;     // Número de columnas del mapa
} t_mapa;

// Función para calcular el tamaño del mapa y leerlo
void leer_mapa(const char *mapa_str, t_mapa *mapa) {
    const char *ptr = mapa_str;
    char *linea;
    int fila = 0;

    // Contar el número de filas
    mapa->height = 0;
    while (*ptr) {
        if (*ptr == '\n') {
            mapa->height++;
        }
        ptr++;
    }
    mapa->height++; // Para la última línea sin '\n'

    // Contar el número de columnas (asumiendo que todas las filas tienen el mismo tamaño)
    ptr = mapa_str;
    mapa->width = 0;
    while (*ptr != '\n' && *ptr != '\0') {
        mapa->width++;
        ptr++;
    }

    // Reservar memoria para el mapa
    mapa->maps2 = (char **)malloc(mapa->height * sizeof(char *));
    for (int i = 0; i < mapa->height; i++) {
        mapa->maps2[i] = (char *)malloc((mapa->width + 1) * sizeof(char)); // +1 para el carácter nulo
    }

    // Leer el contenido del mapa
    ptr = mapa_str;
    for (int i = 0; i < mapa->height; i++) {
        linea = mapa->maps2[i];
        for (int j = 0; j < mapa->width; j++) {
            if (*ptr != '\0' && *ptr != '\n') {
                *linea++ = *ptr++;
            }
        }
        *linea = '\0'; // Terminar la cadena de caracteres
        if (*ptr == '\n') {
            ptr++; // Saltar el carácter de nueva línea
        }
    }
}

// Función para imprimir el mapa
void imprimir_mapa(const t_mapa *mapa) {
    for (int i = 0; i < mapa->height; i++) {
        printf("%s\n", mapa->maps2[i]);
    }
}

// Función para liberar la memoria del mapa
void liberar_mapa(t_mapa *mapa) {
    for (int i = 0; i < mapa->height; i++) {
        free(mapa->maps2[i]);
    }
    free(mapa->maps2);
}

int main() {
    t_mapa mapa;
    const char *mapa_str = 
        "111111111111\n"
        "100010010001\n"
        "1P00010C0001\n"
        "1C00C00CE001\n"
        "10000000C001\n"
        "111111111101\n";
    
    leer_mapa(mapa_str, &mapa);

    printf("Mapa:\n");
    imprimir_mapa(&mapa);

    liberar_mapa(&mapa);

    return 0;
}
