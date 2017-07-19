#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handing(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len, i;
    int recv_cnt;
    int recv_len = 0; 
    struct sockaddr_in serv_adr;
    socklen_t clnt_adr_sz;

    if(argc  != 3){
        error_handing("argc miss");
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));  
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2])); 

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1){
        error_handing("connec() error");
    }

    while(1)
    {
        fputs("Input message ", stdout);
        fgets(message, BUF_SIZE, stdin);
        str_len = write(sock, message, sizeof(message)); 
        recv_len = 0;
        while(recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE-1);
            if(recv_cnt == -1){
                error_handing("read() error");
            }
            recv_len = recv_len + recv_cnt;
        }
        message[recv_len] = 0;
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


