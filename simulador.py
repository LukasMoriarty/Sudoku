import time
import os

# Códigos de color ANSI para la terminal
RESET = "\033[0m"
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"

# Tablero inicial 4x4
board = [[0, 0, 0, 0], [0, 2, 0, 1], [4, 0, 2, 0], [0, 0, 1, 0]]


def print_board(bo, current=None, trying=None, status=""):
    """Dibuja el tablero en la terminal, limpiando la pantalla en cada frame."""
    os.system("clear" if os.name == "posix" else "cls")
    print(f"{CYAN}=== Simulador Interactivo: Backtracking 4x4 ==={RESET}\n")
    print(status + "\n")

    for i in range(len(bo)):
        if i % 2 == 0 and i != 0:
            print("- - - - - - - -")
        row_str = ""
        for j in range(len(bo[0])):
            if j % 2 == 0 and j != 0:
                row_str += "| "

            # Colorear la celda actual que se está evaluando
            if current == (i, j):
                if trying == 0:
                    row_str += f"{RED}X {RESET}"  # Retroceso (Backtrack)
                else:
                    row_str += f"{YELLOW}{trying} {RESET}"  # Probando un número
            elif bo[i][j] == 0:
                row_str += ". "
            else:
                row_str += f"{GREEN}{bo[i][j]} {RESET}"  # Número confirmado temporal o permanentemente
        print(row_str)
    print("\n")
    # Pausa para crear el efecto de animación (puedes ajustar la velocidad aquí)
    time.sleep(0.7)


def is_valid(bo, num, pos):
    """Comprueba si el número es válido en la fila, columna y caja 2x2."""
    # Revisar Fila
    for i in range(len(bo[0])):
        if bo[pos[0]][i] == num and pos[1] != i:
            return False
    # Revisar Columna
    for i in range(len(bo)):
        if bo[i][pos[1]] == num and pos[0] != i:
            return False
    # Revisar Caja 2x2
    box_x = pos[1] // 2
    box_y = pos[0] // 2
    for i in range(box_y * 2, box_y * 2 + 2):
        for j in range(box_x * 2, box_x * 2 + 2):
            if bo[i][j] == num and (i, j) != pos:
                return False
    return True


def find_empty(bo):
    """Busca la siguiente celda vacía (representada por 0)."""
    for i in range(len(bo)):
        for j in range(len(bo[0])):
            if bo[i][j] == 0:
                return (i, j)
    return None


def solve(bo):
    """Función recursiva de Backtracking."""
    find = find_empty(bo)
    if not find:
        print_board(bo, status=f"{GREEN}¡Sudoku Resuelto Exitosamente!{RESET}")
        return True
    else:
        row, col = find

    for i in range(1, 5):
        print_board(
            bo,
            current=(row, col),
            trying=i,
            status=f"Probando {i} en fila {row + 1}, columna {col + 1}...",
        )

        if is_valid(bo, i, (row, col)):
            bo[row][col] = i
            print_board(
                bo,
                current=(row, col),
                trying=i,
                status=f"{GREEN}Válido. Avanzando a la siguiente celda...{RESET}",
            )

            if solve(bo):
                return True

            # Si retorna False, significa que hubo un error más adelante. Borramos la celda actual.
            bo[row][col] = 0
            print_board(
                bo,
                current=(row, col),
                trying=0,
                status=f"{RED}Callejón sin salida. Retrocediendo (Backtrack) en fila {row + 1}, columna {col + 1}{RESET}",
            )

    return False


if __name__ == "__main__":
    print_board(
        board, status="Tablero Inicial. Presiona Enter para iniciar la simulación..."
    )
    input()
    solve(board)
