#include  <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>

#define NQ      3      
#define MAXMSZ  512    
#define KEY     0x123  

struct threadinfo {
    int qid;
    int fd;
};

struct mymesg {
    long mtype;
    char mtext[MAXMSZ];
};

void *helper(void *arg)
{
    int                 n;
    struct mymesg       *m;
    struct threadinfo   *tip = arg;

    for(;;) {
        m = malloc(sizeof(struct mymesg));
        memset(m, 0, sizeof(struct mymesg));
        if ((n = msgrcv(tip->qid, m, MAXMSZ, 0, MSG_NOERROR)) < 0)
            printf("msgrcv error");
        if (write(tip->fd, &m, sizeof(void*)) < 0)
            printf("write error");
    }
}

int main()
{
    int                 i, n, err;
    int                 fd[2];
    int                 qid[NQ];
    struct pollfd       pfd[NQ];
    struct threadinfo   ti[NQ];
    pthread_t           tid[NQ];
    struct mymesg       *m;

    for (i = 0; i < NQ; i++) {
        if ((qid[i] = msgget((KEY+i), IPC_CREAT|0666)) < 0)
            printf("msgget error");

        fprintf(stderr, "queue ID %d is %d\n", i, qid[i]);

        if (pipe(fd) < 0)
            printf("pipe error");

        pfd[i].fd = fd[0];
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];
        if ((err = pthread_create(&tid[i], NULL, helper, &ti[i])) != 0)
            printf( "pthread_create error");
    }

    for (;;) {
        if (poll(pfd, NQ, -1) < 0)
            printf("poll error");
        for (i = 0; i < NQ; i++) {
            if (pfd[i].revents & POLLIN) {
                if ((n = read(pfd[i].fd, &m, sizeof(char*))) < 0)
                    printf("read error");
                fprintf(stderr, "queue id %d, message %s\n", qid[i], m->mtext);
                free(m);
            }
        }
    }

    exit(0);
}
