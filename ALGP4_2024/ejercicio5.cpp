#include <iostream>
#include <vector>
#include <set>
#include <list>

using namespace std;

class nodo{
private:
    int x;
    int y;
    vector<pair<int,int>> secuencia;
public:
    nodo(int x, int y){
        this->x = x;
        this->y = y;
        secuencia.push_back({x,y});
    }

//por si falla recuerda en un futuro que la copia de las secuencias puede ser el motivo. pero tambien puede no serlo
    void operator=(const nodo& otro){
        this->x = otro.x;
        this->y = otro.y;
        secuencia = otro.secuencia;
    }

    bool operator<(const nodo& otro) const {
        if (x < otro.x){
            return true;
        }
        else if (x == otro.x && y < otro.y)
        {
            return true;
        }
        else{
            return false;
        }
        
    }
    
    void pusheaNueva(int x, int y){
        this->x = x;
        this->y = y;
        secuencia.push_back({x,y});
    }

    int numPosiblesCercanas(vector<vector<bool>> matriz){
        int count = 0;
        for (int i = -1 ; i <= 1 ; i++){
            for (int j = -1 ; j <= 1 ; j++){
                if (i >= 0 && i < matriz.size() && j >= 0 && j < matriz.size() && i != 0 && j != 0){
                    if (matriz[x+i][y+j]){
                        count++;
                    }
                }
            }
        }

        return count;
    }

    vector<pair<int,int>> getSecuencia(){
        return secuencia;
    }

    list<nodo> posiblesCercanas(vector<vector<bool>> matriz){
        list<nodo> solucion;
        
        for (int i = -1 ; i <= 1 ; i++){
            for (int j = -1 ; j <= 1 ; j++){
                if (i >= 0 && i < matriz.size() && j >= 0 && j < matriz.size() && i != 0 && j != 0){
                    if (matriz[x+i][y+j]){
                        nodo nuevo_nodo = *this;
                        nuevo_nodo.pusheaNueva(x+i,y+j);
                        solucion.push_back(nuevo_nodo);
                    }
                }
            }
        }

        return solucion;
    }

    bool esSolucion(int xSoluc, int ySoluc){
        if (x == xSoluc && y == ySoluc){
            return true;
        }
        else
        {
            return false;
        }
    }
};

vector<pair<int,int>> secuenciaSolucion(vector<vector<bool>> matriz, nodo posInicial, int finX, int finY){

    nodo nodo_hijo = posInicial;
    set<nodo> explorados;
    list<nodo> frontera;
    int tamSolCorta = 1000;
    nodo nodo_solucion(0,0);

    frontera.push_back(posInicial);

    while (!frontera.empty())
    {
        nodo_hijo = frontera.front();
        frontera.pop_front();
        explorados.insert(nodo_hijo);

        while (!frontera.empty() && (explorados.find(nodo_hijo) != explorados.end()))
        {
            nodo_hijo = frontera.front();
            frontera.pop_front();
        }

        if (nodo_hijo.esSolucion(finX,finY)){
            if (nodo_hijo.getSecuencia().size() < tamSolCorta){
                tamSolCorta = nodo_hijo.getSecuencia().size();
                nodo_solucion = nodo_hijo;
            }
        }

        list<nodo> posibles_cercanas = nodo_hijo.posiblesCercanas(matriz);

        while (!posibles_cercanas.empty())
        {
            if (explorados.find(posibles_cercanas.front()) == explorados.end()){
                frontera.push_back(posibles_cercanas.front());
                posibles_cercanas.pop_back();
            }
        }
    }

    return nodo_solucion.getSecuencia();
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
