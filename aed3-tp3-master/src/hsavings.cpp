#include<iostream>
#include<utility>
#include "Savings.h"
#include "hauxiliares.h"

using namespace std;

double distanciaTotal(Savings &s, vector< vector< int> > rutas){
    double res = 0;

    for( auto ruta : rutas ){
        res += s.distanciaEntrePuntos( 0, ruta.front() );

        for( int i = 0; i < ruta.size() - 1 ; i++)
            res += s.distanciaEntrePuntos( ruta[i], ruta[i+1] );

        res += s.distanciaEntrePuntos( ruta.back(), 0 );
    }

    return res;
}

int buscame(vector< vector<int> > rutas, int x){
    if (x == 0) return -1;
    for (int i = 0; i < rutas.size(); i++){
        for (int j = 0; j < rutas[i].size(); j++){
            if(x == rutas[i][j]) return i;
        }
    }
}

int main(){
    int n, capacidad;
    cin >> n >> capacidad;
    //while(n != 0 and capacidad != 0){
        vector< tuple<double, double, int> > puntos;
        for (int i = 0; i < n; i++){
            double x, y;
            int demanda;
            cin >> x >> y >> demanda;
            puntos.push_back( make_tuple(x, y, demanda) );
        }
        //high_resolution_clock::time_point t1 = high_resolution_clock::now();
        Savings savings(puntos, capacidad);
        vector< vector<int> > rutas = savings.procesar();
        cout << rutas.size() << endl;
        for(auto ruta : rutas){
            cout << "0" << " ";
            for(auto p : ruta)
                cout << p << " ";
            cout << "0" << endl;
        }
        cout  << distanciaTotal(savings, rutas) << endl;  
        /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout  << n << " " << distanciaTotal(savings, rutas) << " " << time_span.count() << endl;  
        cin >> n >> capacidad;*/
    //}
    return 0;
}