#include <iostream>
#include <vector>

using namespace std;

bool sePuedeVisitar(int x, int y, int n, vector<vector<bool>> &laberinto, vector<vector<bool>> &visitadas) {
    return (x >= 0 && x < n && y >= 0 && y < n && laberinto[x][y] && !visitadas[x][y]);
}

void explorarLaberinto(int x, int y, int n, vector<vector<bool>> &laberinto, vector<vector<bool>> &visitadas, vector<vector<int>> &pasos, int numPaso, vector<vector<vector<int>>> &soluciones) {
    if (x == n - 1 && y == n - 1) {
        visitadas[x][y] = true;
        pasos[x][y] = numPaso; 
        soluciones.push_back(pasos); 
        visitadas[x][y] = false;
        pasos[x][y] = 0; 
        return;
    }

    if (sePuedeVisitar(x, y, n, laberinto, visitadas)) {
        visitadas[x][y] = true;
        pasos[x][y] = numPaso;

       
        explorarLaberinto(x + 1, y, n, laberinto, visitadas, pasos, numPaso + 1, soluciones);
        explorarLaberinto(x, y + 1, n, laberinto, visitadas, pasos, numPaso + 1, soluciones);
        if (x > 0) explorarLaberinto(x - 1, y, n, laberinto, visitadas, pasos, numPaso + 1, soluciones);
        if (y > 0) explorarLaberinto(x, y - 1, n, laberinto, visitadas, pasos, numPaso + 1, soluciones);

        visitadas[x][y] = false; 
        pasos[x][y] = 0; 
    }
}

bool resolverLaberinto(vector<vector<bool>> &laberinto) {
    int n = laberinto.size();
    vector<vector<bool>> visitadas(n, vector<bool>(n, false));
    vector<vector<int>> pasos(n, vector<int>(n, 0));
    vector<vector<vector<int>>> soluciones;

    explorarLaberinto(0, 0, n, laberinto, visitadas, pasos, 1, soluciones);

    if (soluciones.empty()) {
        cout << "No se encontró ninguna solución." << endl;
        return false;
    }

    cout << "Caminos encontrados:" << endl;
    int numSoluciones = 1;
    for (auto sol : soluciones) {
        cout << "Solución " << numSoluciones++ << ":" << endl;
        for (auto fil : sol) {
            for (auto col : fil) {
                cout << col << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    return true;
}

int main() {
    // Definir el tamaño de la matriz del laberinto
    int N = 5;
    // Crear la matriz del laberinto (true: se puede pasar, false: no se puede pasar)
    vector<vector<bool>> laberinto = {
        {true, true, true, false, true},
        {false, false, true, false, true},
        {true, true, true, true, true},
        {true, false, false, false, false},
        {true, true, true, true, true}
    };

    // Posición inicial
    nodo posInicial(0, 0);
    // Posición de destino
    int destinoX = N-1;
    int destinoY = N-1;

    // Encontrar la secuencia de solución
    vector<pair<int, int>> solucion = secuenciaSolucion(laberinto, posInicial, destinoX, destinoY);

    // Imprimir la secuencia de solución
    cout << "Secuencia de solución:" << endl;
    for (auto p : solucion) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return 0;
}
