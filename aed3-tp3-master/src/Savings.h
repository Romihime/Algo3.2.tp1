//
// Created by julian on 30/10/18.
//

#ifndef TP3_SAVINGS_H
#define TP3_SAVINGS_H


#include <vector>
#include <map>
#include <utility>
#include <numeric>
#include <list>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std;

#define Matriz vector< vector < double > >
#define D distancias


class Savings {
public:
    //constructor complejidad: O(N²)
    Savings( vector<tuple<double, double, int>> _puntos, int _capacidad);
    //algoritmo complejidad : O(N³)
    vector<vector<int>> procesar();

    double distanciaEntrePuntos(int p1, int p2);

private:
    /* Matriz de distancias que indica la  */
    Matriz distancias;

    //demanda[i] indica la demanda del punto de entrega i
    vector<int> demanda;//demandas demanda;

    //capacidad de transporte de los vehiculos
    int capacidad;

    //lista las posibles uniones de vehiculos
    list<tuple<double, int, int> > listarPosiblesUnionesPorAhorro( map<int, tuple<int, vector<int> > > &vehiculo );

    //suma los elemetos de un vector Complejidad O(#elementos) en el vector
    int sumaVector(vector < int> elementos);

    //calcula el ahorro(saving) que se obtiene al unir los recorridos de los caminos A y B. Complejidad O(1)
    double calcularAhorro( vector<int> &vehiculoA, vector<int> &vehiculoB );

    //une el recorrido de 2 vehiculos, coplejidad O( #recorrido_vA + #recorrido_vB )
    void unir( tuple<double, int, int> puntos, map<int, tuple<int, vector<int>>> &vehiculo );

    //calcula la distancia total del recorrido. Complejidad O( log(#vehiculos)*#puntos )
    double calcularDistancia( map<int, tuple<int, vector<int> > > &vehiculos );

    //funcion que usamos para definir el orden de las tuplas<saving, vehiculoA, vehiculoB>. Complejidad O(1)
    static bool ordenDeTuplas( tuple<double, int, int> a, tuple<double, int,int> b );
};

double Savings::distanciaEntrePuntos(int p1, int p2){
    return D[p1][p2];
}

Savings::Savings(vector<tuple<double, double, int>> _puntos, int _capacidad) : distancias( vector<vector<double>>( _puntos.size(), vector<double>(_puntos.size(), 0) ) ), demanda( _puntos.size() ), capacidad(_capacidad) {

    double x = 0;
    double y = 0;

    double x_depot = get<0>(_puntos[0]);
    double y_depot = get<1>(_puntos[0]);

    for(int i = 0; i < demanda.size()-1; i++){
        //asignamos la demanda del punto de entrega
//        demanda[i] = get<2>(_puntos[i+1]);
        demanda[i+1] = (int) get<2>(_puntos[i+1]);

        x = (double)( get<0>( _puntos[i+1] ) );
        y = (double)( get<1>( _puntos[i+1] ) );
        //asignamos la distancia desde el deposito al punto de entrega
        distancias[0][i+1] = distancias[i+1][0] = sqrt( pow( x - x_depot, 2 ) + pow(y - y_depot,2) ) ;
    }
    //calculamos las distancias entre todos los puntos
    for( int i = 1 ; i < _puntos.size(); i++){
        double x_p1 = get<0>( _puntos[i] );
        double y_p1 = get<1>( _puntos[i] );
        for(int j = i+1; j < _puntos.size(); j++){
            double x_p2 = get<0>( _puntos[j] );
            double y_p2 = get<1>( _puntos[j] );
            D[i][j] = D[j][i] = sqrt( pow( x_p1 - x_p2 ,2 ) + pow(y_p1 - y_p2, 2) );
        }
    }

}
vector<vector<int>> Savings::procesar() {
    //map<int, tuple<int, vector<int> > > vehiculo;//vehiculo debe tener siempre guardado
    map<int, tuple<int, vector<int> > > vehiculo;// la clave indica que vehiculo es
    //significado, primer elemento demenda total del camino, segundo elemento distancia total del camino, tercer elemento: camino

    //en principio tenemos un vehiculo que solo va y vuelve a un solo punto
    //cada vehiculo tiene un punto distinto
    for(auto i = 1; i < this->distancias.size(); i++ )
//        vehiculo[i] = make_tuple( demanda[i-1], vector<int>(1, i) );//al principio la distancia del camino es 0, ya que solo hay un punto de entrega
        vehiculo[i] = make_tuple( demanda[i], vector<int>(1, i) );//al principio la distancia del camino es 0, ya que solo hay un punto de entrega
    bool hay_cambios = true;
    while( hay_cambios ){
        int vehiculos_antes_de_unir = vehiculo.size();
        vector<bool> vehiculosVisitados( this->distancias.size(), false );
        vehiculosVisitados[0] = true; //marcamos el deposito como visitado
        list<tuple<double,int,int>> posiblesUnionsPorAhorro = listarPosiblesUnionesPorAhorro(vehiculo);//
        posiblesUnionsPorAhorro.sort(ordenDeTuplas );
        for( auto it : posiblesUnionsPorAhorro ){
            if( !vehiculosVisitados[get<1>(it)] && !vehiculosVisitados[ get<2>(it) ] ){
                //en esta parte tenemos que mergear los dos circuitos
                //lo que vamos a hacer es unirlo sobre el de menor numero, y eliminar el de mayor numero
                //tambien tenemos que actualizar la demanda total del circuito
                unir( it, vehiculo );
                vehiculosVisitados[get<1>(it)] = true;
                vehiculosVisitados[get<2>(it)] = true;
            }
        }

        if(vehiculos_antes_de_unir == vehiculo.size())
            hay_cambios = false;//si en esta iteración no se redujó la cantidad de vehiculos, salgo de la iteración
    }
    vector<vector<int>> res;
    for( auto elem : vehiculo )
        res.push_back( get<1>(elem.second ));
    return res;
}

