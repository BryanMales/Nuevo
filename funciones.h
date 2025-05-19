#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 5
#define MAX_MATERIALES 5
#define MAX_NOMBRE 100
#define MAX_CODIGO 20

void ingresarProductos(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                       int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                       char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

void fabricarProducto(int n, char codigos[MAX_PRODUCTOS][MAX_CODIGO], int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

void mostrarProductos(int n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                      int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

void editarProducto(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                    int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                    char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

void eliminarProducto(int *n, char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char codigos[MAX_PRODUCTOS][MAX_CODIGO],
                      int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE], int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

void calcularTotalesYVerificarDemanda(int n, int tiempos[MAX_PRODUCTOS], int demandas[MAX_PRODUCTOS],
                                      char materiales[MAX_PRODUCTOS][MAX_MATERIALES][MAX_NOMBRE],
                                      int cantidades[MAX_PRODUCTOS][MAX_MATERIALES]);

int leerTiempoEnMinutos(void);

#endif
