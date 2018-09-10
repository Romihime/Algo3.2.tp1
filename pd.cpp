#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <stdio.h> 
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define INF 999

/*
int tiempo;*
*/


int main (){
	int n;
	int v;
	vector <int> valores;
	vector <int> resultado;
	
	cin >> n;
	cin >> v;
	int aux = n;
	if (n == 0) return -1;
	if (v == 0) return 0;

	while (aux > 0){
		int aux2;
		cin >> aux2;
		valores.push_back( aux2 );
		aux--;
	}

	int f[n+1][v+1];
	f[0][0] = 0;

	for (int i = 1; i <= v; i++){
		f[0][i] = INF;
	}



	for (int i = 1; i <= n; i++){ // bottom up

		for (int t = 0; t <= v; t++){

			if (valores[i-1] > v){

				f[i][t] = f[i-1][t];
			}
			else{

				f[i][t] = min(f[i-1][t], 1 + f[i-1][t - valores[i-1]]);
			}
		}
	}

	for(int i =0; i <=n;i++){
		for(int j= 0; j<=v; j++ ){
			cout << f[i][j] << " "; // esto es para chekear que hay dentro de la matriz
		}
		cout << endl;
	}

	if (f[n][v] == INF){
		cout << "El res es " << -1 << endl;
		return -1; // si la ultima posicion de la matriz no alcanza a tener un valor menor a infinito, entonces no existe res valido
	} 

	cout << "El res es " << f[n][v] << endl;
	return f[n][v];




	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();

	//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  	//cout << time_span.count() << endl; 
}

