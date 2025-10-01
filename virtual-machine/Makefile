
all:
	gcc -o danos main.c src/memory.c src/debug.c src/cpu.c src/utils.c src/ops.c

clean: danos
	rm danos

run: danos
	./danos


vg: danos
	valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --track-fds=yes \
         --num-callers=50 \
         --error-exitcode=1 \
         --errors-for-leak-kinds=all \
         ./danos
