CC = gcc
CFLAGS = -g -std=c99 -Wall

all: assembler linker

assembler: clean
	$(CC) $(CFLAGS) -o assembler assembler.c my_assembler_utils.c -L. -llibP4

linker: clean
	$(CC) $(CFLAGS) -o linker linker.c my_linker_utils.c -L. -llibP4

clean:
	del /f /q assembler.exe linker.exe
