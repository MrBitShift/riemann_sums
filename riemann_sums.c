#include <stdio.h>
#include <time.h>
#include "riemann_sums.h"
#include "mathinput.h"
#include "dbg.h"

#define SHOW_INFO_FLAG "--show-info"
#define LOG_FILENAME "log.txt"

int debug_time()
{
	// variables to store date and time components
	time_t now;

	// Obtain current time
	time(&now);

	// Convert to local time format and print to stdout
	fprintf(get_dbg_out(), "\r\n-----------------------\r\n");
	debug("%s", ctime(&now));

	return OPERATION_SUCCESS;
}

int main(int argc, char *argv[])
{
	dbg_out = fopen(LOG_FILENAME, "a");
	check(dbg_out != NULL, "Failed to open %s. Try running with admin permissions.", LOG_FILENAME);
	check(debug_time() == OPERATION_SUCCESS, "Failed to write time to debug.");
	
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
	check(rc == OPERATION_SUCCESS, "Could not get equation.");
	terms = *terms_ptr;
	
	for (i = 0; i < len; i++)
	{
		debug("term %zu coefficient: %lf", i + 1, terms[i].coefficient);
		debug("term %zu power: %lf", i + 1, terms[i].power);
	}
	
	rc = get_range(rng_ptr);
	check(rc == OPERATION_SUCCESS, "Could not get range.");
	rng = *rng_ptr;
	debug("start: %lf count: %zu end: %lf", rng.start, rng.count, rng.end);
	
	rc = get_func(&function);
	check(rc == OPERATION_SUCCESS, "Could not get function.");
	debug("function name: %s", function.name);
	
	check(function.func(terms, len, rng, result) == 0, "failure in %s", function.name);
	
	printf("Result: %lf\n", *result);
	debug("Result: %lf\n", *result);
	
	debug("Operation successful. Exiting normally.");
	close_dbg_out();
	return OPERATION_SUCCESS;

error:
	log_err("Operation failed. Exiting with status 1.");
	close_dbg_out();
	return OPERATION_FAILURE;
}
