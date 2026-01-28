#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

vector<vector<int>> min_coste(const vector<vector<int>>& costos) {
  int tam = costos.size();
  vector<vector<int>> min_coste(tam, vector<int>(tam, INT_MAX)); 
  
  for (int i=0 ; i<tam ; i++)
  {
    for (int j=i ; j<tam ; j++)
      min_coste[i][j] = costos[i][j];
  }
  
  for (int k = 0; k < tam; k++) {
    for (int i = 0; i < tam; i++) {
      for (int j = i + 1; j < tam; j++) {
        if (min_coste[i][k] != INT_MAX && min_coste[k][j] != INT_MAX) {
          min_coste[i][j] = min(min_coste[i][j], min_coste[i][k] + min_coste[k][j]);
        }
      }
    }
  }
  
  return min_coste;
}

//Calculo del costo mínimo
pair<vector<vector<int>>, vector<vector<int>>> min_coste_con_plan(const vector<vector<int>>& costos) {
    int tam = costos.size();
    vector<vector<int>> min_coste(tam, vector<int>(tam, INF));
    vector<vector<int>> next(tam, vector<int>(tam, -1));
    
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < tam; ++j) {
            if (costos[i][j] != INF) {
                min_coste[i][j] = costos[i][j];
                next[i][j] = j;  // Inicialmente, el siguiente nodo en el camino de i a j es j
            }
        }
    }

    for (int k = 0; k < tam; ++k) {
        for (int i = 0; i < tam; ++i) {
            for (int j = 0; j < tam; ++j) {
                if (min_coste[i][k] != INF && min_coste[k][j] != INF && 
                    min_coste[i][k] + min_coste[k][j] < min_coste[i][j]) {
                    min_coste[i][j] = min_coste[i][k] + min_coste[k][j];
                    next[i][j] = next[i][k];  
                }
            }
        }
    }

    return {min_coste, next};
}

vector<int> reconstruir_camino(int i, int j, const vector<vector<int>>& next) {
    if (next[i][j] == -1) {
        return {};  // No hay camino
    }
    vector<int> camino = {i};
    while (i != j) {
        i = next[i][j];
        camino.push_back(i);
    }
    return camino;
}

int main() {
    vector<vector<int>> costos = {
        {0, 3, 3, INF, INF},
        {INF, 0, 4, 7, INF},
        {INF, INF, 0, 2, 3},
        {INF, INF, INF, 0, 2},
        {INF, INF, INF, INF, 0}
    };

    // Calcular la matriz de costos mínimos y la matriz de caminos
    auto [min_cost, next] = min_coste_con_plan(costos);

    // Imprimir la matriz de costos mínimos
    cout << "Matriz de costos mínimos:" << endl;
    for (const auto& row : min_cost) {
        for (int cost : row) {
            if (cost == INT_MAX) {
                cout << "INF " << "\t";
            } else {
                cout << cost << "\t";
            }
        }
        cout << endl;
    }

    // Imprimir los caminos más cortos para cada par de aldeas
    cout << "\nCaminos más cortos:" << endl;
    for (int i = 0; i < next.size(); ++i) {
        for (int j = 0; j < next.size(); ++j) {
            if (i != j) {
                cout << "Camino de " << i + 1 << " a " << j + 1 << ": ";
                vector<int> camino = reconstruir_camino(i, j, next);
                if (camino.empty()) {
                    cout << "No hay camino" << endl;
                } else {
                    for (int nodo : camino) {
                        cout << nodo + 1 << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
}

