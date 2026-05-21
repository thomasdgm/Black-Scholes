all: bin/test

bin/test: obj/normalDistribution.o obj/delta.o obj/gamma.o obj/vega.o obj/theta.o obj/rho.o obj/main.o
	g++ -o bin/test obj/normalDistribution.o obj/delta.o obj/gamma.o obj/vega.o obj/theta.o obj/rho.o obj/main.o

obj/main.o : src/normalDistribution.cpp src/delta.cpp src/gamma.cpp src/vega.cpp src/theta.cpp src/rho.cpp src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

obj/rho.o : src/rho.cpp src/theta.cpp src/vega.cpp src/gamma.cpp src/gamma.h src/delta.h src/normalDistribution.h
	g++ -c src/rho.cpp -o obj/rho.o

obj/theta.o : src/theta.cpp src/vega.cpp src/gamma.cpp src/gamma.h src/delta.h src/normalDistribution.h
	g++ -c src/theta.cpp -o obj/theta.o

obj/vega.o : src/vega.cpp src/gamma.cpp src/gamma.h src/delta.h src/normalDistribution.h
	g++ -c src/vega.cpp -o obj/vega.o

obj/gamma.o : src/gamma.cpp src/gamma.h src/delta.h src/normalDistribution.h
	g++ -c src/gamma.cpp -o obj/gamma.o

obj/delta.o : src/delta.cpp src/delta.h src/normalDistribution.h
	g++ -c src/delta.cpp -o obj/delta.o

obj/normalDistribution.o: src/normalDistribution.cpp src/normalDistribution.h
	g++ -c src/normalDistribution.cpp -o obj/normalDistribution.o

clean : 
	rm obj/*.o bin/*