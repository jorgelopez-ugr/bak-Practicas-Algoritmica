
#include <vector>
#include <chrono>
#include <ostream>
#include <cstdlib> // Para usar srand y rand
#include <iostream>
#include <fstream> // Para usar ficheros


using namespace std;

// Función para intercambiar dos elementos
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función para dividir el array y hacer el particionamiento
int partition ( int * v , int low , int high ) {
	int pivot = v [ high ];
	int i = low ; int j = high-1 ;
	while ( i <= j ) {
		while ( i <= j && v [i] < pivot ) {
			i ++;
		}
		while ( i <= j && v [j] > pivot ) {
			j --;
		}
		if ( i <= j ) {
			swap( v [i ++] , v [j--]) ;
		}
	}
	if ( low < j ) {
		swap ( v [low] , v [j]) ;
	}

	return j+1;
}
// Función principal de QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Obtener el índice de partición
        int pi = partition(arr, low, high);

        // Ordenar los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función de utilidad para imprimir un array
// void printArray(int & arr, int n) {
//     for (int i = 0; i < n; i++)
//         cout << arr[i] << " ";
//     cout << endl;
// }

// int main() {
//     vector<int> arr = {10, 7, 8, 9, 1, 5}
//     int n = arr.size();
//     cout << "Array original:" << endl;
//     printArray(arr);

//     quickSort(arr, 0, n - 1);

//     cout << "Array ordenado:" << endl;
//     printArray(arr);
//     return 0;
// }

int main(int argc, char *argv[]) {
	
	int *v;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			// v[i]= rand()%n;
			v[i] = n - i;
		
		cerr << "Ejecutando QuickSort para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		quickSort(v,0,n-1); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
