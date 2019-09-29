/*================================================================================================*/
/* Demonstration of the usage decimal fraction (DF) numbers arithmetic module.                    */
/* Author: Ihar Areshchankau, 2019.                                                               */
/* You may use Digital Mars C++ compiler (https://www.digitalmars.com/download/freecompiler.html) */
/* to build demo.exe this way:                                                                    */
/* dmc.exe demo.c iadf.c                                                                          */
/*================================================================================================*/
#include "stdio.h"
#include "iadf.h"
/*--------------------------------------------------------------------*/
/* The string representation buffer must have a place enough to hold: */
/* - IADFCAPACITY decimal fraction digits,                            */
/* - sign for negative numbers,                                       */
/* - decimal point,                                                   */
/* - leading "zero" for the nubmers: abs (c) < 1.0,                   */
/* - ASCIIZ string terminator.                                        */
/* Therefore N = IADFCAPACITY + 4.                                    */
/*--------------------------------------------------------------------*/
#define N (IADFCAPACITY + 4)
int main ()
{
	char a[] = "1234.56789";
	char b[] = "-98765.4321";
	char c[N];
	
	struct IADF dfa, dfb;
	
	/* Addition: c = a + b. */	
	iadfInit (&dfa, a);
	iadfInit (&dfb, b);
	iadfAdd (&dfa, &dfb);
	iadfToStr (&dfa, c, N);
	printf ("Addition: (%s) + (%s) = (%s)\n", a, b, c);
	
	/* Subtraction: c = a - b. */
	iadfInit (&dfa, a);
	iadfSub (&dfa, &dfb);
	iadfToStr (&dfa, c, N);
	printf ("Subtraction: (%s) - (%s) = (%s)\n", a, b, c);
	
	/* Multiplication: c = a * b. */
	iadfInit (&dfa, a);
	iadfMul (&dfa, &dfb);
	iadfToStr (&dfa, c, N);
	printf ("Multiplication: (%s) * (%s) = (%s)\n", a, b, c);

	/* Division: c = a / b. */
	iadfInit (&dfa, a);
	iadfDiv (&dfa, &dfb);
	iadfToStr (&dfa, c, N);
	printf ("Division: (%s) / (%s) = (%s)\n", a, b, c);
	
	return 0;
}
