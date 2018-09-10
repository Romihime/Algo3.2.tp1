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
/*
int tiempo;*
*/
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


void backtracking(int a,int n, int v, vector <int>& valores, vector <int>& resultado){
	if (resultado.size() < resMin) // poda de mejor resultado ya encontrado
	{
		int c = sumaDeVec(resultado);
	    if( c == v)
	    {
	    	if(resMin == -1) resMin = resultado.size();
			if(resultado.size() < resMin) resMin = resultado.size();
	    }
	    else
	    {
	    	if (a < n){
	    		if(c + valores[a] <= v) // poda de no agrego algo que ya se pasa de v
	    		{
				resultado.push_back(valores[a]);
				backtracking(a+1, n, v, valores, resultado); // recursion con el elemento
				resultado.pop_back();
				}
				backtracking(a+1,n, v, valores, resultado); // recursion sin el elemento
			}
		}
	}    
}



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
	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	backtracking(0, n, v, valores, resultado);
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();

	//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  	//cout << time_span.count() << endl; 

	cout << "El res es " << resMin << endl;
	return 0;
}

