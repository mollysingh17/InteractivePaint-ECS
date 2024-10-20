paint: paint.o print_statements.o
	gcc -g -Wall -Werror -o paint paint.o print_statements.o -lm
paint.o: paint.c print_statements.h
	gcc -g -Wall -Werror -c paint.c
print_statements.o: print_statements.c print_statements.h
	gcc -g -Wall -Werror -c print_statements.c -lm
clean:
	rm -fr *.o *.out