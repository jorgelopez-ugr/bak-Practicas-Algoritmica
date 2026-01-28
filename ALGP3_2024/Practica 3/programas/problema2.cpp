#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calcularConvenienciaTotal(const vector<vector<int>>& conveniencia, const vector<int>& disposicion){
   int nivel_total = 0;
   int num_invitados = disposicion.size();

   // suma de los niveles de conveniencia de cada invitado con los dos invitados sentados a su lado
   for (int i = 0; i < num_invitados; i++){
      // invitado 9, num_invitados = 10
      // el invitado de su derecha es el invitado 0
      // 9 + 1 % 10 = 0

      int actual = disposicion[i];
      int dcha = disposicion[(i + 1) % num_invitados]; 
      int izda = disposicion[(i - 1 + num_invitados) % num_invitados];

      nivel_total += conveniencia[actual][izda] + conveniencia[actual][dcha];
      cout << nivel_total << endl;
   }

   return nivel_total;
}

vector<int> disposicionMaxGreedy(const vector<vector<int>>& conveniencia, int num_invitados) {
   vector<int> mejor_disposicion(num_invitados, -1);
   vector<bool> sentado(num_invitados, false);

   mejor_disposicion[0] = 0;
   sentado[0] = true;

   for (int i = 1; i < num_invitados; i++) { 
      int mejor_invitado = -1;
      int mejor_conveniencia = -1;

      for (int j = 0; j < num_invitados; j++) {
         if (!sentado[j]) { 
            int izda = mejor_disposicion[(i - 1 + num_invitados) % num_invitados]; 
            int dcha = mejor_disposicion[(i + 1) % num_invitados];  
            int conveniencia_actual;

            if (dcha == -1){
               conveniencia_actual = conveniencia[izda][j];
            }
            else{
               conveniencia_actual = conveniencia[izda][j] + conveniencia[j][dcha];
            }

            if (conveniencia_actual > mejor_conveniencia) {
               mejor_invitado = j;  
               mejor_conveniencia = conveniencia_actual;  
            }
         }
      }

      mejor_disposicion[i] = mejor_invitado;
      sentado[mejor_invitado] = true;
   }

   return mejor_disposicion;
}

vector<int> disposicionMaxPermutaciones(const vector<vector<int>>& conveniencia) {
   int num_invitados = conveniencia.size();
   vector<int> disposicion(num_invitados, -1);

   for (int i = 0; i < num_invitados; i++) {
      disposicion[i] = i;
   }

   int mejor_nivel_conveniencia_total = 0;
   vector<int> mejor_disposicion;

   do {
      int nivel_conveniencia_total = calcularConvenienciaTotal(conveniencia, disposicion);

      if (nivel_conveniencia_total > mejor_nivel_conveniencia_total) {
         mejor_nivel_conveniencia_total = nivel_conveniencia_total;
         mejor_disposicion = disposicion;
      }
   } while (next_permutation(disposicion.begin(), disposicion.end()));

   return mejor_disposicion;
}

int main() {

   // matriz ejemplo 
   int num_invitados = 4;
   vector<vector<int>> conveniencia = {
      {0, 5, 1, 10},
      {5, 0, 1, 1},
      {1, 1, 0, 5},
      {10, 1, 5, 0}
   };

   //matriz contrajemplo
   // int num_invitados = 10;
   // vector<vector<int>> conveniencia = {
   //  {0, 50, 10, 30, 70, 20, 40, 90, 80, 60},
   //  {50, 0, 20, 40, 30, 60, 70, 80, 90, 10},
   //  {10, 20, 0, 50, 60, 70, 80, 90, 40, 30},
   //  {30, 40, 50, 0, 20, 80, 90, 70, 60, 10},
   //  {70, 30, 60, 20, 0, 10, 40, 50, 90, 80},
   //  {20, 60, 70, 80, 10, 0, 50, 30, 40, 90},
   //  {40, 70, 80, 90, 40, 50, 0, 60, 70, 20},
   //  {90, 80, 90, 70, 50, 30, 60, 0, 10, 40},
   //  {80, 90, 40, 60, 90, 40, 70, 10, 0, 50},
   //  {60, 10, 30, 10, 80, 90, 20, 40, 50, 0}
   // };
   
   /**
    * Para probar el algoritmo Voraz --> Matriz 4 invitados y disposicionMaxGreedy
    * 
    * Para probar el Contraejemplo --> Matriz 10 invitados y
    * en disposicionMaxGreedy :
    *    vector<int> mejor_disposicion(num_invitados, -1);
    *    vector<bool> sentado(num_invitados, false);
    *     
    *    mejor_disposicion[0] = 2;  -> IMPORTANTE
    *    sentado[2] = true; -> IMPORTANTE
    */
   
   // Algoritmo Greedy
   vector<int> disposicion = disposicionMaxGreedy(conveniencia, num_invitados);

   // Algoritmo Fuerza Bruta 
   //vector<int> disposicion = disposicionMaxPermutaciones(conveniencia);

   int nivel_conveniencia_total = calcularConvenienciaTotal(conveniencia, disposicion);

   cout << "La disposición de invitados que maximiza el nivel de conveniencia total es:" << endl;
   for (int i = 0; i < num_invitados; ++i) {
      cout << disposicion[i] << " ";
   }
   cout << endl;
   cout << "El nivel de conveniencia total es: " << nivel_conveniencia_total << endl;

   return 0;
}
