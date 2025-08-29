all:
	gcc -o danos main.c src/memory.c

clean:
	rm danos
