#include "SudokuTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/**
 * A function that get's some string (token) and check if he is valid number
 * @param token - token to check
 * @return the string converted to a int value, else the token isn't valid value and return -1
 */
int checkToken(char *token)
{
    if (*token == '\n')
    {
        return NOT_VALID;
    }
    char *ptr;
    int value = (int) strtol(token, &ptr, BASE);
    // Check for empty string and characters left after conversion
    if ((ptr == token) || (*ptr != '\0'))
    {
        if (*ptr != '\n')
        {
            return NOT_VALID;
        }
    }
    return value;
}


/**
 * A function that check if we receive valid number of table size. the number has to be positive,
 * with complete square root and have to be integer
 * @param size - the size of every line and column in the table
 * @return 0 iff the size is valid, else return -1
 */
int checkDimension(int size)
{
    int temp = (int) sqrt(size);
    int result = (temp * temp);
    if ((size <= 0) || (result != size) || (size > MAX_N))
    {
        return NOT_VALID;
    }
    return EXIT_SUCCESS;
}


/**
 * Get's the sudoku table and his size and insert element that shows in line (from the file we
 * reading) and insert the numbers one by one to the cell in the specific row number
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param size - the size of every line and column in the table
 * @param line - line from the input file to parse and get's the elements from there
 * @param rowNumber - number of row of the sudoku table to insert the elements
 * @return 0 iff the sudoku table is valid, else return -1
 */
int insertElements(int sudokuTable[MAX_N][MAX_N], int size, char *line, int rowNumber)
{
    char  *token;
    token = strtok(line, " ");
    int value = checkToken(token);
    sudokuTable[rowNumber][0] = value;
    for (int i = 1; i < size; ++i)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            value = checkToken(token);
        }
        if ((value > size) || (value < 0) || (token == NULL))
        {
            return NOT_VALID;
        }
        sudokuTable[rowNumber][i] = value;
    }
    return EXIT_SUCCESS;
}


/**
 * Check if is valid to insert specific number in location (row and column) by checking if the
 * number doesn't appear in this row and this column and also in this box
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param row - number of row of the location
 * @param col - number of column of the location
 * @param number - number we want to check if insert him in the location is valid
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the sudoku table and it's valid insert of number, else 0
 */
int isValidInsert(int sudokuTable[MAX_N][MAX_N], int row, int col, int number, int size)
{
    if ((appearanceInBox(sudokuTable, row, col, number, size)) &&
        (appearanceInCol(sudokuTable, col, number, size)) &&
        (appearanceInRow(sudokuTable, row, number, size)))
    {
        return NUMBER_DOESNT_APPEAR;
    }
    return NUMBER_APPEAR;
}


/**
 * Check if specific number appear in box. First we find with the parameters row and col the box we
 * need to check. if number doesn't appear in the box so this box is valid
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param row - number of row to check if the number appear in his attributed box
 * @param col - number of column to check if the number appear in his attributed box
 * @param number - number we want to check if appear in this box
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the row, else 0
 */
int appearanceInBox(int sudokuTable[MAX_N][MAX_N], int row, int col, int number, int size)
{
    int boxSize = (int) sqrt(size);
    // find the upper left corner of the box
    int startInRow = row - (row % boxSize);
    int startInCol = col - (col % boxSize);
    // iterate over the box and check if the number exit in the box
    for (int i = 0; i < boxSize; ++i)
    {
        for (int j = 0; j < boxSize; ++j)
        {
            if (sudokuTable[startInRow + i][startInCol + j] == number)
            {
                return NUMBER_APPEAR;
            }
        }
    }
    return NUMBER_DOESNT_APPEAR;
}


/**
 * Check if specific number appear in the row of the sudoku Table, if the number doesn't appear we
 * can say the row is valid
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param row - number of row to check if the number appear in this row
 * @param number - number to check if he appear in the row
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the row, else 0
 */
int appearanceInRow(int sudokuTable[MAX_N][MAX_N], int row, int number, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (sudokuTable[row][i] == number)
        {
            return NUMBER_APPEAR;
        }
    }
    return NUMBER_DOESNT_APPEAR;
}

/**
 * Check if specific number appear in the column of the sudoku Table, if the number doesn't appear
 * we can say the column is valid
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param col - number of column to check if the number appear in this column
 * @param number - number to check if he appear in the column
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the column, else 0
 */
