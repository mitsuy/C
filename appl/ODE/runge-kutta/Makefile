CC	=gcc

all:	rk4


rk4: rk4.o rk4_calc.o func_rk4.o output.o
	$(CC) -o $@ $^ 
#	gcc -o rk4 rk4.o func_rk4.o rk4_calc.o output.o
rk4.o: rk4.c
	gcc -c rk4.c
rk4_calc.o: rk4_calc.c
	gcc -c rk4_calc.c
func_rk4.o: func_rk4.c
	gcc -c func_rk4.c
output.o: output.c
	gcc -c output.c

clean:
	rm -f rk4 *.o *~ 
