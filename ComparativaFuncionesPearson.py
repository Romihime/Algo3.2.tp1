import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import random


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

df = pd.DataFrame()

Teorica = datos("outcomplejpdteo")
Experimental = datos("outcomplejpdexp")



df['Teorica'] = Teorica
df['Experimental'] = Experimental

r = df.corr(method="pearson")['Teorica']['Experimental']
print r

sns.jointplot(df['Teorica'], df['Experimental'], kind="reg")
plt.show()


