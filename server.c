#include "tp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include "logger.h"

char **tp_proc_1_svc(tp_info *in, struct svc_req *rqstp)
{

	FILE* fpipe;
    char* grep_args;
    char* comando = "grep ";
    char* comando_final;
    char* program1AndProgram2;
    char* n_maq = getenv("N_MAQ"); //  Numero da maquina a partir da variavel de ambiente
    char* file_log;
    char* prefixo_log = "maquina.";
	static char* readPipeInto;

    file_log = calloc(1,strlen(prefixo_log)+strlen(n_maq)+ 4 + 1);

    strcpy(file_log,prefixo_log);
    strcat(file_log,n_maq);
    strcat(file_log,".log");

    grep_args = calloc(1,strlen(in->grep_args)+1 +1);
    strcpy(grep_args,in->grep_args);
    strcat(grep_args," ");

	readPipeInto = (char*)malloc((100000 + 1)*sizeof(char));
 	memset(readPipeInto, 0,100000 +1);

	// Monta o comando
    comando_final = calloc(1,strlen(comando) + strlen(grep_args) + strlen(file_log)+ 1);
    strcat(comando_final,comando);
    strcat(comando_final,grep_args);
    strcat(comando_final,file_log);

 	program1AndProgram2=(char*)malloc((strlen(comando_final) + 1)*sizeof(char));
	strcpy(program1AndProgram2,comando_final);

	//Executa o comando
 	if ( !(fpipe = (FILE*)popen(program1AndProgram2,"r")) )
 	{
   		perror("Erro no comando!");
        set_log_file(file_log);
        LOG_PRINT("Erro no comando: '%s' [maquina: %s]",comando_final,n_maq);
   		exit(1);
 	}
 	//Salva saida do programa no readPipeInto
 	fread((char *)readPipeInto, 100000, 1, fpipe);
	pclose(fpipe);
 	free(program1AndProgram2);
    set_log_file(file_log);
    LOG_PRINT("Comando executado: '%s' [maquina:%s]",comando_final,n_maq);
 	//return output to the client
 	return (char **)&readPipeInto;
}

void *tp_exit_1_svc(struct tp_info *in, struct svc_req *rqstp)
{
	printf("Request for Termination Received\n");
	fflush(NULL);
	exit(0);
}

int *tp_status_1_svc(tp_info *in, struct svc_req *rqstp)
{
    return (int *)1;
}