make: 
	g++ -g -std=c++11 -o tp1fb fb.cpp
	g++ -g -std=c++11 -o tp1bt sumaDeConj.cpp
	g++ -g -std=c++11 -o tp1bt1 sumaDeConjpoda1.cpp
	g++ -g -std=c++11 -o tp1bt2 sumaDeConjpoda2.cpp
	g++ -g -std=c++11 -o tp1pd pd.cpp
	
clean:
	rm tp1fb
	rm tp1bt
	rm tp1pd
	rm compbt
	rm comppd

test:
	python generadorDeInputs.py > in
	./tp1bt < in > outcomplejbtexp
	./tp1pd < in > outcomplejpdexp
	#./tp1fb < in > outcomplejfbexp

	python plot.py


