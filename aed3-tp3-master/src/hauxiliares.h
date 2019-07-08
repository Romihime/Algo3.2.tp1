#ifndef TP3__H
#define TP3__H


#include <vector>
#include <map>
#include <utility>
#include <numeric>
#include <list>
#include <limits>
#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>
#include <queue>
#include <algorithm>
#include <random>
#include "Savings.h"

using namespace std;
using namespace std::chrono;

#define INFINITO std::numeric_limits<int>::max()
#define PI 3.14159265

struct punto {
    int id;
    float x;
    float y;
    int d;
    float distancia;
    double rad = 0;
    double ang = 0;
    int ruta;
    bool visitado = false;
} ;


//AUXILIARES DE HEURISTICAS--------------------------------------------------------------------------------------------------------

punto damePunto(int x, vector< punto> & puntos){ //O(n)
    punto res;
    for(int i = 0; i < puntos.size(); i++){
        if( x == puntos[i].id) res = puntos[i];
    }
    return res;
}

float sumaDemanda(vector <int>& ruta, vector< punto> & puntos){ //O(n)

    float demanda = 0; 

    for(int k = 0; k < ruta.size(); k++){
        demanda = demanda + damePunto(ruta[k],puntos).d;
    }
    return demanda;
}

float suma(vector <int>& ruta, vector< vector<float> >& matriz){ //O(n)

    float distancia1 = 0; 

    for(int k = 0; k < ruta.size()-1; k++){
        distancia1 = distancia1 + matriz[ruta[k]][ruta[k+1]];
    }
    return distancia1;
}

float distTotal(vector <vector <int> >& rutas, vector< vector<float> >& matriz){ //O(n)

    float res = 0; 
    for(int i = 0; i < rutas.size(); i++){
        res = res + suma(rutas[i],matriz);
    }
    return res;
}

bool NotodosVisitados( vector <punto>& puntos){ //O(n)

    for(int i = 0; i < puntos.size(); i++){
        if (puntos[i].visitado == false) return true;
    }
    return false;
}

int minimin(vector< vector<float> >& matriz, vector < punto >& puntos, int x, int n){ //O(n)
    float min = INFINITO;
    int res = 0;
    for(int i = 1; i < n; i++){
        if(i != x and (puntos[i].visitado == false) and matriz[x][i] <= min){
            min = matriz[x][i];
            res = i;
        }
    }
    return res;
}

int miniminDem(vector< vector<float> >& matriz, vector < punto >&  puntos, int x, int n){  //O(n)
    float min = INFINITO;
    int res = 0;
    for(int i = 1; i < n; i++){
        if(i != x and (puntos[i].visitado == false) and matriz[x][i]/puntos[i].d <= min){
            min = matriz[x][i]/puntos[i].d;
            res = i;
        }
    }
    return res;
}


bool compAng (punto i,punto j) { return (i.ang<j.ang); }
bool compRad (punto i,punto j) { return (i.rad<j.rad); }
bool la (punto i,punto j) { return (i.id<j.id); }

//PRINTS--------------------------------------------------------------------------------------------------------

void printSol(int camiones, vector< vector<int> >& rutas, float total){
    cout << camiones << endl;
    for(int i = 0; i < rutas.size(); i++){
        for(int k = 0; k < rutas[i].size(); k++){
            cout << rutas[i][k] << " ";
        }
        cout << endl;
    }
    cout << total << endl;
}

void printPuntos( vector<punto> & puntos){
    for(int i = 0; i < puntos.size(); i++){
        cout << puntos[i].id << " " << puntos[i].x << " " << puntos[i].y << " " << puntos[i].d  << " " << puntos[i].ruta << endl;
    }
}

void printParaGrafico(int camiones, vector< vector<int> >& rutas, int n, vector<punto>&  puntos){
    cout << camiones << endl;
    for(int i = 0; i < rutas.size(); i++){
        for(int k = 0; k < rutas[i].size(); k++){
            cout << rutas[i][k] << " ";
        }
        cout << endl;
    }
    cout << n << endl;
    for(int i = 0; i < puntos.size(); i++){
        cout << puntos[i].x << " " << puntos[i].y <<  endl;
    }
}

void printRutas(vector< vector<int> > & rutas ){
    for(int i = 0; i < rutas.size(); i++){
        for(int k = 0; k < rutas[i].size(); k++){
            cout << rutas[i][k] << " ";
        }
        cout << endl;
    }
}

//HEURISTICAS--------------------------------------------------------------------------------------------------------


