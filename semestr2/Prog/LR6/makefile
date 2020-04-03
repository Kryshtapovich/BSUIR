all: build run clean
LR6.o: main.cpp
	gcc -c -o LR6.o main.cpp
build: LR6.o
	gcc -o LR6 LR6.o
run: 
	LR6.exe
clean:
	del *.o LR6
	del *.exe LR6
