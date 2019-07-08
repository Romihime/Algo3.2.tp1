#!/usr/bin/python

import sys

def leer_datos(path):
	xs = []
	ys = []
	ds = []
	with open(path, 'r') as f:
		#Ignoro las primeras 3 lineas
		nombre_archivo_salida = str(f.readline().split()[2])
		nombre_archivo_salida = nombre_archivo_salida + ".in"
		for i in range(2):
			f.readline()
		
		#Leo la cantidad de nodos
		line = f.readline()
		p, s, t = line.split()
		n = int(t)
		#print(n)

		#Ignoro la siguiente linea y leo la capacidad de los camiones
		f.readline()
		line = f.readline()
		p, s, t = line.split()
		c = int(t)
		#print(c)

		#Ignoro la siguiente linea y por cada id y coordenada voy guardando
		f.readline()
		for i in range(n):
			line = f.readline()
			_id, x, y = line.split()
			xs.append(x)
			ys.append(y)

		#Ignoro la siguiente linea y guardo la demanda segun cada id
		f.readline()
		for i in range(n):
			line = f.readline()
			_id, d = line.split()
			ds.append(d)
		#print(ds)

		with open(nombre_archivo_salida, 'w') as f2:
		    f2.write('{} {}\n'.format(n, c))
		    for i in range(n):
		        f2.write('{} {} {}\n'.format(xs[i], ys[i], ds[i]))

	return 0

def main():
	nombre_archivo = sys.argv[1] #tomamos el nombre dle archivo
	datos = leer_datos( nombre_archivo )

if __name__ == '__main__':
	main()
