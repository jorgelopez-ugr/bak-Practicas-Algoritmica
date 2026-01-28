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
    vector<vector<bool>> laberinto = {
       {1, 1, 0},
       {1, 0, 1},
       {1, 1, 1}
    };

    if (!resolverLaberinto(laberinto)) {
        cout << "No existe un camino de inicio a fin." << endl;
    }

    return 0;
}
