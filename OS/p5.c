#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 5 
#define NUM_THREADS 3
int id[NUM_THREADS];
char str[26]="abcdefghijklmnopqrstuvwxyz";
char arr[size];  
int front,rear,counter=0;
front= -1;
rear= -1;
int k=0,j=0;
char con1[26],con2[26];
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataProduced = PTHREAD_COND_INITIALIZER;
pthread_cond_t dataConsumed = PTHREAD_COND_INITIALIZER;
pthread_cond_t readingConsumer2 = PTHREAD_COND_INITIALIZER;
void enQueue(char value) 
{ 
    if ((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))){ 
        printf("\nQueue is Full"); 
        return; 
    } 
    else if (front == -1) /* Insert First Element */
    { 
        front = rear = 0; 
        arr[rear] = value; 
    } 
  
    else if (rear == size-1 && front != 0) 
    { 
        rear = 0; 
        arr[rear] = value; 
    } 
  
    else
    { 
        rear++; 
        arr[rear] = value; 
    } 
} 
  
// Function to delete element from Circular Queue 
char deQueue() 
{ 
    if (front == -1) 
    { 
        printf("\nQueue is Empty"); 
        return '\0'; 
    } 
  
    int data = arr[front]; 
    arr[front] = -1; 
    if (front == rear) 
    { 
        front = -1; 
        rear = -1; 
    } 
    else if (front == size-1) 
        front = 0; 
    else
        front++; 
  
    return data; 
} 
  
// Function displaying the elements 
// of Circular Queue 
void displayQueue() 
{ 
    if (front == -1) 
    { 
        printf("\nQueue is Empty"); 
        return; 
    } 
    printf("\nElements in Circular Queue are: "); 
    if (rear >= front) 
    { 
        for (int i = front; i <= rear; i++) 
            printf("%d ",arr[i]); 
    } 
    else
    { 
        for (int i = front; i < size; i++) 
            printf("%d ", arr[i]); 
  
        for (int i = 0; i <= rear; i++) 
            printf("%d ", arr[i]); 
    } 
}  
/* create thread argument struct for thr_func() */

/* thread function */
void *produce(){

    FILE *fp;
    fp=fopen("string.txt","r");
    char ch;
    while((ch=getc(fp))!=EOF){
        pthread_mutex_lock( &mutex1 );
        if(!((rear == size-1 && front == 0) || (rear == front-1)))
        {
            //ch=getc(fp);
            enQueue(ch);
            counter++;
         //   
        }
       // pthread_cond_broadcast(&dataProduced);
      // pthread_cond_wait(&dataConsumed,&mutex1);
       
        pthread_mutex_unlock( &mutex1 );
        //          
    }
}

void consumerA(){
    
    pthread_mutex_lock( &mutex1 );
    con1[k++]=deQueue();
    con1[k++]=deQueue();
    pthread_mutex_unlock( &mutex1 );

}
void consumerB(){
    
    pthread_mutex_lock( &mutex1 );
    con2[j++]=deQueue();
    pthread_mutex_unlock( &mutex1 );
}
void *consume(){
    pthread_cond_wait(&dataProduced,&mutex1);
   // pthread_mutex_lock( &mutex1 );
    while(front!=-1){
        consumerA();
        consumerB();
    }
    //pthread_mutex_unlock( &mutex1 );
    pthread_cond_signal(&dataConsumed);
}
int main(int argc, char **argv){
    pthread_t producer,consumerA,consumerB;
    /* create threads */
    int rc1,rc2,rc3;

    if ((rc1 = pthread_create(&producer, NULL,&produce,NULL))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc1);
      return EXIT_FAILURE;
    }
    if ((rc2 = pthread_create(&consumerA, NULL,&consume,NULL))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc2);
      return EXIT_FAILURE;
    }
    if ((rc3 = pthread_create(&consumerB, NULL,&consume,NULL))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc3);
      return EXIT_FAILURE;
    }
    printf("\n");
    for(int temp=0;temp<k;temp++){
        printf("%c ",con1[temp]);
    }
    printf("\n");
    for(int temp=0;temp<j;temp++){
        printf("%c ",con2[temp]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}