void Savings::unir(tuple<double, int, int> puntos, map<int, tuple<int, vector<int>>> &vehiculo) {
    int vA = get<1>(puntos);//nos quedamos con el indice del vehiculo A
    int vB = get<2>(puntos);//nos quedamos con el indice del vehiculo B

    vector<int> &_vA = get<1>(vehiculo[vA]); //referencia al camino que recorre el vehiculo A, complejidad log(#vehiculos)
    vector<int> &_vB = get<1>(vehiculo[vB]); //referencia al camino que recorre el vehiculo B log(#vehiculos)

    int inicio_A = _vA.front();// primer punto de entrega del vehiculo A
    int fin_A = _vA.back();// ultimo punto de entrega del vehiculo A

    int inicio_B = _vB.front(); // primer punto de entrega del vehiculo B
    int fin_B = _vB.back(); // ultimo punto de entrega del vehiculo B
    double ahorro = get<0>(puntos);
    //HASTA ESTE PUNTO COMPLEJIDAD O(1), SOLO INICIALIZACION DE VARIABLES. ACCEDER A LOS ELEMENTOS DE UN VECTOR OCMPLEJIDAD CONSTANTE

    if( ahorro == D[0][inicio_A] + D[fin_B][0] - D[fin_A][inicio_B] ){//si el ahorro se corresponde a esta union
        //dejo los vectores de recorrido como estaban, solo dejo este if para entender mejor el algoritmo, puede sacarse
        //O(1), NO HAGO NADA EN ESTE IF
    }else if( ahorro == D[0][fin_A] + D[inicio_B][0] - D[inicio_A][fin_B] ){//si el ahorro se corresponde a esta union
        //invierto el orden de los puntos de entrega de los dos vectores
        std::reverse( _vA.begin(), _vA.end() );
        std::reverse( _vB.begin(), _vB.end() );
        //complejidad O( #vA + #vB )
    }else if(ahorro == D[0][fin_A] + D[fin_B][0] - D[inicio_A][inicio_B] ){//si el ahorro se corresponde a esta union
        std::reverse(_vB.begin(), _vB.end());//solo invierto el recorrido del camino B
        //complejidad O(#vB)
    }else if( ahorro == D[0][inicio_A] + D[inicio_B][0] - D[fin_A][fin_B]  ){//si el ahorro se corresponde a esta union
        std::reverse(_vA.begin(), _vA.end());//solo invierto el recorrido del camino A
        //complejidad O(#vA)
    }
    //agregamos el resto del recorrido al vehiculo A
    for(auto elem : _vB) //complejidad O(#vB)
        _vA.push_back(elem);//insercion amortizada O(1)
    //actualizamos la demanta total sobre el vehiculoA
    get<0>(vehiculo[vA]) = get<0>(vehiculo[vA]) + get<0>(vehiculo[vB]);//obtencion y asignacion de una tupla en un map, log(#vehiculos)
    //eliminamos el vehiculo B porque de su carga ya se hizo cargo el vehiculo A
    vehiculo.erase(vB);
}

