#include <iostream>
#include <vector>

using namespace std;

/*Definición del tipo para representar a las alumnos 
y sus puntos de preferencia como una matriz*/
typedef vector<vector<int>> parejas;

/*Función auxiliar que nos permite comprobar si un estudiante ha sido emparejado o no.*/
bool esValido(int estudiante, const vector<int>& asignaciones) {
    for (int i = 0; i < asignaciones.size(); ++i) {
        if (asignaciones[i] == estudiante) {
            return false;
        }
    }
    return true;
}

// Función auxiliar para calcular el valor del emparejamiento
int calculaUnion(const parejas &prefs, const vector<int> &asignaciones) {
    int value = 0;
    for (int i = 0; i < asignaciones.size()-1; i+=2) {
        int estudiante_i = asignaciones[i];
        int estudiante_j = asignaciones[i+1];
        value += prefs[estudiante_i][estudiante_j] * prefs[estudiante_j][estudiante_i];
    }
    return value;
}


/*Función que aplica Backtracking*/
void ParejasBacktracking(const parejas& prefs, vector<int>& asignaciones, int est, int& mejor_valor, vector<int>& best_asignaciones) {
    int n = prefs.size();
    if (est == n) {
        // Hemos emparejado a todos los estudiantes
        int valor_union = calculaUnion(prefs, asignaciones);

        if (valor_union > mejor_valor) {
            mejor_valor = valor_union;
            best_asignaciones = asignaciones;
        }
        return;
    }

    for (int estudiante = 0; estudiante < n; ++estudiante) {
        if (esValido(estudiante, asignaciones)) {
            asignaciones[est] = estudiante;
            ParejasBacktracking(prefs, asignaciones, est + 1, mejor_valor, best_asignaciones);
            asignaciones[est] = -1; // Deshacer la asignación
        }
    }
}

int main() {
    int n = 4; // Número de estudiantes

    parejas prefs = {
            {0, 9,10, 17},
            {3, 0, 13, 13},
            {9, 4, 0, 12},
            {4, 6, 11, 0}
    };

    vector<int> asignaciones(n, -1); // Inicialización de asignaciones
    int mejor_valor = 0;
    vector<int> best_asignaciones(n, -1);

    // Ejecutar el algoritmo de backtracking recursivo
    ParejasBacktracking(prefs, asignaciones, 0, mejor_valor, best_asignaciones);

    int cuenta_salto = 0;
    cout << "Parejas formadas:" << endl;
    for (int estudiante : best_asignaciones){
        cout << estudiante;
        cuenta_salto++;

        if((cuenta_salto)% 2 == 0){
            cout << "\n";
        }
        else{
            cout << " emparejado con estudiante ";
        }
    }

    cout << "Valor: " << mejor_valor << endl;

    return 0;
}
