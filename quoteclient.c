// Usage: quoteclient <server-fifo-filename>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXLEN 1000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        puts("Usage: quoteclient <server-fifo-name> <# of quotes");
        exit(1);
    }

    // argv[1] is the server fifo name

    char clientfifo[MAXLEN];
    sprintf(clientfifo, "/tmp/%s-%d", getenv("USER"), getpid());
    mkfifo(clientfifo, 0600);
    chmod(clientfifo, 0622);

    // argv[2] specifies # of quotes
    int nquotes = atoi(argv[2]);

    // open argv[1] for writing
    // send clientfifo
    FILE *fp = fopen(argv[1], "wb");
    for(int i=0; i<nquotes; i++)
        fprintf(fp, "%s\n", clientfifo);
    fclose(fp);
    
    FILE *quotefp = fopen(clientfifo, "r");
    char line[MAXLEN];
    
    while(fgets(line, MAXLEN, quotefp))
        puts(line);
    unlink(clientfifo);
}