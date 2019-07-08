all: 
	g++ -g  annClustNoSweep.cpp  -std=c++11 -o zannClustNoSweep
	g++ -g  annClustSweep.cpp  -std=c++11 -o zannClustSweep 
	g++ -g  annGolosoDis.cpp  -std=c++11 -o zannGolosoDis 
	g++ -g  annGolosoDem.cpp  -std=c++11 -o zannGolosoDem 
	g++ -g  annSavings.cpp  -std=c++11 -o zannSavings
	g++ -g  hc1r2sweep.cpp  -std=c++11 -o zcrsweep 
	g++ -g  hc1r2Nosweep.cpp  -std=c++11 -o zcrnosweep
	g++ -g  hgolosoDis.cpp  -std=c++11 -o zgolosodis 
	g++ -g  hgolosoDem.cpp  -std=c++11 -o zgolosodem 
	g++ -g  hsavings.cpp  -std=c++11 -o zsavings

todos: #Este make sirve para ver que esten funcionando y dando lo que pide el ejercicio
	./zcrsweep < A-n32-k5.in
	./zcrnosweep < A-n32-k5.in
	./zgolosodis < A-n32-k5.in
	./zgolosodem < A-n32-k5.in
	./zsavings < A-n32-k5.in
	./zannClustNoSweep < A-n32-k5.in
	./zannClustSweep < A-n32-k5.in
	./zannGolosoDis < A-n32-k5.in
	./zannGolosoDem < A-n32-k5.in
	./zannSavings < A-n32-k5.in

#Para correr los graficos se debe ir al .cpp de la heuristica y comentar el "printParaSolucion" y descomentar el "printParaGrafico"
crSweep:
	./zcrsweep < A-n32-k5.in > hc1r2sweep.sal
	python plot.py hc1r2sweep.sal

crNoSweep:
	./zcrnosweep < TodosA > hc1r2Nosweep.sal
	python plot.py hcrnosweep.sal

golDis:
	./zgolosodis < A-n32-k5.in > hgolosoDis.sal
	python plot.py hgolosodis.sal 

golDem:
	./zgolosodem < TodosA > hgolosoDem.sal
	python plot.py hgolosodem.sal

sav:
	./zsavings < TodosA > hsavings.sal
	python plot.py hsavings.sal





	

clean:
	rm -f zcrsweep
	rm -f zcrnosweep
	rm -f zgolosodis
	rm -f zgolosodem
	rm -f zsavings
	rm -f zannClustNoSweep
	rm -f zannClustSweep
	rm -f zannGolosoDis
	rm -f zannGolosoDem
	rm -f zannSavings
	rm -f *.sal


