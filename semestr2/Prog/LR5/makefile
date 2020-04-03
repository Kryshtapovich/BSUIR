all: build run clean
LR5.o: main.cpp
	gcc -c -o LR5.o main.cpp
build: LR5.o
	gcc -o LR5 LR5.o
run:
	LR5.exe
clean:
	del *.o LR5 
	del *.exe LR5 