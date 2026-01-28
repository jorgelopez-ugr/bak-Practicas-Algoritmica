#include <iostream>
#include <vector>

using namespace std;

void combinaSoluciones(vector<vector<int>> &calendario, int valEqInf, int valEqSup,
                              int valDiaInf, int valDiaSup, int eqIni) {

    for (int j = valDiaInf ; j <= valDiaSup ; j++) {
        calendario[valEqInf][j] = eqIni + j-valDiaInf;
    }

    for (int i = valEqInf + 1 ; i <= valEqSup ; i++) {

        calendario[i][valDiaInf] = calendario[i-1][valDiaSup];
        
        for (int j = valDiaInf + 1 ; j <= valDiaSup ; j++) {
            calendario[i][j] = calendario[i-1][j-1];
        }
    }
}

void organizaCampeonato(vector<vector<int>> &calendario, int prim, int ult) {
    int ptoMedio;
    if (ult-prim == 1) {

        calendario[prim][1] = ult;
        calendario[ult][1] = prim;
    } else {
        ptoMedio = (prim + ult)/2;
        
        organizaCampeonato(calendario, prim, ptoMedio);
        organizaCampeonato(calendario, ptoMedio + 1, ult);
        cout << "intermedio" << endl;
        for (int i = 0 ; i < 8+1 ; i++){
        	for (int j = 0 ; j < 8 ; j++){
                if (i != 0 || j != 0){    
                    if (j == 0){
                        cout << "equipo " << calendario[i][j] << "-->";
                    }
                    else if (i == 0)
                    {
                        cout << "  Dia:" << calendario[i][j] << "  ";
                    }
                    else 
                    {
                        cout << calendario[i][j] << " ";
                    }
                }
                
        	}

        cout << endl;
        }
        
        combinaSoluciones(calendario, prim, ptoMedio, ptoMedio-prim + 1, ult-prim, ptoMedio + 1);
        combinaSoluciones(calendario, ptoMedio + 1, ult, ptoMedio-prim + 1, ult-prim, prim);
        
        cout << "el de fuera" << endl;
        for (int i = 0 ; i < 8+1 ; i++){
        	for (int j = 0 ; j < 8 ; j++){
                if (i != 0 || j != 0){    
                    if (j == 0){
                        cout << "equipo " << calendario[i][j] << "-->";
                    }
                    else if (i == 0)
                    {
                        cout << "  Dia:" << calendario[i][j] << "  ";
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
}


int main(){
    int n = 8;
    vector<vector<int>> calendario(n+1,vector<int>(n,0));

    organizaCampeonato(calendario, 1, n);
    cout << "Tabla formada:\n";

    for (int i = 1 ; i < n+1;i++){
        calendario[i][0] = i;
    }

    for (int i = 1 ; i < n;i++){
        calendario[0][i] = i;
    }

    for (int i = 0 ; i < n+1 ; i++){
        for (int j = 0 ; j < n ; j++){
                if (i != 0 || j != 0){    
                    if (j == 0){
                        cout << "equipo " << calendario[i][j] << "-->";
                    }
                    else if (i == 0)
                    {
                        cout << "  Dia:" << calendario[i][j] << "  ";
                    }
                    else 
                    {
                        cout << calendario[i][j] << " ";
                    }
                }
                
        }

        cout << endl;
    }

    return 0;
}
