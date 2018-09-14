import random

#random.seed(50)

for n in range(1,100): #veces
	#n = 100 #n
	v = random.randint(1, 100) #v
	print '{0:d} {1:d}'.format(n,v) #n y #v
	for i in range(0,n): #n
		#aux = random.randint(1, 100)
		print '{0:d}'.format(i)#los valores
print '{0:d} {1:d}'.format(0,0)