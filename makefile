lib:
	mkdir -p dist
	gcc -I./include -c src/lib.c -o dist/lib.o

1: lib
	gcc -I./include -c days/1.c -o dist/d1.o
	gcc -I./include dist/lib.o dist/d1.o -o app

2: lib
	gcc -I./include -c days/2.c -o dist/d2.o
	gcc -I./include dist/lib.o dist/d2.o -o app

3: lib
	gcc -I./include -c days/3.c -o dist/d3.o
	gcc -I./include dist/lib.o dist/d3.o -o app

4: lib
	gcc -I./include -c days/4.c -o dist/d4.o
	gcc -I./include dist/lib.o dist/d4.o -o app

5: lib
	gcc -I./include -c days/5.c -o dist/d5.o
	gcc -I./include dist/lib.o dist/d5.o -o app
