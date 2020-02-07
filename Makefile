all:
	@echo compiling ./fib
	@gcc -o fib fibonacci.c huge_num.c huge_num.h debug.h
	@echo run ./fib
	@./fib 

clean:
	rm -rf ./fib
