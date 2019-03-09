#include <stdio.h>
#include "riemann_sums.h"
#include "mathinput.h"
#include "dbg.h"

/*
#define INVALID_FUNC "You must enter a valid number.\n"

typedef struct riemann_func
{
	char *name;
	int (*func)(term*, size_t, range, double*);
} riemann_func;

*/
// forward declarations
int left_sum(term *terms, size_t t_length, range r, double* result);
//int right_sum(term *terms, size_t t_length, range r, double* result);
//int midpoint_sum(term *terms, size_t t_length, range r, double* result);
//int trapezoid_sum(term *terms, size_t t_length, range r, double *result);
/*
void init_globals();
int get_func(riemann_func *func);
	
// globals
const size_t num_funcs = 1;
riemann_func left_sum_func;
//riemann_func right_sum_func;
//riemann_func midpoint_sum_func;
//riemann_func trapezoid_sum_func;

riemann_func *functions;*/


int main(int argc, char *argv[])
{
	//init_globals();
	
	int rc;
	size_t i;
	size_t len;
	double *result = calloc(1, sizeof(result));
	riemann_func function;
	term *terms;
	term **terms_ptr = calloc(1, sizeof(term*));
	range rng;
	range *rng_ptr = calloc(1, sizeof(range));

	rc = get_equation(terms_ptr, &len);
	check(rc == 0, "Could not get equation.");
	terms = *terms_ptr;
	
	for (i = 0; i < len; i++)
	{
		log_info("term %zu coefficient: %lf\n", i + 1, terms[i].coefficient);
		log_info("term %zu power: %lf\n", i + 1, terms[i].power);
	}
	
	rc = get_range(rng_ptr);
	check(rc == 0, "Could not get range.");
	rng = *rng_ptr;
	log_info("start: %lf interval: %lf count: %zu\n", rng.start, rng.interval, rng.count);
	
	rc = get_func(&function);
	check(rc == 0, "Could not get function.");
	log_info("function name: %s\n", function.name);
	
	check(function.func(terms, len, rng, result) == 0, "failure in function.func");
	
	return 0;

error:
	return 1;
}
/*
int get_func(riemann_func *func)
{
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
	check(terms != NULL, "terms cannot be null.");
	check(t_length > 0, "t_length must be greater than 0.");
	check(result != NULL, "result must not be null.");


	size_t i;
	*result = 0;
	log_info("left_sum called. \n");

	for (i = 0; i < r.count; i++)
	{
		double tmp;
		check(find_y(terms, t_length, (double)i * r.interval, &tmp) == 0, "Could not calculate.");
		*result += tmp * r.interval;
		log_info("result: %lf", *result);
	}
	
	return 0;

error:
	return 1;
}

void init_globals()
{
	left_sum_func.name = "Left Riemann Sum";
	left_sum_func.func = left_sum;
	
	functions = calloc(num_funcs, sizeof(riemann_func));
	functions[0] = left_sum_func; 
} */
