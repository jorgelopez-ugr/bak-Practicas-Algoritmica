#include <iostream>
#include <vector>

using namespace std;

vector<int> gasolinerasGreedy(int kmTotalRuta, vector<int> gasolineras , int autonomiaMax){
	vector<int> solucion;
	int autonomiaAct = autonomiaMax;
	int gasCounter = 0;
	bool quedoSinAutonomia = false;
	
	for (int i = 1 ; i <= kmTotalRuta && !quedoSinAutonomia ; i++){ //cada uno de los km de la ruta
		
		if (i == gasolineras[gasCounter]){ //es decir esta pasando por delante de una gasolinera
			
			if (gasCounter == gasolineras.size()-1){ //es es la ultima
				if (i+autonomiaAct < kmTotalRuta){ //entonces que entre 
					solucion.push_back(gasolineras[gasolineras.size()-1]);
					autonomiaAct = autonomiaMax;
				}
			}
			else{ //en caso de que no sea la ultima
				if (i+autonomiaAct < gasolineras[gasCounter+1]){ //entonces que entre 
					solucion.push_back(gasolineras[gasCounter]);
					autonomiaAct = autonomiaMax;
				}
			}
		
			
			gasCounter++;
		}
		
		autonomiaAct--;	
		
		if (autonomiaAct == 0 && i != kmTotalRuta){
			quedoSinAutonomia = true;
			cout << "quedo sin autonomia" << endl;
			solucion.clear();
		}	
	 }
	
	return solucion;
}

int main(){
	int kmTotal = 50;
    vector<int> gasolineras = {5,10,15,20,25,30,35,40,45};
    int autonomia = 6;

	cout << "las gasolineras estan en: ";

	for (int i = 0 ; i < gasolineras.size() ; i++){
		cout << gasolineras[i] << " ";
	}
	
	cout << endl;

    vector<int> dondeParara = gasolinerasGreedy(kmTotal,gasolineras,autonomia);
    
    if (dondeParara.empty()){
        cout << "no tiene solucion o llego sin tener que parar a repostar" << endl;
    }
    else
    {
        cout << "parara en las siguientes gasolineras: " << endl;

        for (int i = 0 ; i < dondeParara.size() ;i++){
            cout << "gasolinera :" << dondeParara[i] << endl;
        }
    }
}
