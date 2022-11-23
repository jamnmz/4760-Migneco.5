/*
 *Jared Migneco
 *Project 5 OSS Class
 *Hauschild
 *Due: 11/22/22
 *
 *
 *oss class
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
#include <string.h>
#include <sys/msg.h>
#include <time.h>


//shared memory
#define SHMKEY  960158     /* Parent and child agree on common key.*/
#define BUFF_SZ sizeof ( int )

//message queue struct from https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_message_queues.htm
#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

//resource data structure
struct my_resources
{
        char name[10];
        int type;
        char desc[20];
        int shareable;
        int value;

};


//using form provided OS_tutorial
void print_usage ( const char * app )
{
        fprintf (stderr, "usage: %s [-h] \n",app);
        fprintf (stderr, "    Calling with no arguments starts program\n");
}


//main body
int main(int argc, char** argv)
{

        //resource declarations
        struct my_resources r0;
        struct my_resources r1;
        struct my_resources r2;
        struct my_resources r3;
        struct my_resources r4;
        struct my_resources r5;
        struct my_resources r6;
        struct my_resources r7;
        struct my_resources r8;
        struct my_resources r9;
        struct my_resources r10;
        struct my_resources r11;
        struct my_resources r12;
        struct my_resources r13;
        struct my_resources r14;
        struct my_resources r15;
        struct my_resources r16;
        struct my_resources r17;
        struct my_resources r18;
        struct my_resources r19;

        r0.type = (rand() % 2);
        r0.value = (rand() % 11);

        r1.type = (rand() % 2);
        r1.value = (rand() % 11);

        r2.type = (rand() % 2);
        r2.value = (rand() % 11);

        r3.type = (rand() % 2);
        r3.value = (rand() % 11);

        r4.type = (rand() % 2);
        r4.value = (rand() % 11);

        r5.type = (rand() % 2);
        r5.value = (rand() % 11);

        r6.type = (rand() % 2);
        r6.value = (rand() % 11);

        r7.type = (rand() % 2);
        r7.value = (rand() % 11);

        r8.type = (rand() % 2);
        r8.value = (rand() % 11);

        r9.type = (rand() % 2);
        r9.value = (rand() % 11);

        r10.type = (rand() % 2);
        r10.value = (rand() % 11);

        r11.type = (rand() % 2);
        r11.value = (rand() % 11);

        r12.type = (rand() % 2);
        r12.value = (rand() % 11);

        r13.type = (rand() % 2);
        r13.value = (rand() % 11);

        r14.type = (rand() % 2);
        r14.value = (rand() % 11);

        r15.type = (rand() % 2);
        r15.value = (rand() % 11);

        r16.type = (rand() % 2);
        r16.value = (rand() % 11);

        r17.type = (rand() % 2);
        r17.value = (rand() % 11);

        r18.type = (rand() % 2);
        r18.value = (rand() % 11);

        r19.type = (rand() % 2);
        r19.value = (rand() % 11);

        int allocArr[4][5] = { { r0.value, r1.value, r2.value, r3.value, r4.value },
                         { r5.value, r6.value, r7.value, r8.value, r9.value },
                         { r10.value, r11.value, r12.value, r13.value, r14.value },
                         { r15.value, r16.value, r17.value, r18.value, r19.value } };
        int maxArr[4][5];
        int availVec[5];
        int detectionBool;
        int f;
        int g;

        //message queue
        //https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_message_queues.htm
        struct my_msgbuf buf;
        int msqid;
        int len;
        key_t key;
        system("touch msgq.txt");

        int q;
        int w;
        int s;

        //clock variable
        int clockSec = 0;
        int clockNano = 0;
        int clockRand = 0;
        int clockRandNano = 0;
        int clockNeeded;

        //variable for process time
        int procLen = 0;
        int timeNeeded[54];
        int timeRemain;

        //originally thought program needed to handle user input and reread task
        int c = argc;
        int opt;

        //help statement found by calling with an argument
        switch(c)
        {
                case 1:
                        break;
                case 2:
                        print_usage ( argv[0] );
                        return ( EXIT_SUCCESS );
                default: /* '?' */
                        printf ( "Invalid option %c\n", optopt );
                        print_usage ( argv[0] );
                        return ( EXIT_FAILURE );

        }


        //CREATION OF SHARED MEMORY
        int shmid1 = shmget ( SHMKEY, BUFF_SZ, 9045 | IPC_CREAT );
        int shmid2 = shmget ( SHMKEY, BUFF_SZ, 9046 | IPC_CREAT );

        char *secClock = (char*) shmat(shmid1,NULL, 0);
        char *nanoClock = (char*) shmat(shmid2,NULL, 0);

        int *sharedClockSec = (int*) (secClock);
        int *sharedClockNano = (int*) (nanoClock);

        int i;
        //overflow value used to adjust past 18 in the timeNeeded array
        int j = 0;

        int procs;

        //argument array for user_proc, cannot figure out how to convert m value into a string so just passing default m value
        static char *workerArr[] = {"./user_proc", NULL, NULL};
        workerArr[1] = "1";




        int z, x, v, u, k;
        //keeps number of active processes below 18
        for(procs = 0; procs < 18; procs++)
        {
                //checks if clock has reached a second yet
                if(clockNano >= 1000000000)
                {
                        clockNano -= 1000000000;
                        clockSec += 1;
                }

                //forks and increments to active process counter
                pid_t childPid = fork();
                procs++;

                //randomly determines the amount of time processes get to run
                clockRand = rand() % 1000;
                clockRandNano = clockRand * 10000;

                //fills max claims array
                for (f = 0; f < 4; f++)
                {
                        for (g = 0; g < 5; g++)
                        {
                                maxArr[f][g] = rand() % 11;
                        }
                        availVec[f] = rand() % 11;
                }
                wait(1);

                //randomly determines if deadlock detection will be run
                detectionBool = rand() % 4;

                //deadlock safety algorith used from https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/
                if (detectionBool == 1)
                {
                        int f[z], ans[z], ind = 0;
                        for (k = 0; k < z; k++) {
                                f[k] = 0;
                        }
                        int need[z][x];
                        for (u = 0; u < z; u++) {
                                for (v = 0; j < x; j++){
                                        need[u][v] = maxArr[u][v] - allocArr[u][v];
                                }
                        }
                        int y = 0;
                        for (k = 0; k < 5; k++) {
                                for (u = 0; u < z; u++) {
                                        if (f[u] == 0) {
                                                int flag = 0;
                                                for (v = 0; v < x; v++) {
                                                        if (need[u][v] > availVec[v]){
                                                                flag = 1;
                                                                break;
                                                        }
                                                }
                                                if (flag == 0) {
                                                        ans[ind++] = u;
                                                        for (y = 0; y < x; y++){
                                                                availVec[y] += allocArr[u][y];
                                                        }
                                                        f[u] = 1;
                                                }
                                        }
                                }
                        }
                        int flag = 1;
                        for(u = 0; u<z; u++)
                        {
                                if(f[u]==0)
                                {
                                        flag=0;
                                        printf("OSS: The system is not safe");
                                        break;
                                }
                        }
                        if(flag==1)
                        {
                                printf("OSS: Following is the SAFE Sequence\n");
                                for (u = 0; u < z - 1; u++){
                                        printf(" P%d ->", ans[u]);
                                }
                                printf(" P%d", ans[z - 1]);
                        }
                }



                //I may be struggling to keep up, but this is all that keeps me going at this point
                //insert comedy.txt
                if (childPid < 0)
                {
                        perror("ERROR: something got a little forked up\n");
                        exit(EXIT_FAILURE);
                }
                else if (childPid == 0)
                {
                        //increments nanocounter and relays what process is running for how long
                        clockNano = clockNano + clockRandNano;
                        printf("OSS: Process %d requested at", childPid);
                        printf(" %d:", clockSec);
                        printf("%d seconds", clockNano);
                        //uses overflow counter to dtermine how many processes do not get to finish, and if they need to run again
                        if(timeNeeded[procs] != 0)
                        {
                                //incrementing j as overflow value
                                timeNeeded[j+18] = timeNeeded[procs];
                                j++;
                        }

                        execv(workerArr[0], workerArr);
                        fprintf(stderr,"Exec failed, terminating\n");
                        procs--;
                        exit(1);
                }
                wait(1);
        }

        printf("OSS: The Great Termination Cometh\n");

        //freeing from shared memory
        shmdt(sharedClockSec);
        shmctl(shmid1, IPC_RMID, NULL);
        shmdt(sharedClockNano);
        shmctl(shmid2, IPC_RMID, NULL);
        return EXIT_SUCCESS;

}
