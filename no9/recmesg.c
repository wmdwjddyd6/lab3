#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 32
#define QNAME "/my_queue"
#define PRIORITY 1

char recv[BUFSIZE];

int main() {

	mqd_t qd;
	pid_t pid;
	int status;
	struct mq_attr q_attr, old_q_attr; int prio;
	char buf[BUFSIZE];
	q_attr.mq_maxmsg = 10;
	q_attr.mq_msgsize = BUFSIZE;


	while(1){
		if ((pid = fork()) == 0){

			if ((qd = mq_open(QNAME, O_RDWR | O_NONBLOCK, 0600, NULL)) == -1) {
				perror ("mq_open failed");
				exit (1);
			}
			q_attr.mq_flags = 0;

			if (mq_setattr(qd, &q_attr, NULL)) {
				exit (1);
			}

			if (mq_getattr(qd, &old_q_attr)) {
				perror ("mq_getattr failed");
				exit (1);
			}

			if (!(old_q_attr.mq_flags & O_NONBLOCK));

			if (mq_receive(qd, recv, BUFSIZE, &prio) == -1) {
				perror ("mq_send failed");
				exit (1);
			}

			printf ("receive : %s\n", recv);

			if (mq_close(qd) == -1) {
				pid = wait(&status);
				perror ("mq_close failed");
				exit (1);
			}

			if (mq_unlink(QNAME) == -1) {
				perror ("mq_unlink failed");
				exit (1);
			}
			exit(0);
		}else if(pid > 0){
			pid = wait(&status);
			sleep(5);
		}
		else{
			perror("fork failed");
			exit(1);
		}
	}
}
