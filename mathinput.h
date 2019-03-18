#ifndef __mathinput_H__
#define __mathinput_H__

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include <math.h>

#define INVALID "You must enter a valid number."

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
	
	*length = -1;

	size_t i;
	int rc;

	printf("How many terms are there? ");
	rc = scanf("%zu", length);
	check(*length > 0 && rc > 0, INVALID); 
	
	free(*result);
	*result = calloc(*length, sizeof(term)); 
	
	for (i = 0; i < *length; i++)
	{
		printf("Enter coefficient of term %zu: ", i + 1);
		rc = scanf("%lf", &(*result)[i].coefficient);
		check(rc > 0, INVALID);
		
		printf("Enter power of term %zu: ", i + 1);
		rc = scanf("%lf", &(*result)[i].power);
		check(rc > 0, INVALID);
	}

	debug("Exiting get_equation");

	return OPERATION_SUCCESS;

error:
	debug("Failure in get_equation");
	return OPERATION_FAILURE;
}

int get_range(range *result)
{
	int rc;
	debug("Entering get_range");
	check(result != NULL, "result can't be null.");

	printf("Enter the start of the range: a=");
	rc = scanf("%lf", &result->start);
	check(rc > 0, INVALID);
	
	printf("Enter end in the range: b=");
	rc = scanf("%lf", &result->end);
	check(rc > 0, INVALID);
	
	printf("Enter the count of the range: n=");
	rc = scanf("%zu", &result->count);
	check(rc > 0 && result->count > 0, INVALID);
	
	debug("Exiting get_range");
	return OPERATION_SUCCESS;

error:
	debug("Failure in get_range");
	return OPERATION_FAILURE;
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
	return OPERATION_SUCCESS;

error:
	debug("Failure in find_y");
	return OPERATION_FAILURE;
}

#endif
