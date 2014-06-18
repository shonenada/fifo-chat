#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include "structs.h"
 
#define FIFO_NAME "/tmp/server_fifo"
#define CLIENT_FIFO_NAME "/tmp/client_fifo"
#define BUFF_SIZE 200
 
int RegController(ClientEnv* env) {
    char username[32];
    char password[32];
    char protocol[1024];
    printf("Please input your username: ");
    scanf("%s", username);
    printf("Please input your password: ");
    scanf("%s", password);
    sprintf(protocol, "REG %s %s", username, password);
    write(env->serverFd, protocol, strlen(protocol) + 1);
    return 1;
}

int LoginController(ClientEnv* env) {
    return 1;
}

void showTips(ClientEnv* env) {
    int cmdInput;
    printf("*****************************\n");
    printf("*  Please Input the number  *\n");
    printf("* 1. Register               *\n");
    printf("* 2. Login                  *\n");
    printf("* 3. Exit                   *\n");
    printf("*****************************\n");
    scanf("%d", &cmdInput);
    switch(cmdInput) {
        case 1:
        RegController(env);
        break;
        case 2:
        LoginController(env);
        break;
        case 3:
        exit(0);
        break;
        default:
        showTips();
        break;
    }
}

int main (int argc, char* argv[]) {
    // Initialize
    ClientEnv clientEnv = {getpid(), 0, 0, 0, ''};

    if (access(FIFO_NAME, F_OK) == -1) {
        printf("Could not open FIFO %s.\n", FIFO_NAME);
        exit (EXIT_FAILURE);
    }

    clientEnv.serverFd = open(FIFO_NAME, O_WRONLY | O_NONBLOCK);
    if (clientEnv.serverFd == -1) {
        printf("Could not open %s for write access.\n", FIFO_NAME);
        exit (EXIT_FAILURE);
    }

    sprintf(clientEnv.pipe, "/tmp/client_%d_fifo", getpid());
    clientEnv.clientFIFO = mkfifo(clientEnv.pipe, 0777);
    if (clientEnv.clientFIFO != 0) {
        printf("FIFO %s was not created! \n", clientEnv.pipe);
        exit (EXIT_FAILURE);
    }
 
    clientEnv.clientFd = open(clientEnv.pipe, O_RDONLY | O_NONBLOCK);
    if (clientEnv.clientFd == -1) {
        printf("Could not open %s for read only access.\n", FIFO_NAME);
        exit(EXIT_FAILURE);
    }

    showTips(&clientEnv);

    /** 
    strcpy(info.client_fifo_name, pipe_name);
    printf("Please input your username (less than 10 char): ");
    scanf("%s", &username);
    strcpy(info.username, username);
    printf("Welcome %s!\n", info.username);
 
    printf("Cammands:\n\tquit\tQuit client\n\thelp\tShow Help.\n");

    setbuf(stdin, NULL);
    // 清空输入缓存先

    pthread_create(&thread_id, NULL, &pthread_read_fifo, &client_fifo);

    while (1) {
        printf(">>> Say: ");
        fgets(buffer, BUFF_SIZE, stdin);
        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }
        if (strcmp(buffer, "\n") == 0) {
            continue;
        }
        strcpy(info.content, buffer);
        write(fifo_fd, &info, sizeof(CLIENT_INFO));
    }
 
    close(fifo_fd);
    close(client_fifo);

    (void) unlink(pipe_name);

    **/

    close(env.serverFd);
    close(env.clientFd);

    return 0;

}