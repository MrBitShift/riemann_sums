#include <stdio.h>
#include "mathinput.h"
#include "dbg.h"

#define INVALID_FUNC "You must enter a valid number.\n"

typedef struct riemann_func
{
	char *name;
	int (*func)(term*, size_t, range, double*);
} riemann_func;


// forward declarations
int left_sum(term *terms, size_t t_length, range r, double* result);
int right_sum(term *terms, size_t t_length, range r, double* result);
int midpoint_sum(term *terms, size_t t_length, range r, double* result);
int trapezoid_sum(term *terms, size_t t_length, range r, double *result);
	
// globals
int globals_init = 0;
const size_t num_funcs = 4;
riemann_func left_sum_func;
riemann_func right_sum_func;
riemann_func midpoint_sum_func;
riemann_func trapezoid_sum_func;

riemann_func *functions;

void init_globals()
{
	debug("Entering init_globals");
	if (globals_init) return;
	functions = calloc(num_funcs, sizeof(riemann_func));

	left_sum_func.name = "Left Riemann Sum";
	left_sum_func.func = left_sum;
	functions[0] = left_sum_func;
	
	right_sum_func.name = "Right Riemann Sum";
	right_sum_func.func = right_sum;
	functions[1] = right_sum_func;

	midpoint_sum_func.name = "Midpoint Riemann Sum";
	midpoint_sum_func.func = midpoint_sum;
	functions[2] = midpoint_sum_func;

	trapezoid_sum_func.name = "Trapezoid Riemann Sum";
	trapezoid_sum_func.func = trapezoid_sum;
	functions[3] = trapezoid_sum_func;

	globals_init = 1;

	debug("Exiting init_globals");
}

void free_globals()
{
	debug("Entering free_globals");
	
	free(functions);
	
	debug("Exiting free_globals");
}

int get_func(riemann_func *func)
{
	debug("Entering get_func");
	init_globals();
	check(func != NULL, "func can't be null.");
	
	int rc;
	int function;
	size_t i;

	printf("Choose which function you want to use.\n");
	for (i = 0; i < num_funcs; i++)
	{
		printf("%zu: %s\n", i, functions[i].name);
	}
	
	rc = scanf("%d", &function);
	check(function >= 0 && function < num_funcs && rc > 0, INVALID_FUNC);

	*func = functions[function];

	debug("Exiting get_func");
	return OPERATION_SUCCESS;

error:
	debug("Failure in get_func");
	return OPERATION_FAILURE;
}

int left_sum(term *terms, size_t t_length, range r, double *result)
{
	debug("Entering left_sum");
	init_globals();

	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");

	size_t i;
	double b;
	double interval = (r.end - r.start) / r.count;
	double *tmp = calloc(1, sizeof(double));
	*result = 0;

	for (i = 0, b = r.start; i < r.count; i++, b += interval)
	{
		check(find_y(terms, t_length, b, tmp) == OPERATION_SUCCESS, "Could not calculate.");
		*result += *tmp;
	}

	*result *= interval;
	
	debug("Freeing structures");
	free(tmp);
	
	debug("Exiting left_sum");
	return OPERATION_SUCCESS;

error:
	debug("Failure in left_sum");
	return OPERATION_FAILURE;
}

int right_sum(term *terms, size_t t_length, range r, double *result)
{
	debug("Entering right_sum");
	init_globals();
	
	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");

	size_t i;
	double b;
	double interval = (r.end - r.start) / r.count;
	*result = 0;

	for (i = 0, b = r.start + interval; i < r.count; i++, b += interval)
	{
		double *tmp = calloc(1, sizeof(double));
		check(find_y(terms, t_length, b, tmp) == OPERATION_SUCCESS, "Could not calculate.");
		*result += *tmp;
	}

	*result *= interval;
	
	debug("Exiting right_sum");
	return OPERATION_SUCCESS;

error:
	debug("Failure in right_sum");
	return OPERATION_FAILURE;

}

int midpoint_sum(term *terms, size_t t_length, range r, double *result)
{
	debug("Entering midpoint_sum.");
	init_globals();
	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");

	size_t i;
	double b;
	double interval = (r.end - r.start) / r.count;
	*result = 0;

	for (i = 0, b = r.start + (interval / 2); i < r.count; i++, b += interval)
	{
		double *tmp = calloc(1, sizeof(double));
		check(find_y(terms, t_length, b, tmp) == OPERATION_SUCCESS, "Could not calculate.");
		*result += *tmp;
	}

	*result *= interval;
	
	debug("Exiting midpoint_sum.");
	return OPERATION_SUCCESS;

error:
	debug("Failure in midpoint_sum");
	return OPERATION_FAILURE;
}

int trapezoid_sum(term *terms, size_t t_length, range r, double *result)
{
	debug("Entering trapezoid_sum");
	init_globals();

	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");

	size_t i;
	double b;
	double c;
	double interval = (r.end - r.start) / r.count;
	*result = 0;

	for (i = 0, b = r.start, c = r.start + interval; i < r.count; 
		i++, b += interval, c += interval)
	{
		double *tmp1 = calloc(1, sizeof(double));
		double *tmp2 = calloc(1, sizeof(double));
		check(find_y(terms, t_length, b, tmp1) == OPERATION_SUCCESS, "Could not calculate.");
		check(find_y(terms, t_length, c, tmp2) == OPERATION_SUCCESS, "Could not calculate.");
		*result += (*tmp1 + *tmp2) / 2;
	}

	*result *= interval;
	
	debug("Exiting trapezoid_sum");
	return OPERATION_SUCCESS;

error:
	debug("Failure in trapezoid_sum");
	return OPERATION_FAILURE;
}

