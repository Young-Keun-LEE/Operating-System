#include <pthread.h>
pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

/* thread_one runs in this function*/
void *do_work_one(void *param)
{
    int done = 0;

    while(!done){
        pthread_mutex_lock(&first_mutex);
        if(pthread_mutex_trylock(&second_mutex)){
            /*
            Do some work
            */
           pthread_mutex_unlock(&second_mutex);
           pthread_mutex_unlock(&first_mutex);
           done = 1;
        }
        else
            pthread_mutex_unlock(&first_mutex);        
    }
    pthread_exit(0);
}

/* thread_two runs in this function*/
void *do_work_two(void *param)
{
    int done = 0;

    while(!done){
        pthread_mutex_lock(&second_mutex);
        if(pthread_mutex_trylock(&first_mutex)){
            /*
            Do some work
            */
            pthread_mutex_unlock(&first_mutex);
            pthread_mutex_unlock(&second_mutex);
            done = 1;
        }
        else
            pthread_mutex_unlock(&second_mutex);
    }
    pthread_exit(0);
}