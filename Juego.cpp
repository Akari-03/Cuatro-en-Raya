#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Estructura para almacenar los datos de los jugadores
struct Jugador {
    string nombre;
    int puntaje;
};

const int FILAS = 6;
const int COLUMNAS = 7;

// Función para inicializar el tablero
void inicializarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero[i][j] = '-';
        }
    }
}

// Función para mostrar el tablero
void mostrarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para verificar si hay un ganador
char hayGanador(char tablero[FILAS][COLUMNAS], char jugador) {
    // Verificar horizontalmente
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == jugador && tablero[i][j + 1] == jugador && tablero[i][j + 2] == jugador && tablero[i][j + 3] == jugador) {
                return jugador;
            }
        }
    }

    // Verificar verticalmente
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero[i][j] == jugador && tablero[i + 1][j] == jugador && tablero[i + 2][j] == jugador && tablero[i + 3][j] == jugador) {
                return jugador;
            }
        }
    }

    // Verificar diagonalmente (de izquierda a derecha)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == jugador && tablero[i + 1][j + 1] == jugador && tablero[i + 2][j + 2] == jugador && tablero[i + 3][j + 3] == jugador) {
                return jugador;
            }
        }
    }

    // Verificar diagonalmente (de derecha a izquierda)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 3; j < COLUMNAS; ++j) {
            if (tablero[i][j] == jugador && tablero[i + 1][j - 1] == jugador && tablero[i + 2][j - 2] == jugador && tablero[i + 3][j - 3] == jugador) {
                return jugador;
            }
        }
    }

    return '-'; // No hay ganador
}

// Función para colocar una ficha en una columna
char colocarFicha(char tablero[FILAS][COLUMNAS], int columna, char jugador) {
    // Verificar si la columna está llena
    if (tablero[0][columna] != '-') {
        return '-'; // Columna llena
    }

    // Encontrar la fila donde colocar la ficha
    int fila = FILAS - 1;
    while (fila >= 0 && tablero[fila][columna] != '-') {
        fila--;
    }

    // Colocar la ficha en la fila encontrada
    tablero[fila][columna] = jugador;

    // Devolver el jugador que ha colocado la ficha
    return jugador;
}

// Función para mostrar los puntajes de los jugadores
void mostrarPuntajes(Jugador jugadores[], int numJugadores) {
    cout << "Puntajes de los jugadores:" << endl;
    for (int i = 0; i < numJugadores; ++i) {
        cout << jugadores[i].nombre << ": " << jugadores[i].puntaje << " puntos" << endl;
    }
}

// Función para jugar al Cuatro en Raya
void jugar(Jugador jugadores[], int numJugadores) {
    char tablero[FILAS][COLUMNAS];
    inicializarTablero(tablero);

    int turno = 0;
    char ganador = '-';
    bool finJuego = false;

    while (!finJuego) {
        mostrarTablero(tablero);
        int columna;
        cout << "Turno del jugador " << jugadores[turno].nombre << endl;
        cout << "Ingrese el numero de columna (1-" << COLUMNAS << "): ";
        cin >> columna;

        // Ajustar el índice de la columna para que comience desde 0
        columna--;

        char resultado = colocarFicha(tablero, columna, turno == 0 ? 'X' : 'O');
        if (resultado == '-') {
            cout << "Columna llena. Intente nuevamente." << endl;
        } else {
            ganador = hayGanador(tablero, turno == 0 ? 'X' : 'O');
            if (ganador != '-') {
                cout << "El jugador " << jugadores[turno].nombre << " ha ganado!" << endl;
                if (ganador == 'X') {
                    jugadores[0].puntaje += 3; // Gana el jugador 1
                    jugadores[1].puntaje += 0; // Pierde el jugador 2
                } else {
                    jugadores[0].puntaje += 0; // Pierde el jugador 1
                    jugadores[1].puntaje += 3; // Gana el jugador 2
                }
                finJuego = true;
            } else {
                bool tableroLleno = true;
                for (int i = 0; i < FILAS; ++i) {
                    for (int j = 0; j < COLUMNAS; ++j) {
                        if (tablero[i][j] == '-') {
                            tableroLleno = false;
                            break;
                        }
                    }
                    if (!tableroLleno) {
                        break;
                    }
                }
                if (tableroLleno) {
                    cout << "¡Empate!" << endl;
                    jugadores[0].puntaje += 1;
                    jugadores[1].puntaje += 1;
                    finJuego = true;
                } else {
                    turno = (turno + 1) % numJugadores; // Cambiar turno
                }
            }
        }
    }
}

int main() {
    const int MAX_JUGADORES = 2; 
    Jugador jugadores[MAX_JUGADORES];

    // Inicializar datos de jugadores
    for (int i = 0; i < MAX_JUGADORES; ++i) {
        cout << "Ingrese el nombre del jugador " << i+1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].puntaje = 0;
    }

    int opcion;
    do {
        // Mostrar menú
        cout << "\n------Menu------" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Puntajes" << endl;
        cout << "3. Creditos" << endl;
        cout << "4. Salir" << endl;
        cout << "----------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugar(jugadores, MAX_JUGADORES);
                break;
            case 2:
                mostrarPuntajes(jugadores, MAX_JUGADORES);
                break;
            case 3:
                cout << "Desarrollado por: Lenin Jerez y Cristhian Espin" << endl;
                break;
            case 4:
                cout << "Hasta luego!" << endl;
                break;
            default:
                cout << "Opción invalida. Por favor, ingrese una opcion valida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}

