#include "rpc.h"

void
rpc_prog_1(char *host, int a, char* b) // Add parameters. (int a, char* b)
{
	CLIENT *clnt;
	int  *result_1;
	int  id_1_arg;
	char * *result_2;
	char * name_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RPC_PROG, RPC_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	// Assigns the data to be called to a variable.
	id_1_arg = a;
	name_1_arg = b;

	result_1 = id_1(&id_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	// When the call is successful.
	else {
	    printf("INTEGER : %d\n", *result_1);
	}

	result_2 = name_1(&name_1_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	// When the call is successful.
	else{
	    printf("STRING : %s\n", *result_2);
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	// Because we added two parameters, change the condition to (argc < 4).
	if (argc < 4) {
		printf ("usage: %s server_host INTEGER STRING\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	rpc_prog_1 (host, atoi(argv[2]), argv[3]);
exit (0);
}
