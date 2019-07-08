#include "hauxiliares.h"

int main(){
	int n, demanda;
    cin >> n >> demanda;
    //while(n != 0 and demanda != 0){
        vector < punto > puntos;

        for(int i = 0; i < n; i++){
            punto a;
            cin >> a.x >> a.y >> a.d;
            a.id = i;
            a.ruta = -1;
            if(i > 0){
                a.rad = sqrt(pow(( a.x - puntos[0].x),2) +  pow((a.y - puntos[0].y),2));
                a.ang = atan2( a.y- puntos[0].y, a.x - puntos[0].x)*180/3.1416;
                if (a.ang < 0) a.ang = a.ang+180 + 180;
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
                matriz[i][j] =  sqrt(pow(( puntos[i].x - puntos[j].x),2) +  pow((puntos[i].y - puntos[j].y),2)); //O(n.n)
            } 
        }

        //-------------------------------------------------------------------------------------------------
        vector <vector <int> > rutas = ClustSweep(n, demanda, puntos, matriz);
        printSol(rutas.size(), rutas, distTotal(rutas, matriz));
        //printParaGrafico(rutas.size(),rutas, n, puntos);
        //cout << distTotal(rutas, matriz) << endl;
        //cin >> n >> demanda;
    //}
    return 0;
}
