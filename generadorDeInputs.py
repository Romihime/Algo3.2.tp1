import random

#random.seed(50)

for j in range(0,9): #veces
	n = random.randint(1, 10) #n
	v = random.randint(1, 100) #v
	print '{0:d} {1:d}'.format(n,v) #n y #v
	for i in range(0,n): #n
		aux = random.randint(1, 100)
		print '{0:d}'.format(aux)#agentes y #encuestas
print '{0:d} {1:d}'.format(0,0)