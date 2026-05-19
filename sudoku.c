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

void imprimirTablero(int tablero[9][9]);
int resolver(int tablero[9][9], int pos_fila, int pos_col);
int revisar(int tablero[9][9], int num, int x, int y);

int main()
{
  int sudokus[4][9][9] = {
    {   // Tablero 1 
      {0, 0, 0, 3, 0, 5, 1, 8, 0},
      {0, 0, 0, 1, 8, 0, 5, 0, 0},
      {0, 1, 8, 0, 0, 4, 0, 0, 6},
      {6, 9, 0, 5, 0, 0, 0, 0, 1},
      {2, 0, 1, 8, 0, 9, 0, 0, 0},
      {0, 3, 0, 0, 0, 2, 0, 6, 5},
      {3, 0, 0, 9, 0, 0, 6, 0, 0},
      {1, 0, 5, 0, 0, 0, 3, 9, 0},
      {0, 6, 9, 0, 5, 0, 0, 1, 8}      
    },
    {   // Tablero 2
      {0, 0, 9, 0, 4, 6, 7, 0, 5},
      {7, 0, 0, 0, 1, 0, 3, 0, 0},
      {3, 6, 8, 0, 9, 5, 0, 0, 0},
      {4, 0, 0, 8, 0, 7, 0, 0, 2},
      {0, 1, 7, 0, 0, 0, 8, 0, 9},
      {5, 0, 0, 1, 3, 0, 0, 0, 0},
      {0, 0, 1, 5, 0, 4, 9, 0, 0},
      {0, 3, 5, 0, 0, 1, 0, 4, 0},
      {8, 0, 0, 9, 2, 0, 5, 0, 7}
    },
    {   // Tablero 3
      {0, 0, 9, 0, 4, 0, 7, 0, 5},
      {0, 5, 4, 0, 1, 0, 0, 0, 0},
      {3, 0, 0, 7, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 7, 1, 0, 2},
      {6, 0, 7, 0, 5, 0, 8, 0, 0},
      {5, 8, 0, 0, 0, 0, 6, 0, 0},
      {0, 0, 0, 5, 8, 0, 0, 6, 0},
      {0, 0, 5, 6, 0, 0, 0, 4, 8},
      {8, 4, 0, 0, 0, 0, 0, 1, 0}
    },
    {   // Tablero 4 
      {0, 0, 9, 0, 4, 0, 7, 0, 0},
      {0, 5, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 5, 0, 0, 1},
      {4, 0, 0, 8, 0, 0, 0, 0, 0},
      {6, 0, 7, 0, 0, 0, 8, 0, 0},
      {0, 0, 0, 1, 3, 0, 0, 7, 0},
      {0, 7, 0, 0, 0, 0, 0, 0, 0},
      {9, 0, 0, 0, 0, 1, 0, 4, 0},
      {0, 4, 0, 0, 0, 0, 5, 0, 7}
    }
  };

  printf("\nTableros:\n");
  for(int i = 0; i < 4; i++)
    imprimirTablero(sudokus[i]);
	printf("=====================================\n");

	printf("\n");
  for(int i = 0; i < 4; i++) {
    if (resolver(sudokus[i], 0, 0) == 1) {
      printf("\nSolucion del Tablero %d:\n", i + 1);
      imprimirTablero(sudokus[i]);
    } else {
      printf("\nNo se encontro solucion para el Tablero %d\n", i + 1);
    }
  }
	return 0;
}

void imprimirTablero(int tablero[9][9])
{
	printf("=====================================\n");
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

/*
 * Esta funcion se encargará de resolver el sudoku
 */

int resolver(int tablero[9][9], int fila, int col) {
  // si llegamos a la fila 9 (no existe) entonces terminamos
  if(fila == 9)
    return 1;
  
  // si ya terminamos las columnas entonces cambiamos 
  // de fila y reiniciamos el contador de columnas
  if(col == 9)
    return resolver(tablero, fila + 1, 0);

  // si la casilla actual tiene un numero avanzamos a la siguiente
  if(tablero[fila][col] != 0)
    return resolver(tablero, fila, col + 1);

  for (int num = 1; num <= 9; num++) {
    if (revisar(tablero, num, fila, col)) {
      tablero[fila][col] = num;

      if (resolver(tablero, fila, col + 1) == 1)
        return 1;
      
      // si la llamada anterior retorna 0
      // entonces fue que no pudo encontrar un valor valido
      // se vacía la casilla y seguimos probando números
      tablero[fila][col] = 0;
    }
  }
  // caso: ningun numero se pudo poner
  return 0;
}

/*
 * Esta funcion se encargará de verificar si el número se
 * puede colocar
 */

int revisar(int tablero[9][9], int num, int fila, int col) {
  // Revisar fila 
  for(int i = 0; i < 9; i++) {
    if(tablero[fila][i] == num)
      return 0;
  }
  
  // Revisar columna 
  for(int i = 0; i < 9; i++) {
    if(tablero[i][col] == num)
      return 0;
  }

  // Revisar la caja
  int inicioFila = (fila / 3) * 3;
  int inicioCol = (col / 3) * 3;

  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if (tablero[inicioFila + i][inicioCol + j] == num) 
        return 0;
    }
  }
  
  // Pasó todas las comprobaciones
  return 1;
}

