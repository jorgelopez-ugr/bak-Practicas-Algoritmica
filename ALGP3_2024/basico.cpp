#include <iostream>
#include <string>

#include <vector>

using namespace std;

vector<int> paradas(int kmRuta, vector<int> gasolineras, int autonomiaMax){
    int kmActual = 0;
    int autonomia = autonomiaMax;
    vector<int> gasDondePara;
	int llegaHasta;
	bool encontrada;
	bool lastAdded = false;
	bool firstAdded = false;

    while (kmActual < kmRuta && autonomia != 0)
    {
        llegaHasta = kmActual + autonomia; //hasta donde llegaria en funcion del km en el que esta y el deposito que le queda

		kmActual++; // avanza 1 km
        autonomia--; // baja 1 km de autonomia

		encontrada = false;

        if (llegaHasta < kmRuta){ //mientras no pueda llegar al final con lo que lleva
            for (int i = 0 ; i < gasolineras.size() && !encontrada ; i++){
            	if (llegaHasta <= gasolineras[i]){
            		
            		if (i == 0 && !firstAdded){
                    	gasDondePara.push_back(gasolineras[0]);
                    	autonomia = autonomiaMax;
                    	kmActual = gasolineras[0];
                    	
                    	encontrada = true;
                    	firstAdded = true;
                	}
                	else if (i == gasolineras.size()-1 && !lastAdded){
                		//quiere decir que es la ultima gasolinera, necesita un trato especial.
                		//si con la gasolina que lleve no llega al final que pare en la ultima si o si y lo intente
    					gasDondePara.push_back(gasolineras[i]);
            			autonomia = autonomiaMax;
            			kmActual = gasolineras[i];
            			
            			encontrada = true;
            			lastAdded = true;
                	}
                	else{
                    	gasDondePara.push_back(gasolineras[i-1]);
                    	autonomia = autonomiaMax;
                    	kmActual = gasolineras[i-1];
                    	
                    	encontrada = true;
                	}               
                }
            }
        }
    }
    
    if (kmActual != kmRuta){
    	gasDondePara.clear();
    }
    
    return gasDondePara;
}

int main(){
    int kmTotal = 50;
    vector<int> gasolineras = {1,11,24,34,36,39,44,47,48};
    int autonomia = 10;

    vector<int> dondeParara = paradas(kmTotal,gasolineras,autonomia);
    
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
