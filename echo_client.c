#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket>

#define BUF_SIZE 1024;
void error_handing(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len, i;
    
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc  != 3){
        error_handing("argc miss");
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));  
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = hons(atoi(argv[1])); 

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1){
        error_handing("bind() error");
    }

    while(1)
    {
        fputs("Input message ", stdout);
        fgets(message, BUF_SIZE, stdin);
        write(sock, message, sizeof(message)); 
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message From server is %s \n", message);
    }
    close(sock);
    return 0;

}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(0);
}


