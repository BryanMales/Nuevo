#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

int validarAlfanumerico(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalnum(cadena[i])) {
            return 0;
        }
    }
    return 1;
}

int codigoUnico(int n, char codigos[][MAX_CODIGO], char *codigoNuevo, int posExcluir) {
    for (int i = 0; i < n; i++) {
        if (i != posExcluir && strcmp(codigos[i], codigoNuevo) == 0) {
            return 0;
        }
    }
    return 1;
}


int leerTiempoEnMinutos(void) {
    int tiempo;
    do {
        printf("Ingrese tiempo de fabricacion en minutos : ");
        scanf("%d", &tiempo);
        while(getchar() != '\n');
    } while (tiempo < 0);
    return tiempo;
}

void ingresarProductos(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                       int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                       char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
    do {
        printf("Ingrese la cantidad de productos (1 a %d): ", MAX_PRODUCTOS);
        scanf("%d", n);
        while(getchar() != '\n');
    } while (*n < 1 || *n > MAX_PRODUCTOS);

    for (int i = 0; i < *n; i++) {
        printf("\nProducto %d:\n", i + 1);

        do {
            printf("Ingrese el codigo alfanumerico del producto: ");
            fgets(codigos[i], MAX_CODIGO, stdin);
            codigos[i][strcspn(codigos[i], "\n")] = 0;
        } while (strlen(codigos[i]) == 0 || !validarAlfanumerico(codigos[i]) || !codigoUnico(*n, codigos, codigos[i], i));

        printf("Ingrese el nombre del producto: ");
        fgets(nombres[i], MAX_NOMBRE, stdin);
        nombres[i][strcspn(nombres[i], "\n")] = 0;

        tiempos[i] = leerTiempoEnMinutos();

        do {
            printf("Ingrese la cantidad demandada : ");
            scanf("%d", &demandas[i]);
            while(getchar() != '\n');
        } while (demandas[i] < 0);

        for (int j = 0; j < MAX_MATERIALES; j++) {
            printf("Ingrese nombre del material %d (o 'fin' para terminar): ", j + 1);
            fgets(materiales[i][j], MAX_NOMBRE, stdin);
            materiales[i][j][strcspn(materiales[i][j], "\n")] = 0;

            if (strcmp(materiales[i][j], "fin") == 0) {
                for (int k = j; k < MAX_MATERIALES; k++) {
                    materiales[i][k][0] = '\0';
                    cantidades[i][k] = 0;
                }
                break;
            }

            do {
                printf("Ingrese cantidad del material '%s' (1 a 50): ", materiales[i][j]);
                scanf("%d", &cantidades[i][j]);
                while(getchar() != '\n');
            } while (cantidades[i][j] < 1 || cantidades[i][j] > 50);
        }
    }
}

void fabricarProducto(int n, char codigos[MAX_PRODUCTOS][MAX_CODIGO], int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
    char codigo[MAX_CODIGO];
    int encontrado = -1;

    printf("Ingrese codigo del producto a fabricar: ");
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(codigos[i], codigo) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    int faltan = 0;
    printf("Materiales faltantes para fabricar:\n");
    for (int j = 0; j < MAX_MATERIALES; j++) {
        if (strlen(materiales[encontrado][j]) > 0) {
            if (cantidades[encontrado][j] <= 0) {
                printf(" - %s\n", materiales[encontrado][j]);
                faltan = 1;
            }
        }
    }

    if (faltan) {
        char opcion;
        printf("No hay materiales suficientes. Desea reabastecer? (s/n): ");
        scanf("%c", &opcion);
        while(getchar() != '\n');

        if (opcion == 's' || opcion == 'S') {
            for (int j = 0; j < MAX_MATERIALES; j++) {
                if (strlen(materiales[encontrado][j]) > 0) {
                    int reab;
                    printf("Ingrese cantidad a reabastecer para '%s': ", materiales[encontrado][j]);
                    scanf("%d", &reab);
                    while(getchar() != '\n');
                    if (reab > 0) cantidades[encontrado][j] += reab;
                }
            }
            printf("Reabastecimiento realizado.\n");
        } else {
            printf("Fabricacion cancelada.\n");
            return;
        }
    }

    for (int j = 0; j < MAX_MATERIALES; j++) {
        if (strlen(materiales[encontrado][j]) > 0) {
            cantidades[encontrado][j]--;
        }
    }
    printf("Producto fabricado exitosamente.\n");
}

void mostrarProductos(int n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                      int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
    printf("\n%-20s %-15s %-10s %-10s %-40s\n", "Nombre", "Codigo", "Tiempo(min)", "Demanda", "Materiales (cantidad)");
    for (int i = 0; i < n; i++) {
        printf("%-20s %-15s %-10d %-10d ", nombres[i], codigos[i], tiempos[i], demandas[i]);
        for (int j = 0; j < MAX_MATERIALES; j++) {
            if (strlen(materiales[i][j]) > 0)
                printf("%s(%d) ", materiales[i][j], cantidades[i][j]);
        }
        printf("\n");
    }
}

