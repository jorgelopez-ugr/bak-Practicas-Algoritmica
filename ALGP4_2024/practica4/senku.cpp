
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

stack<pair<pair<int, int>, pair<int, int>>> movimientos; //He utilizado una pila por la eficiencia de insertar e eliminar elementos

vector<vector<char>> tablero = 
{
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'O', 'O', 'O', ' ', 'O', 'O', 'O'},
    {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'}
};

bool movimientoValido(int fila, int columna, int direccion_f, int direccion_c){
    if (fila+2*direccion_f < 0 || fila+2*direccion_f >= 7 || columna+2*direccion_c < 0 || columna+2*direccion_c >= 7)
        return false;
    return tablero[fila][columna] == 'O' && tablero[fila+direccion_f][columna+direccion_c] == 'O' && tablero[fila+2*direccion_f][columna+2*direccion_c] == ' ';
}

void realizaMovimiento(int fila, int columna, int direccion_f, int direccion_c){
    tablero[fila][columna] = ' ';
    tablero[fila+direccion_f][columna+direccion_c] = ' ';
    tablero[fila+2*direccion_f][columna+2*direccion_c] = 'O';
    movimientos.push({{fila, columna},{2*direccion_f, 2*direccion_c}});
}

void deshacerMovimiento(int fila, int columna, int direccion_f, int direccion_c){
    tablero[fila][columna] = 'O';
    tablero[fila+direccion_f][columna+direccion_c] = 'O';
    tablero[fila+2*direccion_f][columna+2*direccion_c] = ' ';
    movimientos.pop();
}

bool backtracking(int piezas_restantes){
    if (piezas_restantes == 1 && tablero[3][3] == 'O')
        return true;

    for (int fila = 0; fila < 7; fila++){
        for (int columna = 0; columna < 7; columna++){
            if (tablero[fila][columna] != 'O')
                continue;
            for (int direccion_f = -1; direccion_f <= 1; direccion_f++){
                for (int direccion_c = -1; direccion_c <= 1; direccion_c++){
                    if ((direccion_f == 0 && direccion_c == 0) || (direccion_f != 0 && direccion_c != 0)) //Para que no haya movimientos diagonales
                        continue;
                    if (movimientoValido(fila, columna, direccion_f, direccion_c)){
                        realizaMovimiento(fila, columna, direccion_f, direccion_c);
                        if (backtracking(piezas_restantes - 1))
                            return true;
                        deshacerMovimiento(fila, columna, direccion_f, direccion_c);
                    }
                }
            }
        }
    }
    return false;
}

int main(){
    if (backtracking(32)){
        cout << "Solución encontrada:\n";
        for (const auto& fila : tablero){
            for (char celda : fila){
                cout << celda << ' ';
            }
            cout << '\n';
        }

        
        stack<pair<pair<int, int>, pair<int, int>>> auxiliar;


        while (!movimientos.empty()){
        auxiliar.push(movimientos.top());
        movimientos.pop();
        }

        cout << "Lista de movimientos:" << '\n';
           while (!auxiliar.empty()){
            cout << "ficha :(" << auxiliar.top().first.first << ", " << auxiliar.top().first.second << ") movida de " << '(' << auxiliar.top().second.first << ", " << auxiliar.top().second.second << ")\n";
            auxiliar.pop();
        }
    } 
    else{
        cout << "No hay solución.\n";
    }
    return 0;
}