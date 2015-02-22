all: main wc map

main: main.o
	gcc -ggdb3 main.o -o main

main.o: main.c
	gcc -ggdb3 -c main.c

wc: wc.o
	gcc -ggdb3 wc.o -o wc

wc.o: wc.c
	gcc -ggdb3 -c wc.c

map: map.o
	gcc -ggdb3 map.o -o map

map.o: map.c
	gcc -ggdb3 -c map.c

clean:
	rm -rf *o main wc map
