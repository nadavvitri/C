#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//**********************************Define**********************************//
#define ALPHA 0.012299L
#define BETA (1 - ALPHA)
#define LINE_SIZE 255
#define EXIT_SUCCESS 0
#define TOO_MANY_ARGS 1
#define IO_ERROR 2
#define IS_NOT_INTEGER 3
#define TIME_CANT_BE_NEGATIVE 4
#define M_NOT_DIVIDE_N 5
#define NOT_NUMBER 6
#define STEPS_CANT_BE_NEGATIVE 7
//**************************************************************************//


//***************************Function Declaration***************************//
long double calculateD1(long double xCurPos, long double yCurPos);
long double calculateD2(long double xCurPos, long double yCurPos);
long double calculateXVelocity(long double xCurPos, long double yCurVelocity, long double d1,
                               long double d2);
long double calculateYVelocity(long double yCurPos, long double xCurVelocity, long double d1,
                               long double d2);
void isInteger(long double number1, long double number2);
void checkStepsNumbers (long totalSteps, long stepsToSave);
long double checkInput(char *argv);
void calculateArenstorfOrbit(long double xCurPos, long double yCurPos, long double xCurVelocity,
                             long double yCurVelocity, long double totalTime,
                             long numOfSteps, long numStepsToSave, FILE *outputFile);
int inputFromFile (FILE *inputFile, FILE *outputFile);
long double posXFromUser();
long double posYFromUser();
long double velXFromUser();
long double velYFromUser();
long double totalTimeFromUser();
long numOfStepsFromUser();
long numOfStepsToSaveFromUser();
long checkStepsInput(char *argv);
//**************************************************************************//

/**
 * @brief this is the main function that run the program. there is 2 different ways to get the
 * parameters to calculate
 * the Arenstorf orbit - 1. Get the parameters from the user keyboard   2. get the parameters from
 * file.
 * @param argc - number of the program argument.
 * @param argv - if we got the parameters from the user keyboard the first argument is the output
 * file for the results.
 * if we got the parameters from file so the first argument is the file with the parameters and the
 * second argument for the result.
 * @return 0 iff the program run without any errors.
 */
