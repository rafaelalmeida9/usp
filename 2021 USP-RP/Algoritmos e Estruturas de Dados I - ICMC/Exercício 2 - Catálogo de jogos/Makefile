UTIL1=catalogo.c
UTIL2=jogo.c
MAIN=main.c
BINARY=executavel

all:
	gcc -Wall -g $(UTIL1) $(UTIL2) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)
	
debug:
	gcc -DDEBUG -Wall $(UTIL1) $(UTIL2) $(MAIN) -o $(BINARY)

zip:
	zip -r -j ex2.zip *

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o