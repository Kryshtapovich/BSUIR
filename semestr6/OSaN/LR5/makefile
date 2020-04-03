all: compile run clean

compile:
	g++ main.cpp -std=c++17 -o main.o

run: main.o
	./main.o

clean:
	rm -rf *.o