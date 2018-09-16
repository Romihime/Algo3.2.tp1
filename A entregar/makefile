make: 
	g++ -g -std=c++11 -o tp1fb fb.cpp
	g++ -g -std=c++11 -o tp1bt sumaDeConj.cpp
	g++ -g -std=c++11 -o tp1pd pd.cpp
	
clean:
	rm tp1fb
	rm tp1bt
	rm tp1pd

test:
	python generadorDeInputs.py > in
	./tp1fb < in > outcomplejfbexp
	./tp1bt < in > outcomplejbtexp
	./tp1pd < in > outcomplejpdexp
	python plot.py


