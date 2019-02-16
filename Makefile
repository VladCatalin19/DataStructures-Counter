build:
	gcc -std=c9x tema1.c -o tema1 -g -Wall
clean:
	rm tema1 test_*
run:	
	./tema1
runValgrind:
	valgrind ./tema1 --leak-check=full --show-reachables=yes
