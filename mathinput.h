#ifndef __mathinput_H__
#define __mathinput_H__

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include <math.h>

#define INVALID "You must enter a valid number.\n"

typedef struct term
{
	double coefficient;
	double power;
} term;

typedef struct range
{
	double start;
	size_t count;
	double end;
} range;

int get_equation(term **result, size_t *length)
{
	debug("Entering get_equation");
	check(result != NULL, "result can't be null.");
	check(length != NULL, "length can't be null.");

	size_t i;
	int rc;

	printf("How many terms are there? ");
	rc = scanf("%zu", length);
	printf("\n");
	check(*length > 0 && rc > 0, INVALID);
	
	*result = calloc(*length, sizeof(term)); 
	
	for (i = 0; i < *length; i++)
	{
		printf("Enter coefficient of term %zu: ", i + 1);
		rc = scanf("%lf", &(*result)[i].coefficient);
		printf("\n");
		
		check(rc > 0, INVALID);
		
		printf("Enter power of term %zu: ", i + 1);
		rc = scanf("%lf", &(*result)[i].power);
		printf("\n");
		
		check(rc > 0, INVALID);
	}

	debug("Exiting get_equation");

	return 0;

error:
	return 1;
}

int get_range(range *result)
{
	debug("Entering get_range");
	check(result != NULL, "result can't be null.");

	int rc;

	printf("Enter the start of the range: ");
	rc = scanf("%lf", &result->start);
	printf("\n");

	check(rc > 0 && result->start, INVALID);
	
	printf("Enter end in the range: ");
	rc = scanf("%lf", &result->end);
	printf("\n");

	check(rc > 0 && result->end > 0, INVALID);
	
	printf("Enter the count of the range: ");
	rc = scanf("%zu", &result->count);
	printf("\n");

	check(rc > 0 && result->count > 0, INVALID);
	debug("Exiting get_range");

	return 0;

error:
	return 1;
}

int find_y(term *equation, size_t length, double x, double *out_ptr)
{
	debug("Entering function find_y.");
	check(equation != NULL, "equation can't be null");
	check(length > 0, "length must be greater than 0");
	check(out_ptr != NULL, "out_ptr can't be null");

	*out_ptr = 0;
	size_t i;
	
	for (i = 0; i < length; i++)
	{
		*out_ptr += equation[i].coefficient * pow(x, equation[i].power);
	}

	debug("Exiting function find_y.");

	return 0;

error:
	return 1;
}

#endif
