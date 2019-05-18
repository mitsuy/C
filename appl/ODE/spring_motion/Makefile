CC	=gcc

all:	spring

spring: spring_oscillation.o function.o exEuler.o rk4.o output.o
	$(CC) -o $@ $^

spring_oscillation.o: spring_oscillation.c
	gcc -c spring_oscillation.c

function.o: function.c
	gcc -c function.c

exEuler.o: exEuler.c
	gcc -c exEuler.c

rk4.o: rk4.c
	gcc -c rk4.c

output.p: output.c
	gcc -c output.c

clean:
	rm -f *.o *~
