CC	=gcc

all:	stunnel


stunnel: tunnel_static.o read_data.o print_data.o function.o jacobi.o newton_raphson.o
	$(CC) -o $@ $^ 


tunnel_static.o: tunnel_static.c
	gcc -c tunnel_static.c

read_data.o: read_data.c
	gcc -c read_data.c

print_data.o: print_data.c
	gcc -c print_data.c

function.o: function.c
	gcc -c function.c

newton_raphson.o: newton_raphson.c
	gcc -c newton_raphson.c

clean:
	rm -f rk4 *.o *~ 
