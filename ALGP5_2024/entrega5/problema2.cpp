#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int costeDeUnaSecuencia(vector<vector<int>> matriz, vector<int> secuencia){

    int solucion = 0;

    for (int i = 1 ; i < secuencia.size() ; i++){
        solucion += matriz[secuencia[i-1]][secuencia[i]];
    }

    if (secuencia.size() >= 2)
        solucion += secuencia.size() - 2; // por el coste de las escalas

    return solucion;
}

bool contenida(vector<vector<int>> soluciones, vector<int> secuencia){

    for (int i = 0 ; i < soluciones.size() ; i++){
        if (soluciones[i] == secuencia){
            return true;
        }
    }
    return false;
}


vector<int> caminoMasCorto(vector<vector<int>> matriz, int ini, int fin) {
    int coste_directo = matriz[ini][fin];
    vector<vector<int>> soluciones_parciales;
    vector<vector<int>> soluciones_desechadas;
    vector<vector<int>> soluciones;
    vector<int> secuencia;
    int coste;

    map<vector<int>,int> costes_ya_calculados;

    secuencia.push_back(ini);
    soluciones_parciales.push_back(secuencia);

    secuencia.push_back(fin);
    costes_ya_calculados[secuencia] = matriz[ini][fin];

    soluciones.push_back(secuencia);

    while (!soluciones_parciales.empty())
    {     
        secuencia = soluciones_parciales.back();

        soluciones_parciales.pop_back();

        for (int i = 0 ; i < matriz.size() ; i++){
            if (i != secuencia.back() && i != ini){

                secuencia.push_back(i);
                
                if (costes_ya_calculados.find(secuencia) == costes_ya_calculados.end()){
                    coste = costeDeUnaSecuencia(matriz,secuencia);
                    costes_ya_calculados[secuencia] = coste;
                }
                else
                {
                    coste = costes_ya_calculados[secuencia];
                }
                

                if (!contenida(soluciones_desechadas,secuencia)){
                    if (coste <= coste_directo){
                        if (i == fin){
                            soluciones.push_back(secuencia);
                        }
                        else
                        {
                            soluciones_parciales.push_back(secuencia);
                        }

                        secuencia.pop_back();
                    }
                    else
                    {
                        soluciones_desechadas.push_back(secuencia);
                    }
                }
            }
        }
    }

    vector<int> secuencia_mejor;
    int coste_mejor = coste_directo;

    for (int i = 0 ; i < soluciones.size(); i++){
        int coste_secuencia = costes_ya_calculados[soluciones[i]];

        if (coste_secuencia <= coste_mejor){
            secuencia_mejor = soluciones[i];
            coste_mejor = coste_secuencia;
        }
    }

    cout << "el coste mejor es: " << costes_ya_calculados[secuencia_mejor] << endl;
    cout << "el coste directo es: " << matriz[ini][fin] << endl;
    return secuencia_mejor;
}

int main(){

    vector<vector<int>> matriz;

    matriz.push_back({0,2,1,3});
    matriz.push_back({7,0,9,2});
    matriz.push_back({2,2,0,1});
    matriz.push_back({3,4,8,0});

    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            
            cout << "va desde:" << i << " hasta: " << j << endl;

            vector<int> solucion = caminoMasCorto(matriz,i,j);

            for (int i = 0 ; i < solucion.size() ; i++){
                cout << "pasa por " << solucion[i] << ", ";
            }

            cout << endl;   
            cout << endl;
            cout << endl;
            cout << endl;
        }
    }
}

