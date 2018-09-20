run: main
	./main
all: main.o infcalc.o
	gcc -o main main.o infcalc.o

main.o:	main.c infcalc.h
	gcc -c main.c

infcalc.o: infcalc.c infcalc.h
	gcc -c infcalc.c
