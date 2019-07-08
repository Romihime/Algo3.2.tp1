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
            a.visitado = false;
            a.ruta = -1;
        	puntos.push_back(a);  //O(n)
        }

        vector<vector<float>> matriz( n, vector<float>(n, 0) ); //creamos la matriz de puntos

        for(int i = 0; i < n -1; i++){
            matriz[0][i+1] = matriz[i+1][0] = sqrt( pow( puntos[i+1].x - puntos[0].x ,2) + pow( puntos[i+1].y - puntos[0].y ,2) ); // inicializamos la matriz
        }

       for(int i = 1; i < n; i++){
           for(int j = i+1; j < n; j++){
                matriz[i][j] = matriz[j][i]= sqrt(pow(( puntos[i].x - puntos[j].x),2) +  pow((puntos[i].y - puntos[j].y),2)) ; //O(n.n)
            } 
        }

        //-------------------------------------------------------------------------------------------------

        vector <vector <int> > rutas = GolosoDem(n, demanda, puntos, matriz);
        printSol(rutas.size(), rutas, distTotal(rutas, matriz));
        //printParaGrafico(rutas.size(),rutas, n, puntos);
        //cout << distTotal(rutas, matriz) << endl;
        //cin >> n >> demanda;
    //}
    return 0;
}