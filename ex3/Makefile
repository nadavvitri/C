CC = gcc
CFLAGS_COMPILATION = -c -g -Wvla -Wall -Wextra -std=c99 -DNDEBUG
CFLAGS_LINKAGE = -g


# All Target
all: SudokuSolver libGenericDFS.a

# Exceutables
SudokuSolver: SudokuSolver.o SudokuTree.o GenericDFS.o
	$(CC) $(CFLAGS_LINKAGE) SudokuSolver.o SudokuTree.o GenericDFS.o -o SudokuSolver -lm

# Object Files
GenericDFS.o: GenericDFS.c GenericDFS.h
	$(CC) $(CFLAGS_COMPILATION) GenericDFS.c -o GenericDFS.o

SudokuSolver.o: SudokuSolver.c
	$(CC) $(CFLAGS_COMPILATION) SudokuSolver.c -o SudokuSolver.o

SudokuTree.o: SudokuTree.c SudokuTree.h
	$(CC) $(CFLAGS_COMPILATION) SudokuTree.c -o SudokuTree.o

# Making libraries:
libGenericDFS.a: GenericDFS.c
	ar rcs libGenericDFS.a GenericDFS.c

# Other Target
clean:
	-rm -f *.o libGenericDFS.a SudokuSolver val_result

#make tests:
test: ex3.tar presubmit_ex3
	presubmit_ex3 ex3.tar
ex3.tar: Makefile SudokuSolver.c SudokuTree.c SudokuTree.h GenericDFS.c
	tar -cf ex3.tar Makefile SudokuSolver.c SudokuTree.c SudokuTree.h GenericDFS.c

# Make valgrind output files
valdbg: SudokuSolver
	valgrind --log-file="val_result" --leak-check=full --show-possibly-lost=yes --show-reachable=yes
	 --undef-value-errors=yes SudokuSolver

