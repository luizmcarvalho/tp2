//logger.c
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

FILE *fp ;
static int SESSION_TRACKER; //Keeps track of session
static char* log_file = "padrao.log";

char* print_time()
{
    time_t t;
    char *buf;

    time(&t);
    buf = (char*)malloc(strlen(ctime(&t))+ 1);

    snprintf(buf,strlen(ctime(&t)),"%s ", ctime(&t));

    return buf;
}
void set_log_file(char* file_name)
{
    log_file = (char*)malloc(strlen(file_name) + 1);
    strcpy(log_file,file_name);
}
void log_print(char* filename, int line, char *fmt,...)
{
    va_list         list;
    char            *p, *r;
    int             e;
    double          d;

    if(SESSION_TRACKER > 0)
        fp = fopen (log_file,"a+");
    else
        fp = fopen (log_file,"a+");

    fprintf(fp,"%s ",print_time());
    va_start( list, fmt );

    for ( p = fmt ; *p ; ++p )
    {
        if ( *p != '%' )//If simple string
        {
            fputc( *p,fp );
        }
        else
        {
            switch ( *++p )
            {
                /* string */
                case 's':
                {
                    r = va_arg( list, char * );

                    fprintf(fp,"%s", r);
                    continue;
                }

                    /* integer */
                case 'd':
                {
                    e = va_arg( list, int );

                    fprintf(fp,"%d", e);
                    continue;
                }
                    /* float */
                case 'f':
                {
                    d = va_arg( list, double );

                    fprintf(fp,"%f", d);
                    continue;
                }

                default:
                    fputc( *p, fp );
            }
        }
    }
    va_end( list );
    fprintf(fp," [%s][line: %d] ",filename,line);
    fputc( '\n', fp );
    SESSION_TRACKER++;
    fclose(fp);
}