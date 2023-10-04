all:
	$(CC) src/main.c -o cbasic -Wall -Wextra -pedantic
asm:
	$(CC) src/main.c -o main.asm -S
