import matplotlib.pyplot as plt
import seaborn as sns
#sns.set(style="darkgrid")

def datos(nombre_archivo):
    valores = open(nombre_archivo, "r") 
    valores = valores.read()
    valores = [float(x) for x in valores.split()]
    return valores

def bloques(valores,intervalo):
    res = []
    valor = 0
    for elem in range(0,len(valores)):
        if elem % intervalo == 0 and elem != 0:
            res.append(valor/intervalo)
            valor = 0
        valor += valores[elem]
    res.append(valor/intervalo)
    return res

nada = [None]

fb = datos("outcomplejfbexp")
bt = datos("outcomplejbtexp")
#bt1 = datos("outcomplejbt1exp")
#bt2 = datos("outcomplejbt2exp")
pd = datos("outcomplejpdexp")


#plt.semilogy()
#plt.plot(nada+fb, label= 'Fuerza Bruta')
plt.plot(nada+bt, label= 'Backtracking')
plt.plot(nada+pd, label= 'Dinamica')

plt.legend( ( 'Backtracking', 'Dinamica'), loc = 'upper left', fontsize = 15)


plt.semilogy()
#plt.plot(nada+fb, label= 'Fuerza Bruta')
#plt.plot(nada+bt, label= 'Backtracking')
#plt.plot(nada+bt1, label= 'Backtracking con poda1')
#plt.plot(nada+bt2, label= 'Backtracking con poda2')
#plt.legend( ('Fuerza Bruta', 'Backtracking', 'Backtracking1', 'Backtracking2'), loc = 'upper left', fontsize = 15)




#plt.legend(["Caso Random"])
plt.grid(True)
plt.grid(color = '0.5', linestyle = '--', linewidth = 1)
#plt.axis('tight')
#plt.axis([0, 20, 0, 5])
plt.xlabel(r" V de 1 a 100", fontsize = 24, color = 'black')
plt.ylabel(r"Tiempo en Segundos", fontsize = 24, color = 'black')
plt.title(' BT vs PD',fontsize = 28, color = 'black', verticalalignment = 'baseline', horizontalalignment = 'center')
plt.show()