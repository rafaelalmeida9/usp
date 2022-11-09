UTIL1=Ponto.c
UTIL2=Caminho.c
MAIN=Main.c
BINARY=executavel

all:
	gcc -Wall -g $(UTIL1) $(UTIL2) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)
	
debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL1) $(UTIL2) -o $(BINARY)

zip:
	zip -r -j ex1.zip *

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o