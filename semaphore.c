#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};

#define PATH "/home/sungchan9398/thread-safe-counter"

key_t key;
int semid;
struct sembuf s;
union semun arg;
unsigned int counter = 0;
unsigned int loop_cnt;

void *mythread(void *arg)
{
	char *letter = arg;
	int i;

	printf("%s : begin\n", letter);

	for (i=0; i<loop_cnt; i++)
	{
		s.sem_num = 0;
		s.sem_op = -1;
		s.sem_flg = 0;
		semop(semid, &s, 1);

		counter += 1;

		s.sem_num=0;
		s.sem_op = 1;
		s.sem_flg = 0;
		semop(semid, &s, 1);
	}
	printf("%s:done\n", letter);
	return NULL;
}
                                                                         
int main(int argc, char *argv[])
{                    
   
    
    key = ftok(PATH, 'z');
    if (key < 0){
	perror(argv[0]);
    	exit(1);
    }
    semid = semget(key, 1, 0600 | IPC_CREAT);
    if(semid <0){
	 perror(argv[0]);
      	 exit(1);
    }
    printf("semid = %d\n", semid);

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

	
    loop_cnt = atoi(argv[1]);
    clock_t start, end;
    float result;

    start = clock();
    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", counter);
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    end = clock();

    printf("main: done [counter: %d] [should be: %d]\n", counter, loop_cnt * 2);
    printf("time : %.3f\n", result);
   
    return 0;
}
