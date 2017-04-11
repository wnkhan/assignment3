FLAGS = -Wall -Wextra -std=c99

dijkstra: dijkstra.o darray.o binomial.o scanner.o integer.o sll.o queue.o vertex.o helper.o
	gcc $(FLAGS) dijkstra.o darray.o binomial.o scanner.o integer.o sll.o queue.o vertex.o helper.o -o dijkstra
dijkstra.o: dijkstra.c darray.h binomial.h integer.h sll.h queue.h helper.h
	gcc $(FLAGS) -c dijkstra.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
binomial.o: binomial.c binomial.h darray.h queue.h sll.h
	gcc $(FLAGS) -c binomial.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
vertex.o: vertex.c vertex.h scanner.h darray.h
	gcc $(FLAGS) -c vertex.c
helper.o: helper.c helper.h scanner.h
	gcc $(FLAGS) -c helper.c

cleanbuild:
	clear
	make clean
	make
clean:
	rm -f dijkstra.o darray.o binomial.o scanner.o integer.o sll.o queue.o vertex.o helper.o dijkstra

test: ./dijkstra

	./dijkstra