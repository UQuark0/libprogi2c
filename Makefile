test: compile run clean

compile:
	gcc libprogi2c.c libprogi2c_test.c -o test

run:
	./test

clean:
	rm test