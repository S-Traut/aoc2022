lib:
	mkdir -p dist
	gcc -I./include -c src/lib.c -o dist/lib.o

1: lib
	gcc -I./include -c days/1.c -o dist/d1.o
	gcc -I./include dist/lib.o dist/d1.o -o app

2: lib
	gcc -I./include -c days/2.c -o dist/d2.o
	gcc -I./include dist/lib.o dist/d2.o -o app
