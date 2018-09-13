make: 
	g++ -g -std=c++11 -o tp1fb fb.cpp
	g++ -g -std=c++11 -o tp1bt sumaDeConj.cpp
	g++ -g -std=c++11 -o tp1pd pd.cpp
	g++ -g -std=c++11 -o compbt complejidadbt.cpp
	g++ -g -std=c++11 -o comppd complejidadpd.cpp
	python generadorDeInputs.py > in
	
clean:
	rm tp1fb
	rm tp1bt
	rm tp1pd
	rm compbt
	rm comppd

test:
	./tp1bt < in > outcomplejbtexp
	./tp1pd < in > outcomplejpdexp
	./compbt < in > outcomplejbtteo
	./comppd < in > outcomplejpdteo
	python ComparativaFuncionesPearson.py


