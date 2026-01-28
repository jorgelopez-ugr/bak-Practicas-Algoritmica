#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> mapa = {
    {' ', 'O', 'M', ' '},
    {'O', ' ', ' ', ' '},
    {' ', 'O', ' ', ' '},
    {' ', 'O', ' ', ' '},
    {' ', 'O', ' ', ' '},
    {'S', 'O', 'O', ' '}
};

vector<vector<int>> dp(6, vector<int>(4, -1));
vector<vector<pair<int, int>>> direcciones(6, vector<pair<int, int>>(4, {-1, -1}));

int buscaOro(int i, int j) {
    if (i < 0 || i >= 6 || j < 0 || j >= 4 || mapa[i][j] == 'M') {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int oro = 0;
    if (mapa[i][j] == 'O') {
        oro = 1;
    }
    
    int abajo = buscaOro(i + 1, j);
    int izquierda = buscaOro(i, j - 1);
    int abajoIzquierda = buscaOro(i + 1, j - 1);

    int maxOro = max({abajo, izquierda, abajoIzquierda});

    if (maxOro == abajo) {
        direcciones[i][j] = {i + 1, j};
    } else if (maxOro == izquierda) {
        direcciones[i][j] = {i, j - 1};
    } else {
        direcciones[i][j] = {i + 1, j - 1};
    }

    dp[i][j] = oro + maxOro;

    return dp[i][j];
}

vector<pair<int, int>> recuperarPasos(int i, int j) {
    vector<pair<int, int>> pasos;

    while (i >= 0 && i < 6 && j >= 0 && j < 4) {
        pasos.push_back({i, j});
        pair<int, int> siguiente = direcciones[i][j];
        i = siguiente.first;
        j = siguiente.second;
    }

    return pasos;
}

int main() {
    int resultado = buscaOro(0, 3);  // posición inicial en la esquina superior derecha

    cout << "Número máximo de bolsas de oro: " << resultado << endl;

    vector<pair<int, int>> pasos = recuperarPasos(0, 3);
    cout << "Pasos: ";
    for (const auto& paso : pasos) {
        cout << "(" << paso.first << ", " << paso.second << ") ";
    }
    cout << endl;

    return 0;
}
