#include "tp.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char**argv)
{
	CLIENT *cl;

	if(argc != 3)
	{
		printf("Usage: ./client HOSTNAME GREP_ARGS\n");
		return 1;
	}

	char *server_hostname = argv[1];
	cl = clnt_create(server_hostname, TP_PROG, TP_VERS, "tcp");
	if(cl == NULL) {
		clnt_pcreateerror("Error creating client");
		exit(EXIT_FAILURE);
	}

	struct tp_info t;
	t.grep_args  = argv[2];

	if(t.grep_args == "-1")
	{
		tp_exit_1(&t, cl);
		printf("Terminated Server\n");
		return 0;
	}
	
  	clock_t start = clock();
	struct retorno_server* retorno;
	retorno = tp_proc_1(&t, cl);
	clock_t end = clock();
  	float time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Recebeu %d bytes.\n\n %s\n",(int) strlen(*retorno->grepOutput),*retorno->grepOutput);
	printf("Tempo gasto: Servidor %f segundos. Rede %f segundos. Total %f segundos.\n", retorno->execTime, time-retorno->execTime, time);
	clnt_destroy(cl);
	exit(0);
}
