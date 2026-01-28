#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// Función para encontrar el emparejamiento óptimo
vector<pair<int, int>> HacerParejas(vector<vector<int>>& preferencias) {
    int num_estudiantes = preferencias.size();
    vector<bool> emparejados(num_estudiantes, false);
    vector<pair<int, int>> parejas_finales;

    for (int k = 0; k < num_estudiantes / 2; ++k) {
        int max_emparejamiento = -1;
        pair<int, int> mejor_pareja;

        // Buscar la mejor pareja no emparejada
        for (int i = 0; i < num_estudiantes; ++i) {
            if (!emparejados[i]) {
                for (int j = i + 1; j < num_estudiantes; ++j) {
                    if (!emparejados[j]) {
                        int valor = preferencias[i][j] * preferencias[j][i];
                        if (valor > max_emparejamiento) {
                            max_emparejamiento = valor;
                            mejor_pareja = {i, j};
                        }
                    }
                }
            }
        }

        // Emparejar y marcar como emparejados
        emparejados[mejor_pareja.first] = true;
        emparejados[mejor_pareja.second] = true;
        parejas_finales.push_back(mejor_pareja);
    }

    return parejas_finales;
}

int main() {
    int n = 4; // Número de estudiantes
    vector<vector<int>> preferencias = {
        {0,1,3,1},
        {5,0,10,7},
        {5,1,0,8},
        {12,3,4,0}
    };

    vector<pair<int, int>> pairs = HacerParejas(preferencias);

    for (auto &pair : pairs) {
        cout << "Estudiante " << pair.first << " emparejado con Estudiante " << pair.second << endl;
    }

    return 0;
}
