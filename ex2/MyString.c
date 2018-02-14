#include <stdio.h>
#include "MyString.h"

//**********************************Define**********************************//
#define MATCH 0
#define NO_MATCH 1
//**************************************************************************//

//***************************Function Declaration***************************//
unsigned int stringLength(const char* str);
int checkCyclic(const char* str1, const char* str2, int i);
int checkRestString(const char* str1, const char* str2, int i, int isCyclic);
//**************************************************************************//

/**
 * Counts the length of the string by iterating and count until we reach to line terminator.
 * @param str - the string
 * @return counter - the length of the string
 */
unsigned int stringLength(const char* str)
{
    unsigned int counter = 0;
    while (str[counter] != '\0')
    {
        counter++;
    }
    return counter;
}

/**
 * This function get str1 and the substring of str2 which we need to check if equals to the
 * beginning of str1(cyclic)
 * @param str - the string
 * @param the substring of str2 which we need to check if equals to the beginning of str1
 * @param i the upper bound index number when we iterate over str1
 * @return 0 if was a match, else 1
 */
int checkCyclic(const char* str1, const char* str2, int i)
{
    int str1MinusRestLength = stringLength(str1) - i;
    int str2Length = stringLength(str2);
    int k = 0;
    // we "slice" str1 and run until we reach to the upper bound
    while ((k < str1MinusRestLength || k < str2Length)  && (str1[k] == str2[k]))
    {
        k++;
    }
    // number of iteration equals to str2 length
    if (k == str2Length)
    {
        return MATCH;
    }
    return NO_MATCH;
}

/**
 * Iterating over both str2 and str1(by same index) until we reach line terminator and check if
 * they equal. If the number of iteration equals to originally str2 length then we can assure that
 * was a match. If we are in isCyclic mode then we are in case 2: send the substring of str2 which
 * we need to check if equals to the beginning of str1(cyclic) to the helper function
 * @str1 - the string
 * @str2 - the substring
 * @i - the index of the first letter in str1 that equal to the first letter in str2
 * (we found in countSubStr)
 * @isCycic != 0 - search also for cyclic appearance
 * @return 0 if was a match, else 1
 */
int checkRestString(const char* str1, const char* str2, int i, int isCyclic)
{
    int j = i;
    unsigned int p = 0;
    unsigned int str2Length = stringLength(str2);
    // run parallel index by index from where we found first letter in str1 that equal to str2
    while ((str2[p] != '\0') && (str1[j] == str2[p]))
    {
        j++;
        p++;
    }
    // number of iteration equals to originally str2 length
    if (p == str2Length)
    {
        return MATCH;
    }
    // case 2
    if (isCyclic)
    {
        if (!checkCyclic(str1, &str2[p], i))
        {
            return MATCH;
        }
    }
    return NO_MATCH;
}


/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one(or two) of the strings is empty - returns 0.
 * @str1 - the string
 * @str2 - the substring
 * @isCycic != 0 - search also for cyclic appearance
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const char* str1, const char* str2, int isCyclic)
{
    unsigned int counter = 0;
    int i = 0;
    // check if one of the strings is NULL
    if(str1 == NULL || str2 == NULL)
    {
        return 0;
    }
    while (str1[i] != '\0')
    {
        if (str1[i] == str2[0])
        {
            if (!checkRestString(str1, str2, i, isCyclic))
            {
                counter++;
            }
        }
        i++;
    }
    return counter;
}
