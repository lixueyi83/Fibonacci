all:
	@echo compiling ./fib
	@gcc -o fib fibonacci.c debug.h
	@echo run ./fib
	@./fib 

clean:
	rm -rf ./fib
