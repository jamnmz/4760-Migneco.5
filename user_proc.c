/*
 *Jared Migneco
 *Hauschild Projecr 5
 *Due: 11/22/22
 *
 *
 *User_proc Class
 *
 *
 *
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>

#define SHMKEY  960158     /* Parent and child agree on common key.*/
#define BUFF_SZ sizeof ( int )

//message buffer from https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_message_queues.htm
#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

int main(int argc, char** argv)
{
        printf("User_Proc: We are in the child class\n");
        int shmid1 = shmget ( SHMKEY, BUFF_SZ, 9045);
        int shmid2 = shmget ( SHMKEY, BUFF_SZ, 9046);

        //initializing needed variables for message buffer
        struct my_msgbuf buf;
        int msqid;
        int toend;
        int len;
        key_t key;
        char *msgText = "(Un)Locked and ready to go";
        system("touch msgq.txt");


        //intializing variables and setting value of m to passed parameter m from parent
        int m = atoi(argv[1]);
        int x;
        int i;

        //shared memory integers
        char *secClock = (char*) (shmat(SHMKEY, NULL, 9045));
        char *nanoClock = (char*) (shmat(SHMKEY, NULL , 9046));


        int *sharedSecClock = (int*)(secClock);
        int *sharedNanoClock = (int*)(nanoClock);

        srand(time(0));
        int randResource = rand() % 20;


        printf("User_Proc: %d",getpid());
        printf(" requesting resource R%d\n", randResource);

        //freeing memory
        shmdt(secClock);
        shmdt(sharedSecClock);
        sleep(3);
        return EXIT_SUCCESS;
}
