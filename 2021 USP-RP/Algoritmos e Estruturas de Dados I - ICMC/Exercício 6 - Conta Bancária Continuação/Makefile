UTIL1=cliente.c
UTIL2=tree.c
MAIN=main.c
BINARY=executavel

all:
	gcc -Wall -g $(UTIL1) $(UTIL2) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)
	
debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL1) $(UTIL2) -o $(BINARY)

zip:
	zip -r -j ex6.zip *

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o