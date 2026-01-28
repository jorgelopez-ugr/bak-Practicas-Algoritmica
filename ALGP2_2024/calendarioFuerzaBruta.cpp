#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> organizaCalendario(int n_par){
    /*
             dia1  dia2  dia3 ...
    equipo1   .     .     .
    equipo2   .     .     .      
    equipo3   .     .     .

      ...

    */

    int nfil = n_par+1;
    int ncol = n_par;

    vector<vector<int>> calendario(nfil,vector<int>(ncol,0));

    calendario[0][0] = 0;

    for (int i = 1 ; i < nfil;i++){
        calendario[i][0] = i;
    }

    for (int i = 1 ; i < ncol;i++){
        calendario[0][i] = i;
    }

    for (int i = 1 ; i < nfil ; i++){ 
        for (int j = 1 ;j < ncol ; j++){ 
            calendario[i][j] = 0;
        }
    }


    for (int i = 1 ; i < nfil ; i++){
        for (int j = 1 ;j < ncol ; j++){
            for (int k = 1 ; k <= n_par ; k++){
                if (k != calendario[i][0]){
                    bool repetido_fila = false;
                    bool repetido_columna = false;

                    for (int l = 1 ; l < ncol && !repetido_fila; l++){
                        if (calendario[i][l] == k){
                            repetido_fila = true;
                        }
                    }

                    if (!repetido_fila){
                        for (int l = 1 ; l < nfil && !repetido_columna; l++){
                            if (calendario[l][j] == k){
                                repetido_columna = true;
                            }
                        }
                    }

                    if (!repetido_fila && !repetido_columna){
                        calendario[i][j] = k;
                    }
                }
            }
        }
    }

    return calendario;
}

int main(){

    int n_par = 8;
    vector<vector<int>> calendario = organizaCalendario(n_par);

    int nfil = n_par+1;
    int ncol = n_par;

    cout << "cada columna representa un dia de campeonato" << endl;
    cout << "el torneo durara los siguientes dias: " << n_par-1 << endl;

    for (int i = 0 ; i < nfil ; i++){
        for (int j = 0 ; j < ncol ; j++){
                if (i != 0 || j != 0){    
                    if (j == 0){
                        cout << "equipo " << calendario[i][j] << " se enfrentará a: " ;
                    }
                    else
                    {
                        cout << calendario[i][j] << " ";
                    }
                }
                
        }

        cout << endl;
    }

}
