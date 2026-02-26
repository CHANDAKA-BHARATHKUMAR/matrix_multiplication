// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>
 
// pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// pthread_barrier_t barrier;
// pthread_t t1,t2;
// int exit_flag = 0;
// int counter = 0;
// void* thread2(void* arg) {
//     while (!exit_flag) {
//         pthread_barrier_wait(&barrier);
//         pthread_mutex_lock(&mutex1);
//         if(counter%2==1){
//             counter++;
//             printf("t2 count: %d\n",counter);
//         }
//         pthread_mutex_unlock(&mutex1);
//         if (counter>100){
//         exit_flag = 1;}
//     }
//     pthread_exit(NULL);
// }
// void* thread1(void* arg) {
//     while (!exit_flag) {
//         pthread_mutex_lock(&mutex1);
//         if(counter%2==0){
//             counter++;
//             printf("t1 count: %d\n",counter);
//         }
//         pthread_mutex_unlock(&mutex1);

//         if (counter>100){
//     exit_flag = 1;}
//     }
    
//     pthread_exit(NULL);
// }
// int main() {
//     pthread_create(&t1,NULL,thread1,NULL);
//     pthread_create(&t2,NULL,thread2,NULL);
//     pthread_join(t1,NULL);
//     pthread_join(t2,NULL);
//     printf("all threads terminated\n");
//     return 0;
// // }
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
 
pthread_t t1, t2;
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
 
int counter = 0;
int exit_flag = 0;
 
void* thread1(void* arg)
{
    while (1) {
        pthread_barrier_wait(&barrier);   // sync start of step
 
        pthread_mutex_lock(&mutex);
 
        if (counter > 100) {
            exit_flag = 1;
            pthread_mutex_unlock(&mutex);

 
        pthread_barrier_wait(&barrier);  
            break;
        }
 
        if (counter % 2 == 0) {
            counter++;
            printf("t1 count: %d\n", counter);
        }
 
        pthread_mutex_unlock(&mutex); // sync end of step
    }
    pthread_exit(NULL);
}
 
void* thread2(void* arg)
{
    while (1) {
        pthread_barrier_wait(&barrier);   // sync start of step
 
        pthread_mutex_lock(&mutex);
 
        if (counter > 100) {
            exit_flag = 1;

 
            pthread_barrier_wait(&barrier); 
            pthread_mutex_unlock(&mutex);
            break;
        }
 
        if (counter % 2 == 1) {
            counter++;
            printf("t2 count: %d\n", counter);
        }
 
        pthread_mutex_unlock(&mutex);    // sync end of step
    }
    pthread_exit(NULL);
}
 
int main()
{
    pthread_barrier_init(&barrier, NULL, 2);
 
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 
    pthread_barrier_destroy(&barrier);
 
    printf("all threads terminated\n");
    return 0;
}
 