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
//int right_sum(term *terms, size_t t_length, range r, double* result);
//int midpoint_sum(term *terms, size_t t_length, range r, double* result);
//int trapezoid_sum(term *terms, size_t t_length, range r, double *result);
	
// globals
int globals_init = 0;
const size_t num_funcs = 1;
riemann_func left_sum_func;
//riemann_func right_sum_func;
//riemann_func midpoint_sum_func;
//riemann_func trapezoid_sum_func;

riemann_func *functions;

void init_globals()
{
	if (globals_init) return;
	left_sum_func.name = "Left Riemann Sum";
	left_sum_func.func = left_sum;
	
	functions = calloc(num_funcs, sizeof(riemann_func));
	functions[0] = left_sum_func;

	globals_init = 1;
}


int get_func(riemann_func *func)
{
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
	return 0;

error:
	return 1;
}

int left_sum(term *terms, size_t t_length, range r, double *result)
{
	init_globals();
	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");

	size_t i;
	double b;
	*result = 0;
	log_info("left_sum called. \n");

	for (i = 0, b = r.start; i < r.count; i++, b += r.interval)
	{
		double *tmp = calloc(1, sizeof(double));
		check(find_y(terms, t_length, b, tmp) == 0, "Could not calculate.");
		*result += *tmp;
		log_info("result: %lf", *result);
	}
	
	return 0;

error:
	return 1;
}
