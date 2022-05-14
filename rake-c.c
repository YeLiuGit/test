#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <string.h>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <unistd.h>

#define PORT 12345

/**
typedef struct{
    char *command
} action;

typedef struct{
    action actions
} actionset;

typedef struct{
    int default_port;
    char **hosts;
    actionset *actionset
}
*/

void usage(){
    printf("Usage: rake-c only allow on argument: filename\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {

    if (argc != 1) {
        usage();  
        exit(EXIT_FAILURE);
    }
    
    int client = 0, valread;
    
    struct sockaddr_in serv_addr;
    char* message = "this a a message";
    char buffer[1024] = { 0 };

    if ((client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("fail to creat Socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //convert IP address from string binary 
    if (inet_pton(AF_INET, "192.168.1.110", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(client, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(client, message, strlen(message), 0);
    printf("message sent\n");

    valread = read(client, buffer, 1024);
    printf("message below received:\n %s\n", buffer);

    return 0
}
