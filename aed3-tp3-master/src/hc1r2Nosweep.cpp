#include "hauxiliares.h"

int main(){
    int n, demanda;
    cin >> n >> demanda;
    //while(n != 0 and demanda != 0){ //esto es para que tome mas de una entrada
        vector < punto > puntos;

        for(int i = 0; i < n; i++){
            punto a;
            cin >> a.x >> a.y >> a.d;
            a.id = i;
            a.ruta = -1;
            if(i > 0){
                a.rad = sqrt(pow(( a.x - puntos[0].x),2) +  pow((a.y - puntos[0].y),2));
                a.ang = atan2( a.y, a.x ) * 180 /100;
            }else{
                a.rad = 0;
                a.ang = 0;
            }
            puntos.push_back(a);  //O(n)
        }

        vector< vector<float> > matriz(n);

        for(int i = 0; i < n; i++){
            matriz[i].resize(n); // inicializamos la matriz
        }

       for(int i = 0; i < n; i++){
           for(int j = 0; j < n; j++){
                matriz[i][j] = sqrt(pow(( puntos[i].x - puntos[j].x),2) +  pow((puntos[i].y - puntos[j].y),2)); //O(n.n)
            } 
        }

        //-------------------------------------------------------------------------------------------------
        vector <vector <int> > rutas = ClustNoSweep(n, demanda, puntos, matriz);
        printSol(rutas.size(), rutas, distTotal(rutas, matriz));
        //printParaGrafico(rutas.size(),rutas, n, puntos); // descomentar esto y comentar lo de arriba para ver los graficos
        //cin >> n >> demanda; //esto es para que tome mas de una entrada
    //}
    return 0;
}
