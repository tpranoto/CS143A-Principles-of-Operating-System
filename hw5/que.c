//CS143a HW5
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include "que.h"

pthread_mutex_t m;
sem_t full,empty,lock;


static ELE _que[QUE_MAX];
static int _front = 0, _rear = 0;
extern int producers_working;

static int matches = 0;

void add_match()
{
    //Note: you will need to lock this update because it is a race condition
    pthread_mutex_lock(&m);
    matches++;
    pthread_mutex_unlock(&m);
}

void report_matches(char *pattern)
{
    printf("Found %d total matches of '%s'\n", matches, pattern);
}

int que_init()
{
    sem_init(&lock,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,QUE_MAX-1);
}

void que_error(char *msg)
{
    fprintf(stderr, "***** Error: %s\n", msg);
    // exit(-1);
}

int que_is_full()
{
    return (_rear + 1) % QUE_MAX == _front; /* this is why one slot is unused */
}

int que_is_empty()
{
    return _front == _rear;
}

void que_enq(ELE v)
{
    sem_wait(&empty);
    sem_wait(&lock);
    if ( que_is_full() )
        que_error("enq on full queue");
    _que[_rear++] = v;
    if ( _rear >= QUE_MAX )
        _rear = 0;
    sem_post(&lock);
    sem_post(&full);
}

ELE que_deq()
{
    ELE temp;
    temp.string[0]='\0';
    
    struct timespec myTime;
    myTime.tv_sec=0;
    myTime.tv_nsec=0;

    if(sem_timedwait(&full, &myTime)==-1)
       return temp;

    sem_wait(&lock);
    if ( que_is_empty() )
        que_error("deq on empty queue");
    ELE ret = _que[_front++];
    if ( _front >= QUE_MAX )
        _front = 0;
    sem_post(&lock);
    sem_post(&empty);
    return ret;
}


/*

int main()
{
    for ( int i=0; i<QUE_MAX-1; ++i )
    {
        Buffer b;
        sprintf(&b.string, "%d", i);
        que_enq(b);
    }
    while ( !que_is_empty() )
        printf("%s ", que_deq().string);
    putchar('\n');
}
*/
