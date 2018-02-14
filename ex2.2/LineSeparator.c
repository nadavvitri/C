#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "LineSeparator.h"

//***************************Function Declaration***************************//
int innerProduct(const double vectorX[], const double vectorY[], int dimension);
void updateVector(double vector[], int *tag, char *line, int dimension);
void updateW(double W[], int yTag, const double vectorX[], int dimension);
void exampleToTag(char *line, double W[], double X[], int dimension);
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
    FILE *inputFile = fopen(argv[FIRST_ARG], "rt");
    if (inputFile == NULL)
    {
        fprintf(stderr, IO_ERROR_MSG);
        return IO_ERROR;
    }
    reader(inputFile);
    fileCheckClosing(inputFile);
    return 0;
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


/**
 * Calculate the standard inner product of two vectors
 * @param vectorX - vector number 1
 * @param vectorY - vector number 2
 * @param dimension - the dimension of the vectors
 * @return 1 if the product is positive, else -1
 */
int innerProduct(const double vectorX[], const double vectorY[], int dimension)
{
    double product = 0;
    for (int i = 0; i < dimension; ++i)
    {
        product += vectorX[i] * vectorY[i];
    }
    if (product >= LOWER_BOUND_POSITIVE)
    {
        return POSITIVE_DOT;
    }
    return NEGATIVE_DOT;
}


/**
 * Update the W vector coordinates by parsing the line and insert every coordinate to the vector
 * coordinates array
 * @param vector - to update his coordinates
 * @param line - the line we parse and get every coordinate
 * @param dimension - the dimension of vector
 */
void updateVector(double vector[], int *tag, char *line, int dimension)
{
    char  *token;
    token = strtok(line, ",");
    double x = strtod(token, NULL);
    vector[FIRST_COORDINATE] = x;
    for (int i = 1; i < dimension; ++i)
    {
        token = strtok(NULL, ",");
        x = strtod(token, NULL);
        vector[i] = x;
    }
    token = strtok(NULL, ",");
    *tag =  (int) strtol(token, NULL, BASE);
}


/**
 * Update vector W according to the formula: W = W + yTag*(vector) given in ex2.pdf
 * @param W - vector W to update
 * @param yTag - the inner product of <w|vector>
 * @param vectorX - some vector that given in the input file
 * @param dimension - the dimension of vectors
 */
void updateW(double W[], int yTag, const double vectorX[], int dimension)
{
    for (int i = 0; i < dimension; ++i)
    {
        W[i] = W[i] + yTag * vectorX[i];
    }
}


/**
 * Got vector X for example and vector W and calculate <X|W> by the innerProduct function and print
 * the result
 * @param line - current line in from the input file
 * @param W - vector W
 * @param dimension - the dimension of vectors
 */
void exampleToTag(char *line, double W[], double X[], int dimension)
{
    char  *token;
    token = strtok(line, ",");
    double coordinate = strtod(token, NULL);
    X[FIRST_COORDINATE] = coordinate;
    for (int i = 1; i < dimension; ++i)
    {
        token = strtok(NULL, ",");
        coordinate = strtod(token, NULL);
        X[i] = coordinate;
    }
    int result = innerProduct(X, W, dimension);
    printf("%d\n", result);
}


/**
 * Manage the reading from file - the 2 first line represent the dimension and the number of lines
 * that has the description of dot in the space. Then the send the line to create the vector
 * @param inputFile - include practice examples and data to tag
 */
void reader(FILE *inputFile)
{
    char line1[LINE_MAX_SIZE];
    fgets(line1, LINE_MAX_SIZE, inputFile);
    const int N = (int) strtol(line1, NULL, BASE);
    assert(N > 1);
    fgets(line1, LINE_MAX_SIZE, inputFile);
    const int M = (int) strtol(line1, NULL, BASE);
    assert(M >= 1);
    double W[MAX_DIMENSION] = {0}, X[MAX_DIMENSION];
    Vector vector;
    // m lines with description of dot in the space and her suitable tag
    for (int i = 0; i < M; ++i)
    {
        fgets(line1, LINE_MAX_SIZE, inputFile);
        updateVector(vector.coordinates, &vector.tag, line1, N);
        int yTag = innerProduct(vector.coordinates, W, N);
        // if yTag != tag >> W = W + yTag*(vector)
        if (yTag != vector.tag)
        {
            updateW(W, vector.tag, vector.coordinates, N);
        }
    }
    // lines with examples to tag
    while (fgets(line1, LINE_MAX_SIZE, inputFile) != NULL)
    {
        exampleToTag(line1, W, X, N);
    }
}

