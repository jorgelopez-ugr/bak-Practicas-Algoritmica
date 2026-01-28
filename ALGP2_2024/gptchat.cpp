#include <iostream>
#include <vector>

using namespace std;

// Función para construir el calendario del torneo
void construirCalendario(int n) {
    // Crear una matriz para almacenar los enfrentamientos
    vector<vector<int>> calendario(n, vector<int>(n - 1, 0));

    // Caso base: solo dos participantes
    if (n == 2) {
        calendario[0][0] = 1;
        calendario[1][0] = 2;
    } else {
        // Dividir el problema en dos subproblemas
        int mitad = n / 2;
        construirCalendario(mitad); // Subproblema 1
        construirCalendario(mitad); // Subproblema 2

        // Combinar las soluciones
        for (int i = 0; i < mitad; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                calendario[i][j] = calendario[i][j] + mitad;
                calendario[i + mitad][j] = calendario[i][j] + 1;
                if (calendario[i + mitad][j] > n) {
                    calendario[i + mitad][j] -= n;
                }
            }
        }
    }

    // Imprimir el calendario
    cout << "Calendario del torneo:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Participante " << i + 1 << ": ";
        for (int j = 0; j < n - 1; ++j) {
            cout << calendario[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n; // Número de participantes (debe ser potencia de 2)
    cout << "Ingrese el número de participantes (potencia de 2): ";
    cin >> n;

    construirCalendario(n);

    return 0;
}

