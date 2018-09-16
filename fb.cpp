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
int tiempo;
int resMin = -1;



int sumaDeVec(vector <int>& entry){
	int i = 0;
	int res = 0;
	while(i < entry.size()){
		res = res + entry[i];
		i++;
	}
	//cout << "El vector suma " << res << endl;
	return res;
}

void fuerzaBruta(int a,int n, int v, vector <int>& valores, vector <int>& resultado){
	    if( a == n)
	    {
	    	if(resMin == -1 && sumaDeVec(resultado) == v) resMin = resultado.size();
	    	if(sumaDeVec(resultado) == v && sumaDeVec(resultado) < resMin) resMin = resultado.size();
	    }
	    else
	    {
			resultado.push_back(valores[a]);
			fuerzaBruta(a+1, n, v, valores, resultado); // recursion con el elemento
			resultado.pop_back();
			fuerzaBruta(a+1,n, v, valores, resultado); // recursion sin el elemento
		}    
}


int main (){
	int n;
	int v;
	
	cin >> n;
	cin >> v;
	if (n == 0) return -1;
	if (v == 0) return 0;

	while ( n!= 0 && v != 0){

		int aux = n;
		vector <int> valores;
		vector <int> resultado;
		while (aux > 0){
			int aux2;
			cin >> aux2;
			valores.push_back( aux2 );
			aux--;
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		fuerzaBruta(0, n, v, valores, resultado);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	  	//cout << time_span.count() << endl; 

		//cout << "El res es " << resMin << endl;

		cout << resMin << endl;

		resMin = -1;
		cin >> n;
		cin >> v;
	}
	return 0;
}

