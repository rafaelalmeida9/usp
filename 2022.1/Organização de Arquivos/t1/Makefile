all:
	gcc -Wall -g *.c -o executavel

run:
	./executavel
	
debug:
	gcc -DDEBUG -Wall *.c -o executavel

zip:
	zip -r -j ex6.zip *

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./executavel