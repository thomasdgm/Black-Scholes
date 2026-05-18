all: bin/test

bin/test: obj/normalDistribution.o obj/main.o
	g++ -o bin/test obj/normalDistribution.o obj/main.o

obj/main.o : src/normalDistribution.cpp src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

obj/normalDistribution.o: src/normalDistribution.cpp src/normalDistribution.h
	g++ -c src/normalDistribution.cpp -o obj/normalDistribution.o