vector <vector <int> > GolosoDis(int n, int demanda, vector <punto>& puntos, vector< vector<float> >& matriz){
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int contador = 0;
    int iterador = 0;
    int actual = 0;
    int clientes = 0;
    vector <vector <int> > rutas;
    vector <int> ruta;
    rutas.push_back(ruta);
    rutas[iterador].push_back(0);

    while(clientes < n){ // esto separa en rutas segun distancia //O(n.n)
        actual = minimin(matriz,puntos,actual,n);
        if(contador + puntos[actual].d  <= demanda){ //O(n)
            puntos[actual].ruta = iterador;
            puntos[actual].visitado = true;
            rutas[iterador].push_back(actual);
            contador = contador + puntos[actual].d;
        } else{
            rutas[iterador].push_back(0);
            iterador++;
            vector <int> ruta;
            rutas.push_back(ruta);
            rutas[iterador].push_back(0);
            puntos[actual].ruta = iterador;
            puntos[actual].visitado = true;
            rutas[iterador].push_back(actual);
            contador = 0 + puntos[actual].d;
        }
        clientes++;
    }
    /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout  << n << " " << distTotal(rutas, matriz) << " " << time_span.count() << endl; */
    return rutas;    
}

vector <vector <int> > GolosoDem(int n, int demanda, vector <punto>& puntos, vector< vector<float> >& matriz){
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int contador = 0;
    int iterador = 0;
    int actual = 0;
    int clientes = 0;
    vector <vector <int> > rutas;
    vector <int> ruta;
    rutas.push_back(ruta);
    rutas[iterador].push_back(0);

    while(clientes < n){ // esto separa en rutas segun distancia //O(n.n)
        actual = miniminDem(matriz,puntos,actual,n);
        if(contador + puntos[actual].d  <= demanda){ //O(n)
            puntos[actual].ruta = iterador;
            puntos[actual].visitado = true;
            rutas[iterador].push_back(actual);
            contador = contador + puntos[actual].d;
        } else{
            rutas[iterador].push_back(0);
            iterador++;
            vector <int> ruta;
            rutas.push_back(ruta);
            rutas[iterador].push_back(0);
            puntos[actual].ruta = iterador;
            puntos[actual].visitado = true;
            rutas[iterador].push_back(actual);
            contador = 0 + puntos[actual].d;
        }
        clientes++;
    }
    /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);*/
    //cout  << n << " " << distTotal(rutas, matriz) << " " << time_span.count() << endl; 
    return rutas;    
}

vector <vector <int> > ClustSweep(int n, int demanda, vector <punto>& puntos, vector< vector<float> >& matriz){
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    vector<punto> _puntos = puntos;
    sort (puntos.begin()+1, puntos.end(), compAng);

    int contador = 0;
    int iterador = 0;
    vector <vector <int> > rutas;
    vector <int> ruta;
    rutas.push_back(ruta);
    rutas[iterador].push_back(0);

    for(int i = 1; i < n; i++){ // esto separa en rutas segun barrido en angulo y por capacidad //O(n)
        if(contador + puntos[i].d  <= demanda){
            _puntos[puntos[i].id].ruta = iterador;
            rutas[iterador].push_back(puntos[i].id);
            contador = contador + puntos[i].d;
        } else{
            rutas[iterador].push_back(0);
            iterador++;
            vector <int> ruta;
            rutas.push_back(ruta);
            rutas[iterador].push_back(0);
            _puntos[puntos[i].id].ruta = iterador;
            rutas[iterador].push_back(puntos[i].id);
            contador = 0 + puntos[i].d;
        }
        if(i == n-1) rutas[iterador].push_back(0);
    }

    int cantDeMioncas = iterador+1;

    for(int i = 0; i < cantDeMioncas; i++){
   
        float distanciabase = 0;
        
        for(int k = 0; k < rutas[i].size()-1; k++){
            distanciabase = distanciabase + matriz[rutas[i][k]][rutas[i][k+1]];
        }

        for(int l = 1; l < rutas[i].size()-1; l++){ //O(n.n)
            for(int j = 1; j < rutas[i].size()-1; j++){
                if (l != j){
                    vector <int> rutaAux = rutas[i];

                    swap(rutaAux[l],rutaAux[j]);

                    float distancia = suma(rutaAux, matriz);

                    if (distancia < distanciabase){
                        distanciabase = distancia;
                        rutas[i] = rutaAux;
                    }
                }
            } 
        }
    }
    puntos = _puntos;
    /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout  << n << " " << distTotal(rutas, matriz) << " " << time_span.count() << endl; */ 
    return rutas;
}