int Savings::sumaVector(vector<int> elementos) {
    int res = 0;
    for (int elem : elementos)
        res += elem;
    return res;
}

list<tuple<double, int, int> > Savings::listarPosiblesUnionesPorAhorro(map<int, tuple<int, vector<int> > > &vehiculo) {
    list<tuple<double, int, int>> res;
    for( auto it1 = vehiculo.begin(); it1 != vehiculo.end(); it1++ ){
        auto it2 = it1;
        it2++;
        while( it2 != vehiculo.end() ){
            if( get<0>( it1->second ) + get<0>(it2->second) <= this->capacidad ){
                double ahorro;
                ahorro = calcularAhorro( get<1>( it1->second) , get<1>(it2->second));
                res.push_back( make_tuple( ahorro, it1->first, it2->first ) );
            }
            it2++;
        }
    }
    return res;
}

double Savings::calcularAhorro( vector<int> &vehiculoA, vector<int> &vehiculoB) {
//  d-p1-p2-p3-d       d-p7-p8-p9-d
/*  d-iA .. fA-d       d-iB .. fB-d
 * la distancia recorrida por el vehiculoA es: D[0][p1] + D[p1][p3] + D[p3][0]
 * la distancia recorrida por el vehiculoB es: D[0][p7] + D[p7][p9] + D[P9][0]
 * la distancia recorrida por el par de vehiculos es: D[0][p1] + D[p1][p3] + D[p3][0] + D[0][p7] + D[p7][p9] + D[P9][0]
 * si optamos por unir las rutas por p3 y p7 la distancia recorrida por un vehiculo es: D[0][p1] + D[p1][p3] + D[p3][p7] + D[p7][p9] + D[p9][0]
 * El ahorro por optar por esta union es: D[0][p1] + D[p1][p3] + D[p3][0] + D[0][p7] + D[p7][p9] + D[P9][0] - ( D[0][p1] + D[p1][p3] + D[p3][p7] + D[p7][p9] + D[p9][0] )
 *                                        D[p3][0] + D[0][p7] - D[p3][p7]
 * Si optamos por unir las rutas por p1 y p9 la distancia recorrida es: D[0][p3] + D[p3][p1] + D[p1][p9] + D[p9][p7] + D[p7][0]
 * El ahorro por optar por esta union es: D[0][p1] + D[p1][p3] + D[p3][0] + D[0][p7] + D[p7][p9] + D[P9][0] -( D[0][p3] + D[p3][p1] + D[p1][p9] + D[p9][p7] + D[p7][0] )
 *                                        D[0][p1] + D[p9][p0] -D[p1][p9]
 * Si optamos por unir las rutas por p3 y p9 el ahorro es: D[0][p3] + D[p9][0] - D[p3][p9]
 * Si optamos por unir las rutas por p1 y p7 el ahorro es: D[0][p1] + D[p7][0] - D[p7][p9]
 * */
    int inicioA = vehiculoA.front();
    int finA = vehiculoA.back();
    int inicioB = vehiculoB.front();
    int finB = vehiculoB.back();
    double max = D[0][inicioA] + D[finB][0] - D[finA][inicioB];
    max = std::max( max, D[0][finA] + D[0][inicioB] - D[inicioA][finB] );
    max = std::max( max, D[0][inicioA] + D[0][inicioB] - D[finA][finB] );
    max = std::max( max, D[0][finA] + D[0][finB] - D[inicioA][inicioB]);

    return max;
}

double Savings::calcularDistancia(map<int, tuple<int, vector<int> > > &vehiculos) {
    double res = 0;
    for( auto v : vehiculos ){
        res += D[0][ get<1>( v.second ).front() ];
        for(int i = 0; i < get<1>( v.second ).size() - 1; i++){
            int p1 = get<1>( v.second )[i];
            int p2 = get<1>( v.second )[ i+1 ];
            res += D[p1][p2];
        }
        res += D[0][ get<1>( v.second ).back() ];
    }
}

bool Savings::ordenDeTuplas(tuple<double, int, int> a, tuple<double, int, int> b) { return get<0>(a) > get<0>(b); }


#endif //TP3_SAVINGS_H

