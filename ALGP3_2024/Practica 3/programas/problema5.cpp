#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int buscar_menor(vector<vector<int>> matriz, int ciudad_actual, int ciudades_visitadas[5]){
    int menor = -1;
    for (int i = 0; i < 5; i++){
        if (ciudades_visitadas[i] == 0 && ciudad_actual != i && matriz[ciudad_actual][i] != -1){
            if (menor == -1 ){
                menor = i;
            } else if (matriz[ciudad_actual][i] < matriz[ciudad_actual][menor]){
                menor = i;
            }
        }
    }
    return menor;
}

int main() {
    // Semilla para generar números aleatorios
    std::srand(std::time(0));

    // Crear una matriz 5x5
    vector<vector<int>> matriz(5);
    int ciudades_visitadas[5] = {0, 0, 0, 0, 0};

    int ciudad_inicial = std::rand() % 5;

    //Plaza Azcárate = 0
    //Plaza de las maravillas = 1
    //Plaza de la constitución = 2
    //Plaza de la libertad = 3
    //Plaza mayor = 4

    matriz[0] = {0, 450004, 748456, 1100000, 130000};
    matriz[1] = {450004, 0, 143552, 555123, -1};
    matriz[2] = {748456, 143552, 0, 1700000, 554521};
    matriz[3] = {1100000, 555123, 1700000, 0, 1300000};
    matriz[4] = {13000, -1, 554521, 1300000, 0};

    int ciudad_actual = ciudad_inicial;
    int ciudad_siguiente = -1;
    int distancia_total = 0;
    
    for (int i = 0; i < 5; i++){
        cout << "Ciudad actual: " << ciudad_actual << endl;
        ciudades_visitadas[ciudad_actual] = 1;
        ciudad_siguiente = buscar_menor(matriz, ciudad_actual, ciudades_visitadas);
        if (ciudad_siguiente == -1) {
            break;
        }
        cout << "Ciudad siguiente: " << ciudad_siguiente << endl;
        distancia_total += matriz[ciudad_actual][ciudad_siguiente];
        ciudad_actual = ciudad_siguiente;
    }

    cout << "Distancia total: " << distancia_total << endl;

    return 0;
}
