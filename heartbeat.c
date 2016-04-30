#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "logger.h"

int main(int argc, char** argv)
{
    FILE *fp;
    char path[1035];
    char* n_maq = getenv("N_MAQ"); //  Numero da maquina a partir da variavel de ambiente
    char* file_log;
    file_log = calloc(1,8+strlen(n_maq)+ 4 + 1);
    strcpy(file_log,"maquina.");
    strcat(file_log,n_maq);
    strcat(file_log,".log");

    while(1)
    {
        /* Open the command for reading. */
        fp = popen("ps aux | grep -c \"./[s]erver\"","r");
        if (fp == NULL) {
            printf("Failed to run command\n" );
            exit(1);
        }
        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            printf("%s", path);
        }
        /* close */
        pclose(fp);

        if(atoi(path)==0)
        {
            set_log_file(file_log);
            LOG_PRINT("Heartbeat: Falha no servidor!");
        }
        if(argc == 2 )
            sleep(argv[1]);
        else
            sleep(1);
    }
}
