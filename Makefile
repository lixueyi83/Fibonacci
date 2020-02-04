all:
	gcc -o fib fibonacci.c
	./fib 

clean:
	rm -rf ./fib
