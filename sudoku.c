/*
	UNIVERSIDAD AUTONOMA DE BAJA CALIFORNIA - FACULTAD DE CIENCIAS QUIMICAS E INGENIERIAS

	ANALISIS DE ALGORITMOS

	PROYECTO: SUDOKU
	- Objetivo: completar un tablero de Sudoku respetando reglas de fila, columna y subcuadro.
	
	- Descripción:
		Dado un tablero de Sudoku (matriz de 9x9, con algunos números colocados en diferentes posiciones)
		asigna los números del 1 al 9 en las celdas vacías, de tal manera manera que
		cada renglón, columna y submatriz de 3x3 contenga exactamente 1 instancia de cada número.
		Deben existir al menos 4 tableros distintos para resolver, y
		los tableros no pueden contener más de 40 números al iniciar.
		Hacer corridas con 3 tableros distintos.

	- Integrantes:
	MANRIQUEZ GUERRERO RAMON - 2210376
	ZEPEDA AVILA LUIS CARLOS - 1298670
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void crearTablero(int tablero[9][9]);
void imprimirTablero(int tablero[9][9]);

int main()
{
	int tablero1[9][9], tablero2[9][9], tablero3[9][9], tablero4[9][9];
	crearTablero(tablero1);
	crearTablero(tablero2);
	crearTablero(tablero3);
	crearTablero(tablero4);

	tablero1[5][7] = 1;

	printf("\nTablero 1:\n");
	imprimirTablero(tablero1);

	/*
	printf("Tablero 2:\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", tablero2[i][j]);
		}
		printf("\n");
	}
	printf("Tablero 3:\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", tablero3[i][j]);
		}
		printf("\n");
	}
	printf("Tablero 4:\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", tablero4[i][j]);
		}
		printf("\n");
	}
	*/

	printf("\n");
	return 0;
}

void crearTablero(int tablero[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tablero[i][j] = 0;
		}
	}
}

void imprimirTablero(int tablero[9][9])
{
	for (int k = 0; k < 16; k++) printf("- ");
	printf("\n");
	for (int i = 0; i < 9; i++)
	{
		printf("|");
		for (int j = 0; j < 9; j++)
		{
			//printf(" %d ", tablero[i][j]);
			tablero[i][j] == 0 ? printf(" * ") : printf(" %d ", tablero[i][j]);;
			if (j == 2 || j == 5)
				printf("|");
		}
		printf("|");
		printf("\n");
		if (i == 2 || i == 5)
		{
			for (int k = 0; k < 16; k++) printf("- ");
			printf("\n");
		}
	}
	for (int k = 0; k < 16; k++) printf("- ");
	printf("\n");
}