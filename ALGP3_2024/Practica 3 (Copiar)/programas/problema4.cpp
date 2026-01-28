#include <iostream>
#include <vector>
#include <limits>
#include <time.h>
#include <string>

using namespace std;

const int PESOS = 10;

struct Nodo{
    int identificador;  //Identificador del nodo
    int dist_serv;  //Distancia total al servidor
    vector<int> conexiones; //Nodos con los que se conecta
    vector<int> tiempo_conex; //Tiempo que hay entre los nodos con los que se conecta.
};

struct caminos{
    vector<int> camino; //nodos por los que tiene que pasar para llegar al servidor.
};

int menorTiempo(vector<Nodo> nodos){
    int menor = 100000;
    int sensor = -1;

    for(int i = 0; i < nodos.size(); i++){
        if(nodos[i].dist_serv < menor){
            menor = nodos[i].dist_serv;
            sensor = i;
        }
    }

    return sensor;
}

bool busca(vector<Nodo> nodos, int id){
    bool encontrado = false;

    for(int i = 0; i < nodos.size(); i++){
        if(id == nodos[i].identificador){
            encontrado = true;
            break;
        }
    }

    return encontrado;
}

void red_sensores(vector<Nodo> &grafo_red, int servidor, vector<caminos> &solucion){
    int seleccionados = 1;
    int peso;
    int padre = servidor;

    vector<Nodo> elegidos;

    elegidos.push_back(grafo_red.at(servidor));

    while(seleccionados < grafo_red.size()){
        int menor = 100000;

        vector<Nodo> candidatos;

        for(int i = 0; i < elegidos.size(); i++){

            for(int j = 0; j < (elegidos.at(i)).conexiones.size(); j++){

                if(!busca(elegidos, elegidos.at(i).conexiones.at(j))){

                    int pesoServ = elegidos.at(i).dist_serv;
                    Nodo x = grafo_red.at(elegidos.at(i).conexiones.at(j));
                    x.dist_serv += (pesoServ + elegidos.at(i).tiempo_conex.at(j));

                    if(x.dist_serv < menor){
                        padre = elegidos.at(i).identificador;

                        menor = x.dist_serv;
                    }

                    candidatos.push_back(x);

                }
            }
        }

        int seleccionado = menorTiempo(candidatos);

        seleccionados++;

        grafo_red.at(candidatos.at(seleccionado).identificador).dist_serv = candidatos.at(seleccionado).dist_serv;
        
        elegidos.push_back(grafo_red.at(candidatos.at(seleccionado).identificador));

        solucion.at(candidatos.at(seleccionado).identificador) = solucion.at(padre);

        (solucion.at(candidatos.at(seleccionado).identificador)).camino.push_back(candidatos.at(seleccionado).identificador);
    }
}

int main(){
    int n_nodos = 5;

    vector<caminos> salida;

    srand(time(NULL)); 
 
    int num = 0;

    //cout << "Introduzca el número de nodos que desee: ";
    //cin >> n_nodos;

    //Vamos a crear la matriz en la que se verá representada el grafo.

    int matriz[n_nodos][n_nodos] = {0};
 
    for(int i = 0; i < n_nodos; i++){ 
        for(int j = i; j < n_nodos; j++){ 
            num = rand()%(PESOS);

            if(i==j){
                matriz[i][j] = 0; 
            }
            else{ 
                matriz[i][j] = num; 
                matriz[j][i] = num; 
            }  
        } 
    } 

    for(int i = 0; i < n_nodos; i++){ 
        
        for(int j = 0; j < n_nodos; j++){ 
            cout << matriz[i][j] << " "; 
        } 
        
        cout << endl; 
    }

    /*Tras crearla y mostrarla en pantalla, vamos a pasarla a un vector
    que almacena nodos, este tipo de dato(Nodo) almacena su identificador,
    el el destino hacia el servidor, un vector con los nodos a los que se
    conecta y otro vector que incluye el tiempo de las conexiones con los
    distintos nodos.*/

    vector<Nodo> red;

    for(int i = 0; i < n_nodos; i++){
        Nodo n;

        n.identificador = i;
        n.dist_serv = 0;

        for(int j = 0; j < n_nodos; j++){

            //Si encontramos una conexión, la añadimos.
            if(matriz[i][j] != 0){
                n.conexiones.push_back(j);
                n.tiempo_conex.push_back(matriz[i][j]);
            }
        }

        red.push_back(n);
    }

    /*A continuación mostraremos los grafos y sus conexiones(junto con el 
    tiempo que tardan estas) para que se entienda bien cómo están concetados*/

    for(int i = 0; i < n_nodos; i++){
        cout << "Nodo sensor " << red[i].identificador << " :[";

        for(int j = 0; j < red[i].conexiones.size(); j++){
            cout << "(" << ((red.at(i)).conexiones).at(j) << "," << ((red.at(i)).tiempo_conex).at(j) << "),";
        }

        cout << "]" << endl;
    }

    //Elegimos un nodo servidor aleatorio.    
    int servidor = rand()%(n_nodos);

    /*Aquí inicializo el vector solución, este luego se modificará a la hora
    de llamar a la función.*/

    for(int i = 0; i < n_nodos; i++){
        caminos resultado;

        vector<int> camino;

        camino.push_back(i);

        resultado.camino = camino;

        salida.push_back(resultado);
    }

    //Llamamos a la función que implementa el algoritmo.
    red_sensores(red, servidor, salida);

    cout << endl;
    cout << "MOSTRANDO RESULTADOS:" << endl;

    //Por último mostramos la solución con los recorridos.

    for(int i = 0; i < n_nodos; i++){
        cout << "Nodo sensor " << i << ", recorre: [";

        for(int j = salida.at(i).camino.size() - 1; j >= 0; j--){
            cout << (salida.at(i)).camino.at(j) << " ";
        }

        cout << "]" << endl;
    }

    cout << endl;
}