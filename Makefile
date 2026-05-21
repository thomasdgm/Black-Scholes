all: bin/test

bin/test: obj/normalDistribution.o obj/delta.o obj/gamma.o obj/main.o
	g++ -o bin/test obj/normalDistribution.o obj/delta.o obj/gamma.o obj/main.o

obj/main.o : src/normalDistribution.cpp src/delta.cpp src/gamma.cpp src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

obj/gamma.o : src/gamma.cpp src/gamma.h src/delta.h src/normalDistribution.h
	g++ -c src/gamma.cpp -o obj/gamma.o

obj/delta.o : src/delta.cpp src/delta.h src/normalDistribution.h
	g++ -c src/delta.cpp -o obj/delta.o

obj/normalDistribution.o: src/normalDistribution.cpp src/normalDistribution.h
	g++ -c src/normalDistribution.cpp -o obj/normalDistribution.o

clean : 
	rm obj/*.o bin/*