int appearanceInCol(int sudokuTable[MAX_N][MAX_N], int col, int number, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (sudokuTable[i][col] == number)
        {
            return NUMBER_APPEAR;
        }
    }
    return NUMBER_DOESNT_APPEAR;
}


/**
 * This function run over the sudoku table in search for empty location to attempt inserting there
 * number
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param size - the size (row/column) of the sudoku table
 * @return if we found empty location return array that represent empty location with row and column
 * number, else no empty location found (there is a number) and return 0
 */
int* findEmptyLocation(int sudokuTable[MAX_N][MAX_N], int size)
{
    int *location = (int*) malloc(sizeof(int) * 2);
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            if (sudokuTable[row][col] == 0)
            {
                location[0] = row;
                location[1] = col;
                return location;
            }
        }
    }
    return NUMBER_APPEAR;
}


/**
 * A function that do deep copy of Node.
 * @param node - of pNode to copy
 * @return copy of the node we receive
 */
pNode copy(pNode node)
{
    SudokuNode sudokuNode = *(SudokuNode*) node;
    SudokuNode *copy = (SudokuNode*) malloc(sizeof(SudokuNode));
    for (int row = 0; row < sudokuNode.size; ++row)
    {
        for (int col = 0; col < sudokuNode.size; ++col)
        {
            copy->sudokuTable[row][col] = sudokuNode.sudokuTable[row][col];
        }
    }
    copy->size = sudokuNode.size;
    return copy;
}


/**
 * A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children
 * @param node - of pNode to check how many children he have
 * @param children - pointer to array of nodes.
 * @return int, number of children of this node
 */
int getNodeChildren(pNode node, pNode** children /*for the result*/)
{
    SudokuNode sudokuNode = *(SudokuNode*) node;
    *children = malloc(sizeof(pNode) * sudokuNode.size);
    int numberOfChildren = 0;
    int *location = findEmptyLocation(sudokuNode.sudokuTable, sudokuNode.size);
    int j = 0;
    for (int i = 0; i < sudokuNode.size; ++i)
    {
        if (isValidInsert(sudokuNode.sudokuTable, location[0], location[1], i + 1, sudokuNode.size))
        {
            SudokuNode *copyTable = (SudokuNode*) copy(node);
            copyTable->sudokuTable[location[0]][location[1]] = i + 1;
            (*children)[j] = (pNode) copyTable;
            j++;
            numberOfChildren++;
        }
    }
    free(location);
    return numberOfChildren;
}


/**
 * A function that gets a node and returns its value, as int. the value calculate by count the non
 * zero numbers in the sudoku table of the node
 * @param node - pNode (that here we cast to sudokuNode)
 * @return sum of non zero numbers on his sudoku table
 */
unsigned int getNodeVal(pNode node)
{
    if (node == NULL)
    {
        return 0;
    }
    SudokuNode sudokuNode = *(SudokuNode*) node;
    unsigned int value = 0;
    for (int i = 0; i < sudokuNode.size; ++i)
    {
        for (int j = 0; j < sudokuNode.size; ++j)
        {
            if (sudokuNode.sudokuTable[i][j] != 0)
            {
                value++;
            }
        }
    }
    return value;
}


/**
 * The function get's pNode and casting the node to SudokuNode, and if he is  not null then free
 * his inner field that hold the sudoku table and then free the sudokuNode struct himself
 * @param node of pNone
 */
void freeNode(pNode node)
{
    // check nullity
    if (node == NULL)
    {
        return;
    }
    SudokuNode* sudokuNode = (SudokuNode*) node;
    free(sudokuNode);
}


/**
 * A function that print the sudoku table to the screen
 * @param sudokuNode - sudoku node (has field that represent sudoku table) to print
 */
void printTable(SudokuNode sudokuNode)
{
    printf("%d\n", sudokuNode.size);
    for (int row = 0; row < sudokuNode.size; ++row)
    {
        for (int col = 0; col < (sudokuNode.size - 1); ++col)
        {
            printf("%d ", sudokuNode.sudokuTable[row][col]);
        }
        printf("%d\n", sudokuNode.sudokuTable[row][sudokuNode.size - 1]);
    }
}