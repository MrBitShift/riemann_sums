#include <stdio.h>
#include "riemann_sums.h"
#include "mathinput.h"
#include "dbg.h"


int main(int argc, char *argv[])
{
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
	
	check(function.func(terms, len, rng, result) == 0, "failure in %s", function.name);
	
	return 0;

error:
	return 1;
}
