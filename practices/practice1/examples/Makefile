all: main

main: main.o libhello1.a libhello2.so
	gcc -s main.o -o main -L. -lhello1 -lhello2
	
main.o: main.c
	gcc main.c -o main.o -c

libhello1.a: hello1.o
	ar rcs libhello1.a hello1.o
	
hello1.o: hello1.c
	gcc hello1.c -o hello1.o -c
	
libhello2.so: hello2.o
	gcc -fPIC hello2.c -c -o hello2.o
	gcc -shared hello2.o -o libhello2.so
	
hello2.o: hello2.c
	gcc hello2.c -o hello2.o -c
	
clean:
	rm -f hello1.o hello2.o libhello1.a libhello2.so main.o main
