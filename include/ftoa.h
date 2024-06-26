#ifndef FTOA
#define FTOA

#include <math.h>
#include <stdio.h>
 
// Reverses a string 'str' of length 'len'
void reverse(char* str, int len);
 
// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d);
 
// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint);

#endif /* FTOA */