void editarProducto(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                    int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                    char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
    char codigoBuscar[MAX_CODIGO];
    int encontrado = -1;

    printf("Ingrese codigo del producto a editar: ");
    fgets(codigoBuscar, MAX_CODIGO, stdin);
    codigoBuscar[strcspn(codigoBuscar, "\n")] = 0;

    for (int i = 0; i < *n; i++) {
        if (strcmp(codigos[i], codigoBuscar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Editando producto %s\n", codigos[encontrado]);

    do {
        printf("Ingrese nuevo codigo alfanumerico: ");
        fgets(codigos[encontrado], MAX_CODIGO, stdin

);
codigos[encontrado][strcspn(codigos[encontrado], "\n")] = 0;
} while (strlen(codigos[encontrado]) == 0 || !validarAlfanumerico(codigos[encontrado]) || !codigoUnico(*n, codigos, codigos[encontrado], encontrado));

printf("Ingrese nuevo nombre: ");
fgets(nombres[encontrado], MAX_NOMBRE, stdin);
nombres[encontrado][strcspn(nombres[encontrado], "\n")] = 0;

tiempos[encontrado] = leerTiempoEnMinutos();

do {
    printf("Ingrese nueva demanda (>=0): ");
    scanf("%d", &demandas[encontrado]);
    while(getchar() != '\n');
} while (demandas[encontrado] < 0);

for (int j = 0; j < MAX_MATERIALES; j++) {
    printf("Ingrese nuevo nombre del material %d (o 'fin' para terminar): ", j + 1);
    fgets(materiales[encontrado][j], MAX_NOMBRE, stdin);
    materiales[encontrado][j][strcspn(materiales[encontrado][j], "\n")] = 0;

    if (strcmp(materiales[encontrado][j], "fin") == 0) {
        for (int k = j; k < MAX_MATERIALES; k++) {
            materiales[encontrado][k][0] = '\0';
            cantidades[encontrado][k] = 0;
        }
        break;
    }

    do {
        printf("Ingrese cantidad del material '%s' (1 a 50): ", materiales[encontrado][j]);
        scanf("%d", &cantidades[encontrado][j]);
        while(getchar() != '\n');
    } while (cantidades[encontrado][j] < 1 || cantidades[encontrado][j] > 50);
}

printf("Producto editado correctamente.\n");
}

void eliminarProducto(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
char codigoEliminar[MAX_CODIGO];
int posEliminar = -1;

printf("Ingrese codigo del producto a eliminar: ");
fgets(codigoEliminar, MAX_CODIGO, stdin);
codigoEliminar[strcspn(codigoEliminar, "\n")] = 0;

for (int i = 0; i < *n; i++) {
    if (strcmp(codigos[i], codigoEliminar) == 0) {
        posEliminar = i;
        break;
    }
}

if (posEliminar == -1) {
    printf("Producto no encontrado.\n");
    return;
}

for (int i = posEliminar; i < *n - 1; i++) {
    strcpy(nombres[i], nombres[i+1]);
    strcpy(codigos[i], codigos[i+1]);
    tiempos[i] = tiempos[i+1];
    demandas[i] = demandas[i+1];

    for (int j = 0; j < MAX_MATERIALES; j++) {
        strcpy(materiales[i][j], materiales[i+1][j]);
        cantidades[i][j] = cantidades[i+1][j];
    }
}
(*n)--;
printf("Producto eliminado correctamente.\n");
}

void calcularTotalesYVerificarDemanda(int n, int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE],
int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]) {
int tiempoTotal = 0;
int faltanMateriales = 0;
char materialesFaltantes[MAX_PRODUCTOS * MAX_MATERIALES][MAX_NOMBRE];
int idxFaltantes = 0;

for (int i = 0; i < n; i++) {
    tiempoTotal += tiempos[i] * demandas[i];
}

printf("\nTiempo total necesario para fabricar toda la demanda: %d minutos\n", tiempoTotal);

for (int i = 0; i < n; i++) {
    for (int j = 0; j < MAX_MATERIALES; j++) {
        if (strlen(materiales[i][j]) > 0) {
            int totalNecesario = demandas[i] * cantidades[i][j];
            if (totalNecesario > cantidades[i][j]) { 

                if (totalNecesario > cantidades[i][j]) {
                    int repetido = 0;
                    for (int k = 0; k < idxFaltantes; k++) {
                        if (strcmp(materialesFaltantes[k], materiales[i][j]) == 0) {
                            repetido = 1;
                            break;
                        }
                    }
                    if (!repetido) {
                        strcpy(materialesFaltantes[idxFaltantes], materiales[i][j]);
                        idxFaltantes++;
                    }
                    faltanMateriales = 1;
                }
            }
        }
    }
}

if (faltanMateriales) {
    printf("No se puede cubrir la demanda por falta de materiales:\n");
    for (int i = 0; i < idxFaltantes; i++) {
        printf(" - %s\n", materialesFaltantes[i]);
    }
} else {
    printf("Hay suficientes materiales para cubrir la demanda.\n");
}
}