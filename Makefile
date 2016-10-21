all: makematrix makeblock makemain
	g++  main.o matrix.o block.o -lpapi -o main

makematrix:
	g++ -c -std=c++11 matrix.cpp

makeblock:
	g++ -c -std=c++11 block.cpp

makemain:
	g++ -c -std=c++11 main.cpp

test: all
	./main -time ./a2000.bin ./b2000.bin > ./test/time
	./main -test flops ./a2000.bin ./b2000.bin > ./test/flops
	./main -test l1 ./a2000.bin ./b2000.bin > ./test/l1
	./main -test l2 ./a2000.bin ./b2000.bin > ./test/l2
	./main -test tlb ./a2000.bin ./b2000.bin > ./test/tlb
	./main -test tot ./a2000.bin ./b2000.bin > ./test/tot
	gnuplot plotrules

generate: all
	./main -generate