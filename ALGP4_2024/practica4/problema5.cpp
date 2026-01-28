#include <vector>
#include <iostream>
#include <set>
#include <list>

using namespace std;

vector<pair<int,int>> mejor;
int n = 5;
int finFil = n-1;
int finCol = n-1;

struct nodo{
    int fil;
    int col;
    vector<pair<int,int>> secuenciaSeguida;
};

list<nodo> frontera2;

void backTracking3(vector<vector<bool>> matriz){
    
    if (!frontera2.empty()){
        nodo nodoAct = frontera2.front();
        frontera2.pop_front();

        if ( (nodoAct.fil == finFil && nodoAct.col == finCol) && (nodoAct.secuenciaSeguida.size() <= mejor.size() || mejor.empty() ) ){
            mejor = nodoAct.secuenciaSeguida;
        }
        else
        {
        //generamos los posibles caminos si los hay desde dicho nodo y pusheamos a la frontera.
        for (int i = -1 ; i <= 1 ; i++){
            if (i != 0){
                if (nodoAct.fil+i >= 0 && nodoAct.fil+i < n ){
                    if (matriz[nodoAct.fil+i][nodoAct.col] && (mejor.empty() || nodoAct.secuenciaSeguida.size() < mejor.size())){
                        nodo nodoHijo;
                        nodoHijo.fil = nodoAct.fil+i;
                        nodoHijo.col = nodoAct.col;
                        nodoHijo.secuenciaSeguida = nodoAct.secuenciaSeguida;
                        nodoHijo.secuenciaSeguida.push_back({nodoHijo.fil,nodoHijo.col});
                        
                        frontera2.push_back(nodoHijo);
                    }
                }

                if (nodoAct.col+i >= 0 && nodoAct.col+i < n ){
                    if (matriz[nodoAct.fil][nodoAct.col+i] && (mejor.empty() || nodoAct.secuenciaSeguida.size() < mejor.size())){
                        nodo nodoHijo;
                        nodoHijo.fil = nodoAct.fil;
                        nodoHijo.col = nodoAct.col+i;
                        nodoHijo.secuenciaSeguida = nodoAct.secuenciaSeguida;
                        nodoHijo.secuenciaSeguida.push_back({nodoHijo.fil,nodoHijo.col});
                        frontera2.push_back(nodoHijo);
                    }
                }
            }
        }

            if (!frontera2.empty()){
                backTracking3(matriz);
            }
        }
    }    
}

int main(){
    // Matriz del laberinto
    //vector<vector<bool>> laberinto = {
    //    {true, true, true, false,true},
    //    {false,false,true, false,true},
    //    {true, true, true, true, true},
    //    {true, false,false,false,false},
    //    {true, true, true, true, true}
    //};

     //// Matriz del laberinto
     //vector<vector<bool>> laberinto = {
     //    {true, true, true, true ,true},
     //    {false,false,false, false,true},
     //    {true, true, true, true, true},
     //    {true, false,false,false,false},
     //    {true, true, true, true, true}
     //};

     // Matriz del laberinto
     vector<vector<bool>> laberinto = {
         {true, true, true, true  ,true},
         {true,false,true, false, true},
         {true, true, true, true  ,true},
         {false, false,true,false ,true},
         {true, true, true, true  ,true},
     };

    nodo nodoOrig;
    nodoOrig.fil = 0;
    nodoOrig.col = 0;
    nodoOrig.secuenciaSeguida.push_back({0,0});

    frontera2.push_back(nodoOrig);
    backTracking3(laberinto);

    cout << "Laberinto:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (laberinto[i][j] ? "1" : "0") << " ";
        }
        cout << endl;
    }

    vector<vector<int>> visualizaMatriz(n,vector<int>(n));

    for (int i = 0 ; i < n; i++){
        for (int j = 0 ; j < n ; j++){
            visualizaMatriz[i][j] = static_cast<int>(laberinto[i][j]);
        }
    }

    for (int i = 0 ; i < mejor.size() ; i++){
        visualizaMatriz[mejor[i].first][mejor[i].second] = 2;
    }

    cout << "Visualiza:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << visualizaMatriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << "la mejor ruta es: " << endl;
    for (int i = 0 ; i < mejor.size() ; i++){
        cout << " (" << mejor[i].first << "," << mejor[i].second << ") ";
    }
}



