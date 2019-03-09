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
	double interval;
	size_t count;
} range;

int get_equation(term **result, size_t *length)
{
	check(result != NULL, "result can't be null.");
	check(length != NULL, "length can't be null.");

	size_t i;
	int rc;

	printf("How many terms are there? ");
	rc = scanf("%zu", length);
	printf("\n");
	check(*length > 0 && rc > 0, INVALID);
	log_info("length: %zu\n", *length);
	
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

	return 0;

error:
	return 1;
}

int find_y(term *equation, size_t length, double x, double *out_ptr)
{
	check(equation != NULL, "equation can't be null");
	check(length > 0, "length must be greater than 0");
	check(out_ptr != NULL, "out_ptr can't be null");

	size_t i;
	double result = 0;
	log_info("x: %lf out: %lf", x, *out_ptr);
	
	for (i = 0; i < length; i++)
	{
		result += equation[i].coefficient * pow(x, equation[i].power);
	}
	
	*out_ptr = result;
	return 0;

error:
	return 1;
}

int get_range(range *result)
{
	check(result != NULL, "result can't be null.");

	int rc;

	printf("Enter the start of the range: ");
	rc = scanf("%lf", &result->start);
	printf("\n");

	check(rc > 0 && result->start, INVALID);
	
	printf("Enter interval in the range: ");
	rc = scanf("%lf", &result->interval);
	printf("\n");

	check(rc > 0 && result->interval > 0, INVALID);
	
	printf("Enter count in the range: ");
	rc = scanf("%zu", &result->count);
	printf("\n");

	check(rc > 0 && result->count > 0, INVALID);

	return 0;

error:
	return 1;
}
#endif
