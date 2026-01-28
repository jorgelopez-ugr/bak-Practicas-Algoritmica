#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// a la hora de devolver el plan a realizar
// lo devolvemos haciendo referencia desde la base de la montaña
// es decir, la ultima fila de la matriz montaña , quedándonos con el valor de la 
// columna en la que se encuentra el paso a dar.

// la función escalada devuelve el coste mínimo para llegar a la cima de la montaña

void printEscalada(const vector<vector<int>> &montaña, const vector<int> &camino){
   int filas = montaña.size();
   int cols = montaña[0].size();

   vector<vector<char>> mostrar(filas, vector<char> (cols, ' '));

   // copiamos literalmente la matriz mmontaña

   for (int i = 0; i < filas; i++){
      for (int j = 0; j < cols; j++){
         mostrar[i][j] = montaña[i][j] + '0';
      }
   }
   
   //pintamos el camino

   for (int i = 0; i < camino.size(); i++){
      mostrar[i][camino[i]] = 'X';
   }
   
   // mostramos la matriz

   for (int i = 0; i < filas; i++){
      for (int j = 0; j < cols; j++){
         cout << mostrar[i][j] << " ";
      }

      cout << endl;
   }
}


int escaladaCosteMinimo(const vector<vector<int>> &montaña){
   if (montaña.size() == 0) {
      return 0;
   }
      
   vector<vector<int>> coste(montaña.size(), vector<int>(montaña[0].size(), INT_MAX));

   int filas = montaña.size();
   int cols = montaña[0].size();

   // identificacion del caso base:

   for (int col = 0; col < cols; col++)
      coste[filas - 1][col] = montaña[filas - 1][col];


   // movimientos posibles:
   // hacia arriba desde abajo [i-1][j]
   // diagonal izq [i-1][j-1]
   // diagonal dcha [i-1][j+1]

   for (int fil = filas - 2; fil >= 0;  fil--){
      for (int col = 0; col < cols; col++){
         int coste_casilla = montaña[fil][col];

         // comprobamos el coste para cada uno de los movimientos posibles:
         
         // movimiento ascendente:

         int coste_movimiento = coste[fil + 1][col];

         // diagonal izquierda

         if (col > 0)
            coste_movimiento = min(coste_movimiento, coste[fil + 1][col - 1]);
         
         // diagonal derecha

         if (col < cols - 1)
            coste_movimiento = min(coste_movimiento, coste[fil + 1][col + 1]);

         // asignamos el menor coste

         coste[fil][col] = coste_casilla + coste_movimiento;
      }
   }

   int coste_minimo = INT_MAX;
   
   for (int col = 0; col < cols; col++){
      if (coste[0][col] < coste_minimo)
         coste_minimo = coste[0][col];
   }

   return coste_minimo;
}

// para recuperar la solucion

int escaladaCosteMinimoConPlan(const vector<vector<int>> &montaña, vector<int> &path){
   if (montaña.size() == 0) {
      return 0;
   }
      
   vector<vector<int>> coste(montaña.size(), vector<int>(montaña[0].size(), INT_MAX));
   vector<vector<int>> camino(montaña.size(), vector<int>(montaña[0].size(), -1));

   int filas = montaña.size();
   int cols = montaña[0].size();

   // identificacion del caso base:

   for (int col = 0; col < cols; col++)
      coste[filas - 1][col] = montaña[filas - 1][col];


   // movimientos posibles:
   // hacia arriba desde abajo [i-1][j]
   // diagonal izq [i-1][j-1]
   // diagonal dcha [i-1][j+1]

   for (int fil = filas - 2; fil >= 0;  fil--){
      for (int col = 0; col < cols; col++){
         int coste_casilla = montaña[fil][col];
         int posi_min = -1;

         // comprobamos el coste para cada uno de los movimientos posibles:
         
         // movimiento ascendente:

         int coste_movimiento = coste[fil + 1][col];
         posi_min = col;

         // diagonal izquierda

         if (col > 0){
            coste_movimiento = min(coste_movimiento, coste[fil + 1][col - 1]);
            if (coste_movimiento == coste[fil + 1][col - 1]) posi_min = col - 1;
         }

         // diagonal derecha

         if (col < cols - 1){
            coste_movimiento = min(coste_movimiento, coste[fil + 1][col + 1]);
            if (coste_movimiento == coste[fil + 1][col + 1]) posi_min = col + 1;
         }
            
         // asignamos el menor coste

         coste[fil][col] = coste_casilla + coste_movimiento;
         camino[fil][col] = posi_min;      
      }
   }

   int coste_minimo = INT_MAX;
   int posi_minima = -1;
   
   for (int col = 0; col < cols; col++){
      if (coste[0][col] < coste_minimo){
         coste_minimo = coste[0][col];
         posi_minima = col;
      }
   }

   // recuperamos el plan
   // comenzamos insertando desde la cima los valores
   
   for (int i = 0; i < filas; i++){
      path.push_back(posi_minima);
      posi_minima = camino[i][posi_minima];
   }

   return coste_minimo;
}



int main() {
   vector<vector<int>> montaña = {
      {2, 8, 9, 5, 8},
      {4, 4, 6, 2, 3},
      {5, 7, 5, 6, 1},
      {3, 2, 5, 4, 8}
   };

   // vector<vector<int>> montaña = {
   //    {8, 9, 3},
   //    {4, 6, 7},
   //    {3, 5, 8}
   // };

   vector<int> plan;
   int resultado = escaladaCosteMinimoConPlan(montaña, plan);

   cout << "El coste mínimo para llegar a la cima de la Pixel Mountain es: " << resultado << endl;
   cout << "El camino de menor dificultad: ";
   for (int posi : plan) cout << posi << " ";

   cout << endl;
   cout << endl;
   
   cout << "La matriz final es: " << endl;
   printEscalada(montaña, plan);



   cout << endl;
}


