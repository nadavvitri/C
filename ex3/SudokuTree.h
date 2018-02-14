//
// Created by nadav vitri on 17/08/2017.
//

#ifndef EX3_SUDOKUTREE_H
#define EX3_SUDOKUTREE_H

//**********************************Define**********************************//
#include "GenericDFS.h"

#define NUMBER_APPEAR 0
#define NUMBER_DOESNT_APPEAR 1
#define BASE 10
#define NOT_VALID (-1)
#define MAX_N 100
//**************************************************************************//

//********      types and functions types
/**
 * this struct represent current sudoku table, with 2d array (default max size of 100) and hold
 * in the second field the size of the sudoku table
 */
typedef struct Node
{
    int sudokuTable[MAX_N][MAX_N];
    int size;
} SudokuNode;

/**
 * A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children
 * @param node - of pNode to check how many children he have
 * @param children - pointer to array of nodes.
 * @return int, number of children of this node
 */
int getNodeChildren(pNode, pNode** /*for the result*/);

/**
 * A function that gets a node and returns its value, as int. the value calculate by count the non
 * zero numbers in the sudoku table of the node
 * @param node - pNode (that here we cast to sudokuNode)
 * @return sum of non zero numbers on his sudoku table
 */
unsigned int getNodeVal(pNode);

/**
 * A function that do deep copy of Node.
 * @param node - of pNode to copy
 * @return copy of the node we receive
 */
pNode copy(pNode node);

/**
 * A function that get's some string (token) and check if he is valid number
 * @param token - token to check
 * @return the string converted to a int value, else the token isn't valid value and return -1
 */
int checkToken(char *token);

/**
 * A function that check if we receive valid number of table size. the number has to be positive,
 * with complete square root and have to be integer
 * @param size - the size of every line and column in the table
 * @return 0 iff the size is valid, else return -1
 */
int checkDimension(int size);

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
int isValidInsert(int sudokuTable[MAX_N][MAX_N], int row, int col, int number, int size);

/**
 * This function run over the sudoku table in search for empty location to attempt inserting there
 * number
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param size - the size (row/column) of the sudoku table
 * @return if we found empty location return array that represent empty location with row and column
 * number, else no empty location found (there is a number) and return 0
 */
int* findEmptyLocation(int sudokuTable[MAX_N][MAX_N], int size);

/**
 * Get's the sudoku table and his size and insert element that shows in line (from the file we
 * reading) and insert the numbers one by one to the cell in the specific row number
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param size - the size of every line and column in the table
 * @param line - line from the input file to parse and get's the elements from there
 * @param rowNumber - number of row of the sudoku table to insert the elements
 * @return 0 iff the sudoku table is valid, else return -1
 */
int insertElements(int sudokuTable[MAX_N][MAX_N], int size, char *line, int rowNumber);

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
int appearanceInBox(int sudokuTable[MAX_N][MAX_N], int row, int col, int number, int size);

/**
 * Check if specific number appear in the row of the sudoku Table, if the number doesn't appear we
 * can say the row is valid
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param row - number of row to check if the number appear in this row
 * @param number - number to check if he appear in the row
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the row, else 0
 */
int appearanceInRow(int sudokuTable[MAX_N][MAX_N], int row, int number, int size);

/**
 * Check if specific number appear in the column of the sudoku Table, if the number doesn't appear
 * we can say the column is valid
 * @param sudokuTable - 2d array that represent the sudoku table
 * @param col - number of column to check if the number appear in this column
 * @param number - number to check if he appear in the column
 * @param size - the size (row/column) of the sudoku table
 * @return 1 iff number doesn't appear in the column, else 0
 */
int appearanceInCol(int sudokuTable[MAX_N][MAX_N], int col, int number, int size);

/**
 * A function that print the sudoku table to the screen
 * @param sudokuNode - sudoku node (has field that represent sudoku table) to print
 */
void printTable(SudokuNode sudokuNode);

/**
 * The function get's pNode and casting the node to SudokuNode, and if he is  not null then free
 * his inner field that hold the sudoku table and then free the sudokuNode struct himself
 * @param node of pNone
 */
void freeNode(pNode node);

#endif //EX3_SUDOKUTREE_H
