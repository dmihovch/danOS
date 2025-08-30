
all:
	gcc -o danos main.c src/memory.c src/debug.c src/cpu.c src/utils.c

clean:
	rm danos

run:
	./danos