vector <vector <int> > ClustNoSweep(int n, int demanda, vector <punto>& puntos, vector< vector<float> >& matriz){
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    vector<punto> _puntos = puntos;
    sort (puntos.begin()+1, puntos.end(), compRad);

    int contador = 0;
    int iterador = 0;
    vector <vector <int> > rutas;
    vector <int> ruta;
    rutas.push_back(ruta);
    rutas[iterador].push_back(0);

    for(int i = 1; i < n; i++){ // esto separa en rutas segun barrido en angulo y por capacidad //O(n)
        if(contador + puntos[i].d  <= demanda){
            _puntos[puntos[i].id].ruta = iterador;
            rutas[iterador].push_back(puntos[i].id);
            contador = contador + puntos[i].d;
        } else{
            rutas[iterador].push_back(0);
            iterador++;
            vector <int> ruta;
            rutas.push_back(ruta);
            rutas[iterador].push_back(0);
            _puntos[puntos[i].id].ruta = iterador;
            rutas[iterador].push_back(puntos[i].id);
            contador = 0 + puntos[i].d;
        }
        if(i == n-1) rutas[iterador].push_back(0);
    }

    int cantDeMioncas = iterador+1;

    for(int i = 0; i < cantDeMioncas; i++){
   
        float distanciabase = 0;
        
        for(int k = 0; k < rutas[i].size()-1; k++){
            distanciabase = distanciabase + matriz[rutas[i][k]][rutas[i][k+1]];
        }

        for(int l = 1; l < rutas[i].size()-1; l++){ //O(n.n)
            for(int j = 1; j < rutas[i].size()-1; j++){
                if (l != j){
                    vector <int> rutaAux = rutas[i];

                    swap(rutaAux[l],rutaAux[j]);

                    float distancia = suma(rutaAux, matriz);

                    if (distancia < distanciabase){
                        distanciabase = distancia;
                        rutas[i] = rutaAux;
                    }
                }
            } 
        }
    }
    puntos = _puntos;
    /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout  << n << " " << distTotal(rutas, matriz) << " " << time_span.count() << endl;  */
    return rutas;
}

vector< vector<int> > SavingsAnn(int n, int demandita, vector <punto>& puntitos){
    
    int capacidad = demandita;
    vector< tuple<double, double, int> > puntos;
    for (int i = 0; i < n; i++){
        double x, y;
        int demanda;
        puntos.push_back( make_tuple(puntitos[i].x, puntitos[i].y, puntitos[i].d) );
    }
    Savings savings(puntos, capacidad);
    vector< vector<int> > rutas = savings.procesar();

    for(int i = 0; i < rutas.size(); i++){
        vector<int> ruta;
        ruta.push_back(0);
        for(int j = 0; j < rutas[i].size(); j++){
            ruta.push_back(rutas[i][j]);
        }
        ruta.push_back(0);
        rutas[i] = ruta;
    }

    for (int i = 0; i < rutas.size(); i++){
        for (int j = 0; j < rutas[i].size(); j++){
            puntitos[damePunto(rutas[i][j], puntitos).id].ruta = i;
        }
    }
    return rutas;
}

//ANNEALING AUXILIARES--------------------------------------------------------------------------------------------------------

bool sePuedeInsertar(int A, int rutaElegida, vector <vector <int>>&  rutas, vector < punto >& puntos, int capacidad){ //O(n)
    int aux1 = sumaDemanda(rutas[rutaElegida], puntos) + puntos[A].d ;
    if (aux1 > capacidad ){
        return false;
    }
    return true;
}


bool sePuedeHacerSwap(int A, int B, vector <vector <int>> & rutas, vector< vector<float> > & matriz, vector < punto >& puntos, int capacidad){ //O(n)
    int aux1 = sumaDemanda(rutas[puntos[A].ruta], puntos) - puntos[A].d + puntos[B].d;
    int aux2 = sumaDemanda(rutas[puntos[B].ruta], puntos) - puntos[B].d + puntos[A].d;
    if (aux1 > capacidad || aux2 > capacidad){
        return false;
    }
    return true;
}

bool comp (punto i,punto j) { return (i.distancia < j.distancia); } //O(1)

int dameUnoCercano(int A, int n, vector < punto >& puntos, vector< vector<float> >& matriz){ // O(n.log(n))
    int B = rand() % ( (int) ((n/10)-1)) + 1;
    while( A == B) B = rand() % ( (int) ((n/2)-1)) + 1;
    auto begin = puntos.begin();
    begin++;
    vector <punto> puntosCopia(begin, puntos.end() );

    for(int i = 0; i < n-1; i++){ //O(n)
        puntosCopia[i].distancia = matriz[i+1][A];
    }

    sort (puntosCopia.begin(), puntosCopia.end(), comp); // O(n.log(n))
    return (puntosCopia[B]).id;
}

int buscarIndice(int A, vector <vector <int>> & rutas){ //O(n.n)
    int res = -1;
    for( auto ruta : rutas ){
        for( int i = 0; i < ruta.size(); i++ ){
            if( A == ruta[i] )
                res = i;
        }   
    }
    return res;
}

