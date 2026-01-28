#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> secuenciaSolucion;
vector<pair<int,int>> yaVisitadas;
int sizeN;
//suponemos que solo se puede mover en horizontal y vertical, nada de movimiento oblicuo
vector<pair<int,int>> backtracking(vector<vector<bool>> matriz, int actX, int actY, int finX, int finY,
                                   vector<pair<int,int>> secuenciaActual, int tamSolActual){
    secuenciaActual.push_back({actX,actY});

    if (actX == finX && actY == finY){
        if (secuenciaSolucion.size() > secuenciaActual.size()){
            secuenciaSolucion = secuenciaActual;
            return secuenciaActual;
        }
    }
    else
    {
        for (int i = -1 ; i <= 1 ; i++){
            if (i != 0){
                if (actX+i >= 0 && actX+i < sizeN){
                    if (matriz[actX+i][actY]){
                        if (secuenciaActual.size()+1 < secuenciaSolucion.size()){
                            backtracking(matriz,actX+i,actY,finX,finY,secuenciaActual,secuenciaActual.size());
                        }
                    }
                }

                if (actY+i >= 0 && actY+i < sizeN){
                    if (matriz[actX][actY+i]){
                        if (secuenciaActual.size()+1 < secuenciaSolucion.size()){
                            backtracking(matriz,actX,actY+i,finX,finY,secuenciaActual,secuenciaActual.size());
                        }
                    }
                }
            }
        }
    }
}

int main() {
    
}

// void backTracking(vector<vector<bool>> matriz, int actX, int actY, vector<pair<int,int>> secuenciaAct){
    
//     secuenciaAct.push_back({actX,actY});
//     exploradas.insert({actX,actY});

//     // bool analizada_completa = true;
//     // for (int i = -1 ; i <= 1 && analizada_completa; i++){

//     //     if (exploradas.find({actX+i,actY}) == exploradas.end()){
//     //         analizada_completa = false;
//     //     }

//     //     if (exploradas.find({actX+i,actY}) == exploradas.end()){
//     //         analizada_completa = false;
//     //     }
//     // }

//     // if (analizada_completa){
//     //     completasAnalizadas.insert({actX,actY});
//     // }

//     // cout << "la secuencia actual es: " << endl;
//     // for (int i = 0 ; i < secuenciaAct.size() ; i++){
//     //     cout << " (" << secuenciaAct[i].first << "," << secuenciaAct[i].second << ") ";
//     // }
//     // cout << endl;

//     // cout << "la actual mejor ruta es: " << endl;
//     // for (int i = 0 ; i < mejor.size() ; i++){
//     //     cout << " (" << mejor[i].first << "," << mejor[i].second << ") ";
//     // }

//     // cout << "nos econtramos en la posicion: (" << actX << "," << actY << ")" << endl;
//     // cout << "hay una solucion?:" << hayUnaSolucion;

//     if ( (actX == finX && actY == finY ) && (secuenciaAct.size() < mejor.size() || !hayUnaSolucion) ){
//         hayUnaSolucion = true;
//         // cout << endl << endl;
//         // cout << "UN CAMINO HA LLEGADO A SOLUCION" << endl;
//         // cout << endl;
        
//         mejor = secuenciaAct;
//     }
//     else
//     {
//         for (int i = -1 ; i <= 1 ; i++){
//             if (i != 0){
//                 if (actX+i >= 0 && actX+i < n){    
//                     if (matriz[actX+i][actY]){
//                         if (exploradas.find({actX+i,actY}) == exploradas.end()){
//                             backTracking(matriz,actX+i,actY,secuenciaAct);
//                         }
//                         // if (exploradas.find({actX+i,actY}) == exploradas.end() && (actX+i != anteX && actY != anteY)){
//                         //     backTracking(matriz,actX+i,actY,actX,actY,secuenciaAct);
//                         // }
//                         // if (secuenciaAct.size() < mejor.size() || !hayUnaSolucion){
//                         //     backTracking(matriz,actX+i,actY,secuenciaAct);
//                         // }
//                         // if (completasAnalizadas.find({actX+i,actY}) == completasAnalizadas.end()){
//                         //     backTracking(matriz,actX+i,actY,secuenciaAct);
//                         // }
//                     }
//                 }

//                 if (actY+i >= 0 && actY+i < n){    
//                     if (matriz[actX][actY+i]){
//                         if (exploradas.find({actX,actY+i}) == exploradas.end()){
//                             backTracking(matriz,actX,actY+i,secuenciaAct);
//                         }
//                         // if (exploradas.find({actX,actY+i}) == exploradas.end() && (actX!= anteX && actY+i != anteY)){
//                         //     backTracking(matriz,actX,actY+i, actX,actY,secuenciaAct);
//                         // }
//                         // if (secuenciaAct.size() < mejor.size() || !hayUnaSolucion){
//                         //     backTracking(matriz,actX,actY+i,secuenciaAct);
//                         // }
//                         // if (completasAnalizadas.find({actX,actY+i}) == completasAnalizadas.end()){
//                         //     backTracking(matriz,actX,actY+i,secuenciaAct);
//                         // }
//                     }
//                 }
//             }
//         }
//     }
// }

// void backTracking2(vector<vector<bool>> matriz, vector<pair<int,int>> secuenciaAct){
    
//     // if (frontera.empty()){
//     //     return;
//     // }

//     while (!frontera.empty())
//     {
        
    
//         int actX = frontera.front().first;
//         int actY = frontera.front().second;
//         frontera.pop_front();

//         secuenciaAct.push_back({actX,actY});
//         exploradas.insert({actX,actY});

//         if ( (actX == finX && actY == finY ) && (secuenciaAct.size() < mejor.size() || !hayUnaSolucion) ){
//             hayUnaSolucion = true;        
//             mejor = secuenciaAct;

//             cout << "saco una solucion";
//         }
//         else
//         {
//             for (int i = -1 ; i <= 1 ; i++){
//                 if (i != 0){
//                     if (actX+i >= 0 && actX+i < n){    
//                         if (matriz[actX+i][actY]){
//                             if (exploradas.find({actX+i,actY}) == exploradas.end()){
//                                 frontera.push_back({actX+i,actY});
//                             }
//                         }
//                     }

//                     if (actY+i >= 0 && actY+i < n){    
//                         if (matriz[actX][actY+i]){
//                             if (exploradas.find({actX,actY+i}) == exploradas.end()){
//                                 frontera.push_back({actX,actY+i});
//                             }
//                         }
//                     }
//                 }
//             }
//         }

//         backTracking2(matriz,secuenciaAct);
//     }
// }
