#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "SudokuTree.h"

//**********************************Define**********************************//
#define LINE_MAX_SIZE 400
#define IO_ERROR 1
#define TOO_MUCH_ARGS 2
#define SUPPLY_FILE 5
#define CLOSING_FILE_ERROR 3
#define NO_SOLUTION 4
#define IO_ERROR_MSG "Error: Please check your arguments!"
#define SUPPLY_FILE_MSG ":no such file!" "\n"
#define CLOSING_FILE_ERROR_MSG "Error: Some error happen with closing input file!!"
#define NO_SOLUTION_MSG "no solution!" "\n"
#define NOT_VALID_MSG ":not a valid sudoku file" "\n"
//**************************************************************************//

//***************************Function Declaration***************************//
int reader(FILE *inputFile, char *filename);
void fileCheckClosing(FILE *inputFile);
//**************************************************************************//

/**
* the main function that run the program
 * @param argc - number of arguments
 * @param argv - parameters in command line
 * @return 0 iff the program succeed
 */
int main(int argc, char *argv[])
{
    if (argc > TOO_MUCH_ARGS)
    {
        fprintf(stderr, IO_ERROR_MSG);
        return IO_ERROR;
    }
    FILE *inputFile = fopen(argv[1], "rt");
    if (inputFile == NULL)
    {
        fprintf(stderr, strcat(argv[0], SUPPLY_FILE_MSG));
        return SUPPLY_FILE;
    }
    int numOfError = reader(inputFile, argv[0]);
    fileCheckClosing(inputFile);
    return numOfError;
}


/**
 * Manage the reading from file. the first line is the dimension of the table and the other his the
 * unsolved sudoku table
 * @param inputFile - include the dimension of the sudoku table and the initial unsolved sudoku that
 * we need to solve
 * @return 0 iff the program succeed, else return non zero number that represent specific error
 */
int reader(FILE *inputFile, char *filename)
{
    char line[LINE_MAX_SIZE];
    // check if fgets failed
    if (!fgets(line, LINE_MAX_SIZE, inputFile))
    {
        fprintf(stderr, strcat(filename, NOT_VALID_MSG));
        return NOT_VALID;
    }
    const unsigned int N = (unsigned int) checkToken(line);
    // check if we get a valid size for the sudoku table
    if (checkDimension(N))
    {
        fprintf(stderr, strcat(filename, NOT_VALID_MSG));
        return NOT_VALID;
    }
    SudokuNode *sudokuNode = malloc(sizeof(SudokuNode));
    sudokuNode->size = N;
    int flag = 0;       // flag that indicate if was a error with the values
    for (unsigned int i = 0; i < N; ++i)
    {
        if (!fgets(line, LINE_MAX_SIZE, inputFile))
        {
            freeNode(sudokuNode);
            fprintf(stderr, strcat(filename, NOT_VALID_MSG));
            return NOT_VALID;
        }
        flag = insertElements(sudokuNode->sudokuTable, N, line, i);
        // checking if we get some not valid value
        if (flag != 0)
        {
            fprintf(stderr, strcat(filename, NOT_VALID_MSG));
            freeNode(sudokuNode);
            return NOT_VALID;
        }
    }
    pNode bestNode = getBest(sudokuNode, getNodeChildren, getNodeVal, freeNode, copy, (N * N));
    // check if we found solution for this sudoku table
    if (getNodeVal(bestNode) != (N * N))
    {
        fprintf(stderr, NO_SOLUTION_MSG);
        freeNode(bestNode);
        freeNode(sudokuNode);
        return NO_SOLUTION;
    }
    SudokuNode sudokuSolved = *(SudokuNode*) bestNode;
    printTable(sudokuSolved);
    freeNode(bestNode);
    freeNode(sudokuNode);
    return EXIT_SUCCESS;
}


/**
 * This function check if closing input file has succeed
 * @param inputFile - include practice examples and data to tag
 */
void fileCheckClosing(FILE *inputFile)
{
    if (fclose(inputFile) == EOF)
    {
        fprintf(stderr, CLOSING_FILE_ERROR_MSG);
        exit(CLOSING_FILE_ERROR);
    }
}