void arreglarPuntos(vector < punto >& puntos, int indiceRutaABorrar){ //O(n)
    for( int i = 0; i < puntos.size(); i++ ){
        if( puntos[i].ruta > indiceRutaABorrar){
             puntos[i].ruta--;
        }
    }   

}

void annealing(vector <vector <int> > rutas, vector< vector<float> > matriz, vector < punto > puntos, int n, int capacidad){

    //for(float k = 0.000001; k > 0.0000001; k = k/1.1){ // esto es para un experimento
        //high_resolution_clock::time_point t1 = high_resolution_clock::now();
        srand (time(NULL));
        int iterador = 0;
        float Tmax = 500;
        float k = 0.001;
        float TempActual = Tmax;
        float EnergiaInit = distTotal(rutas, matriz);

        vector <vector <int>> rutasSol(rutas.size());
        rutasSol = rutas;
        vector < punto >  puntosSol = puntos;
        vector < punto >  puntosSinModificar = puntos;
        float EnergiaMin = distTotal(rutas, matriz);

        vector < vector < int > > rutasTemp;
        vector < punto >  puntosTemp;

        while (TempActual > 0){
            rutasTemp = rutas;
            puntosTemp = puntos;
            int d = rand() % 10;
            if (d >= 5){

                int A = rand() % (n-1) + 1;
                int B = dameUnoCercano(A, n, puntos, matriz);
                int j = 0;
                while (! sePuedeHacerSwap(A, B, rutas, matriz, puntos, capacidad) and j < 10){ //O(n)
                    A = rand() % (n-1) + 1;
                    B = dameUnoCercano(A, n, puntos, matriz); // O(n.log(n))
                    j++;
                }
                if (j < 10){
                    swap(rutas[puntos[A].ruta][buscarIndice( A, rutas)],rutas[puntos[B].ruta][buscarIndice( B, rutas)]); // O(n)

                    int aux = puntos[B].ruta;
                    puntos[B].ruta = puntos[A].ruta;
                    puntos[A].ruta = aux;
                }
            }else{

                int A = rand() % (n-1) + 1;
                int rutaElegida = rand() % rutas.size();

                while ( rutaElegida == puntos[A].ruta && rutas.size() != 1){
                    rutaElegida = rand() % rutas.size();
                }

                int i = 0;
                while ( !sePuedeInsertar(A,rutaElegida,rutas,puntos,capacidad) and i < 10){ //O(n)
                    A = rand() % (n-1) + 1;
                    rutaElegida = rand() % rutas.size();    
                    while ( rutaElegida == puntos[A].ruta){
                        rutaElegida = rand() % rutas.size();
                    }
                    i++;
                }

                if (i < 10){
                    rutas[rutaElegida][rutas[rutaElegida].size()-1] = A;
                    rutas[rutaElegida].push_back(0);

                    int aux = rutas[puntos[A].ruta].size();
                    int indiceRutaABorrar = puntos[A].ruta;
                    vector <int> copia;
                    for(int i = 0; i < aux; i++){ //O(n)
                        if( rutas[puntos[A].ruta][i] != A ){
                            copia.push_back(rutas[puntos[A].ruta][i]);
                        } 
                    }

                    rutas[puntos[A].ruta] = copia; //O(n)
                    puntos[A].ruta = rutaElegida;

                    if (aux-1 == 2){  //Esto reduce la cantidad de rutas si es posible
                        rutas.erase(rutas.begin()+indiceRutaABorrar);
                        arreglarPuntos(puntos, indiceRutaABorrar);
                    }
                }
            }

            float EnergiaActual = distTotal(rutas, matriz);
            double random =((double)rand()/(double)RAND_MAX); // numero random entre 0 y 1
            float dif = EnergiaActual - EnergiaInit;
            if( dif <= 0 ){
                EnergiaInit = EnergiaActual;
            }else if(exp(-dif/TempActual) >= random){
                EnergiaInit = EnergiaActual;
            } else{ // des swapeo
                rutas = rutasTemp; //O(n)
                puntos = puntosTemp; //O(n)
            }

            if(EnergiaActual < EnergiaMin ){
                rutasSol = rutas; //O(n)
                puntosSol = puntos; //O(n)
                EnergiaMin = EnergiaActual;
            }


            if(EnergiaActual > EnergiaMin*1.5 ){ //RESET 
                EnergiaActual = EnergiaMin; 
                rutas = rutasSol; //O(n)
                puntos = puntosSol; //O(n)
            }

            iterador++;
            TempActual = Tmax - k*iterador;
        }
        printSol(rutas.size(), rutasSol, EnergiaMin); 
        //printParaGrafico(rutas.size(), rutasSol,  n, puntosSol);
        /*high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);*/
        //cout << n << " " << EnergiaMin << " " << time_span.count() << endl; 
    //}
}

#endif //TP3__H

