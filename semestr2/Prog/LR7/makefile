all: build run clean
LR7.o: main.cpp
	gcc -c -o LR7.o main.cpp
build: LR7.o
	gcc -o LR7 LR7.o
run: 
	LR7.exe
clean:
	del *.o LR7
	del *.exe LR7
