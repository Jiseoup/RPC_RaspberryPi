#include "rpc.h"

int *
id_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	result = *argp; // Assign the recalled data.
	printf("INTEGER : %d is called\n", result);

	return &result;
}

char **
name_1_svc(char **argp, struct svc_req *rqstp)
{
	static char *result;

	result = *argp; // Assign the recalled data.
	printf("STRING : %s is called\n", result);
	    
	return &result;
}
