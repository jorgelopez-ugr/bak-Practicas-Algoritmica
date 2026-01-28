#include <iostream>
#include <vector>

using namespace std;

int calcularConvenienciaTotal(const vector<vector<int>>& conveniencia, const vector<int>& disposicion){
   int nivel_total = 0;
   int num_invitados = disposicion.size();

   for (int i = 0; i < num_invitados; i++){
      int actual = disposicion[i];
      int dcha = disposicion[(i + 1) % num_invitados]; 
      int izda = disposicion[(i - 1 + num_invitados) % num_invitados];

      nivel_total += conveniencia[actual][izda] + conveniencia[actual][dcha];
   }

   return nivel_total;
}

void disposicionBacktracking(const vector<vector<int>> &conveniencia, vector<bool> &sentados, int num_invitados, vector<int> &disposicion_actual, int &mejor_conveniencia, vector<int> &mejor_disposicion) {
   if (disposicion_actual.size() == num_invitados) {
      int conveniencia_actual = calcularConvenienciaTotal(conveniencia, disposicion_actual);

      if (conveniencia_actual > mejor_conveniencia) {
         mejor_disposicion = disposicion_actual;
         mejor_conveniencia = conveniencia_actual;
      }
      return;
   }
   
   for (int i = 0; i < num_invitados; i++) {
      if (not sentados[i]){
         sentados[i] = true;
         disposicion_actual.push_back(i);
         disposicionBacktracking(conveniencia, sentados, num_invitados, disposicion_actual, mejor_conveniencia, mejor_disposicion);
         disposicion_actual.pop_back();
         sentados[i] = false;
      }
   }
}

int main() {

   // matriz ejemplo
   int num_invitados = 4;
   vector<vector<int>> conveniencia = {
   {0, 20, 15, 10},
   {20, 0, 10, 5},
   {15, 10, 0, 10},
   {10, 5, 10, 0}
   };


   vector<int> mejor_disposicion;
   vector<int> disposicion_actual;
   vector<bool> sentados(num_invitados, false);
   int mejor_conveniencia = 0;

   cout << "------------------------------------------------" << endl;
   disposicionBacktracking(conveniencia, sentados, num_invitados, disposicion_actual, mejor_conveniencia, mejor_disposicion);

   cout << "La disposición de invitados que maximiza el nivel de conveniencia total es:" << endl;
   for (int i = 0; i < num_invitados; i++) {
      cout << "[" << mejor_disposicion[i] << "]" << " ";
   }

   cout << endl;
   cout << "El nivel de conveniencia total es: " << mejor_conveniencia << endl;
}





