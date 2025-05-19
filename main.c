#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 5
#define MAX_MATERIALES 5
#define MAX_NOMBRE 50
#define MAX_CODIGO 20

int validarAlfanumerico(char str[]);
int codigoUnico(int n, char codigos[MAX_PRODUCTOS][MAX_CODIGO], char nuevoCodigo[], int editarIndex);
void ingresarProductos(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                       int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                       char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);
void mostrarProductos(int n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                      int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);
void editarProducto(int n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                    int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                    char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);
void eliminarProducto(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                      int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);
void calcularTotalesYVerificarDemanda(int n, int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE],
                                      int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE] = {0};
    char codigos[MAX_PRODUCTOS][MAX_CODIGO] = {0};
    int tiempos[MAX_PRODUCTOS] = {0};
    int demandas[MAX_PRODUCTOS] = {0};
    char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE] = {{{0}}};
    int cantidades[MAX_PRODUCTOS][MAX_MATERIALES] = {{0}};
    int n = 0;

    int opcion;

    do {
        printf("\n--- Menu Gestion de Productos ---\n");
        printf("1. Ingresar productos\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular tiempo total y verificar demanda\n");
        printf("0. Salir\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');

        switch (opcion) {
            case 1:
                ingresarProductos(&n, nombres, codigos, tiempos, demandas, materiales, cantidades);
                break;
            case 2:
                mostrarProductos(n, nombres, codigos, tiempos, demandas, materiales, cantidades);
                break;
            case 3:
                editarProducto(n, nombres, codigos, tiempos, demandas, materiales, cantidades);
                break;
            case 4:
                eliminarProducto(&n, nombres, codigos, tiempos, demandas, materiales, cantidades);
                break;
            case 5:
                calcularTotalesYVerificarDemanda(n, tiempos, demandas, materiales, cantidades);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