int main(int argc, char *argv[])
{
    // way 2: we getting the parameters from file
    if (argc == 3)
    {
        FILE *inputFile = fopen(argv[1], "rt");
        FILE *outputFile = fopen(argv[2], "w+");
        if (!inputFile || !outputFile)
        {
            fprintf(stderr, "ERROR: couldn't open file!");
            return  (IO_ERROR);
        }
        inputFromFile(inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }
    else if (argc > 3)        // to many arguments
    {
        fprintf(stderr, "ERROR: Too many arguments!");
        return (TOO_MANY_ARGS);
    }
    else
    {
        // way 1: we getting the parameters from user keyboard
        FILE *outputFile = fopen(argv[1], "w+");
        if (!outputFile)
        {
            fprintf(stderr, "ERROR: couldn't open file!");
            return (IO_ERROR);
        }
        long double initPosX = posXFromUser();
        long double initPosY = posYFromUser();
        long double initVelX = velXFromUser();
        long double initVelY = velYFromUser();
        long double totalTime = totalTimeFromUser();
        long numOfSteps = numOfStepsFromUser();
        long numStepsToSave = numOfStepsToSaveFromUser();
        calculateArenstorfOrbit(initPosX, initPosY, initVelX, initVelY, totalTime, numOfSteps,
                                numStepsToSave, outputFile);
        fclose(outputFile);
    }
    return EXIT_SUCCESS;
}


/**
 * @brief calculate the D1 of the Arenstorf formula.
 * @param xCurPos - the current body position in axle x.
 * @param yCurPos - the current body position in axle y.
 * @return D1 according to Arenstorf formula.
 */
long double calculateD1(long double xCurPos, long double yCurPos)
{
    long double d1 = powl(xCurPos + ALPHA, 2) + powl(yCurPos, 2);
    return powl(d1, 1.5);
}

/**
 * @brief calculate the D2 of the Arenstorf formula.
 * @param xCurPos - the current body position in axle x.
 * @param yCurPos - the current body position in axle y.
 * @return D2 according to Arenstorf formula.
 */
long double calculateD2(long double xCurPos, long double yCurPos)
{
    long double d2 = powl(xCurPos - BETA, 2) + powl(yCurPos, 2);
    return powl(d2, 1.5);
}

/**
 * @brief calculate the velocity in a specific point x.
 * @param xCurPos - the current body position in axle x.
 * @param yCurVelocity - the current body velocity in axle y.
 * @param d1 - D1 according to Arenstorf formula.
 * @param d2 - D2 according to Arenstorf formula.
 * @return the velocity according to Arenstorf formula.
 */
long double calculateXVelocity(long double xCurPos, long double yCurVelocity, long double d1,
                               long double d2)
{
    long double xVelocity = (xCurPos + 2 * (yCurVelocity) - BETA * ((xCurPos + ALPHA) / d1) -
            (ALPHA) * ((xCurPos - BETA) / d2));
    return xVelocity;
}

/**
 * @brief calculate the velocity in a specific point y.
 * @param yCurPos - the current body position in axle y.
 * @param xCurVelocity - the current body velocity in axle x.
 * @param d1 - D1 according to Arenstorf formula.
 * @param d2 - D2 according to Arenstorf formula.
 * @return the velocity according to Arenstorf formula.
 */
long double calculateYVelocity(long double yCurPos, long double xCurVelocity, long double d1,
                               long double d2)
{
    long double yVelocity = (yCurPos - 2 * (xCurVelocity) - BETA * (yCurPos / d1)
                             - ALPHA * (yCurPos / d2));
    return yVelocity;
}

/**
 * @brief check if the number of steps and steps to save are Integer.
 * @param number1 - number of total steps.
 * @param number2 - number of steps to save.
 */
void isInteger(long double number1, long double number2)
{
    long cropped1 = (long)number1;
    long cropped2 = (long)number2;
    if ((cropped1 != number1) || (cropped2 != number2))
    {
        fprintf(stderr, "ERROR: steps have to be integers...");
        exit (IS_NOT_INTEGER);
    }
}

/**
 * @brief check if the number of steps to save and steps to save are Integer.is divisor of
 * total steps.
 * @param stepsToSave - number of steps to save.
 * @param totalSteps - number of total steps.
 */
void checkStepsNumbers (long totalSteps, long stepsToSave)
{
    if ((int)totalSteps % (int)stepsToSave != 0)
    {
        fprintf(stderr, "ERROR: The number of steps to save has to be divisor of total number "
                "of steps...");
        exit (M_NOT_DIVIDE_N);
    }
}

/**
 * @brief the function get's some string and check if he is valid number.
 * @param argv - string to check.
 * @return the initial part of the string  in str converts to a long double int value.
 */
long double checkInput(char *argv)
{
    if (*argv == '\n')
    {
        fprintf(stderr, "ERROR: You don't enter a number...");
        exit (NOT_NUMBER);
    }
    char *next;
    long double val;
    val = strtold(argv, &next);
    // Check for empty string and characters left after conversion.
    if ((next == argv) || (*next != '\0'))
    {
        if (*next != '\n')
        {
            fprintf(stderr, "ERROR: You don't enter a number...");
            exit (NOT_NUMBER);
        }
    }
    return val;
}


/**
 * @brief the function get's some string and check if he is valid number.
 * @param argv - string to check.
 * @return the initial part of the string  in str converts to a long int value.
 */
long checkStepsInput(char *argv)
{
    if (*argv == '\n')
    {
        fprintf(stderr, "ERROR: You don't enter a number...");
        exit (NOT_NUMBER);
    }
    char *next;
    long val;
    val = strtol(argv, &next, 10);
    // Check for empty string and characters left after conversion.
    if ((next == argv) || (*next != '\0'))
    {
        if (*next != '\n')
        {
            fprintf(stderr, "ERROR: You don't enter a number...");
            exit (NOT_NUMBER);
        }
    }
    return val;
}

/**
 * @brief this function calculate the Arenstorf orbit according to the advance period time dt and
 * print the results
 * in output file.
 * @param xCurPos - the current body position in axle x.
 * @param yCurPos - the current body position in axle y.
 * @param xCurVelocity - the current body velocity in axle x.
 * @param yCurVelocity - the current body velocity in axle y.
 * @param outputFile - output file to write the result.
 */
void calculateArenstorfOrbit(long double xCurPos, long double yCurPos, long double xCurVelocity,
                             long double yCurVelocity, long double totalTime,
                             long numOfSteps, long numStepsToSave, FILE *outputFile)
{
    long double d1, d2, a_x, a_y;
    long double dt = (double)totalTime / numOfSteps;
    long step = numOfSteps / numStepsToSave;
    checkStepsNumbers(numOfSteps, numStepsToSave);
    // check if number of steps > 0
    if ((numOfSteps < 0) || (numStepsToSave < 0))
    {
        fprintf(stderr, "Error: Steps can't be negative...");
        exit(STEPS_CANT_BE_NEGATIVE);
    }
    for (int i = 0; i <= (numOfSteps - step); i++)
    {
        d1 = calculateD1(xCurPos, yCurPos);
        d2 = calculateD2(xCurPos, yCurPos);
        a_x = calculateXVelocity(xCurPos, yCurVelocity, d1, d2);
        a_y = calculateYVelocity(yCurPos, xCurVelocity, d1, d2);
        xCurPos += xCurVelocity * dt;
        yCurPos += yCurVelocity * dt;
        xCurVelocity += a_x * dt;
        yCurVelocity += a_y * dt;
        if (totalTime < 0)
        {
            fprintf(stderr, "ERROR: there is no negative time...");
            exit(TIME_CANT_BE_NEGATIVE);
        }
        // check if number of steps is integer
        isInteger(numOfSteps, numStepsToSave);
        // check if numOfSteps % numStepsToSave = 0
        if ((i % step == 0) && i != (numOfSteps - step))
        {
            fprintf(outputFile, "%.3Le, %.3Le, ", xCurPos, yCurPos);
        }
    }
    fprintf(outputFile, "%.3Le, %.3Le\n", xCurPos, yCurPos);
}


/**
 * @brief this function call when the information gets from a input file. the function get's the
 * information from the
 * file and call to calculateArenstorfOrbit with them.
 * @param inputFile - file with the information.
 * @param outputFile - output file to write the result.
 * @return 0 iff the function success.
 */
int inputFromFile (FILE *inputFile, FILE *outputFile)
{
    char line1[LINE_SIZE], line2[LINE_SIZE];
    char *X, *Y, *Vx, *Vy, *T, *N, *M;
    fgets(line1, LINE_SIZE, inputFile);
    fgets(line2, LINE_SIZE, inputFile);
    X = strtok(line1, ",");
    Y = strtok(NULL, ",");
    Vx = strtok(NULL, ",");
    Vy = strtok(NULL, ",");
    if (strtok(NULL, ",") != NULL)
    {
        fprintf(stderr, "ERROR: Too many arguments in line!");
        exit (TOO_MANY_ARGS);
    }
    T = strtok(line2, ",");
    N = strtok(NULL, ",");
    M = strtok(NULL, ",");
    if (strtok(NULL, ",") != NULL)
    {
        fprintf(stderr, "ERROR: Too many arguments in line!");
        exit (TOO_MANY_ARGS);
    }
    long double initPosX = checkInput(X);
    long double initPosY = checkInput(Y);
    long double initVelX = checkInput(Vx);
    long double initVelY = checkInput(Vy);
    long double totalTime = checkInput(T);
    long numOfSteps = checkStepsInput(N);
    long numStepsToSave = checkStepsInput(M);
    checkStepsNumbers(numOfSteps, numStepsToSave);
    calculateArenstorfOrbit(initPosX, initPosY, initVelX, initVelY, totalTime, numOfSteps,
                            numStepsToSave, outputFile);
    return EXIT_SUCCESS;
}

/**
 * @brief get's the initial X position from the user input.
 * @return initial X position.
 */
long double posXFromUser()
{
    char X[sizeof(long double)];
    printf("Enter initial pos x:\n");
    fgets(X, sizeof(long double), stdin);
    long double initPosX = checkInput(X);
    return initPosX;
}

/**
 * @brief get's the initial Y position from the user input.
 * @return initial Y position.
 */
long double posYFromUser()
{
    char Y[sizeof(long double)];
    printf("Enter initial pos y:\n");
    fgets(Y, sizeof(long double), stdin);
    long double initPosY = checkInput(Y);
    return initPosY;
}

/**
 * @brief get's the initial X velocity from the user input.
 * @return initial X velocity.
 */
long double velXFromUser()
{
    char Vx[sizeof(long double)];
    printf("Enter initial vel x:\n");
    fgets(Vx, sizeof(long double), stdin);
    long double initVelX = checkInput(Vx);
    return initVelX;
}

/**
 * @brief get's the initial Y velocity from the user input.
 * @return initial Y velocity.
 */
long double velYFromUser()
{
    char Vy[sizeof(long double)];
    printf("Enter initial vel y:\n");
    fgets(Vy, sizeof(long double), stdin);
    long double initVelY = checkInput(Vy);
    return initVelY;
}

/**
 * @brief get's the total time from the user input.
 * @return total time.
 */
long double totalTimeFromUser()
{
    char T[sizeof(long double)];
    printf("Enter total time T:\n");
    fgets(T, sizeof(long double), stdin);
    long double totalTime = strtold(T, NULL);
    return totalTime;
}

/**
 * @brief get's the number of steps from the user input.
 * @return number of steps.
 */
long numOfStepsFromUser()
{
    char N[sizeof(long double)];
    printf("Enter num of steps:\n");
    fgets(N, sizeof(long double), stdin);
    long numOfSteps = strtol(N, NULL, 10);
    return numOfSteps;
}

/**
 * @brief get's the number of steps to save from the user input.
 * @return number of steps to save.
 */
long numOfStepsToSaveFromUser()
{
    char M[sizeof(long double)];
    printf("Enter num of steps to save:\n");
    fgets(M, sizeof(long double), stdin);
    long numStepsToSave = strtol(M, NULL, 10);
    return numStepsToSave;
}