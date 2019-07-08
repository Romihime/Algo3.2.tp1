#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import sys
def plotTSP(paths, points):
    for p in points:
        x = p[0]
        y = p[1]
        lab = str(points.index(p))
        plt.plot(x, y, marker = 'o', color='b')
        plt.text(x * (1 + 0.01), y * (1 + 0.01) , lab, fontsize=12)
    
    for path in paths:
        nparray = []
        for point in path:
            nparray.append( points[point] )
        nparray = np.array(  nparray  )
        plt.plot(nparray[:,0], nparray[:, 1])
    plt.show()

def main():
    archivo = sys.argv[1] #nos quedamos con el nombre de archivo
    with open(archivo) as f:
        cant_rutas = int(f.readline())

        rutas = []

        for i in range(cant_rutas):
            temp = f.readline()
            temp = [ int(x) for x in temp.split() ]
            rutas.append( temp )
        
        puntos = []
        cant_puntos = int(f.readline())

        for i in range(cant_puntos):
            line = f.readline()
            x, y = line.split()
            x = float(x)
            y = float(y)
            puntos.append( (x,y) )
    plotTSP(rutas, puntos)

if __name__ == '__main__':
    main()
    