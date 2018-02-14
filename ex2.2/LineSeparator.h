//
// Created by nadav vitri on 10/08/2017.
//

#ifndef EX2_2_LINESEPARATOR_H
#define EX2_2_LINESEPARATOR_H

//**********************************Define**********************************//
#define LINE_MAX_SIZE 400
#define MAX_DIMENSION 200
#define POSITIVE_DOT 1
#define NEGATIVE_DOT (-1)
#define TOO_MUCH_ARGS 2
#define IO_ERROR 3
#define FIRST_ARG 1
#define BASE 10
#define FIRST_COORDINATE 0
#define CLOSING_FILE_ERROR 4
#define LOWER_BOUND_POSITIVE 0.00001
#define IO_ERROR_MSG "Error: Please check your arguments!"
#define CLOSING_FILE_ERROR_MSG "Error: Some error happen with closing input file!!"
//**************************************************************************//

//***************************Function Declaration***************************//
/**
 * Manage the reading from file - the 2 first line represent the dimension and the number of lines
 * that has the description of dot in the space. Then the send the line to create the vector
 * @param inputFile - include practice examples and data to tag
 */
void reader(FILE *inputFile);
//**************************************************************************//

/**
 * This struct represent vector that have field for his coordinates and second field for his tag
 */
typedef struct MyStruct
{
    double coordinates[MAX_DIMENSION];
    int tag;
} Vector;


#endif //EX2_2_LINESEPARATOR_H
