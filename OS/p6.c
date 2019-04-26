#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 5 
char str[100],arr[size],con1[100],con2[100];
int front,rear,counter=0,k=0,j=0;
front= -1;
rear= -1;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
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

char deQueue() 
{ 
    if (front == -1) 
    { 
        printf("\nQueue is Empty\n"); 
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

void *produce(void *arg)
{
    int *c=(int *)arg;
    FILE *fp;
    fp=fopen("string.txt","r");
    char ch=getc(fp);
    while(ch!=EOF)
    {
        pthread_mutex_lock(&mutex1);
        while(!((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))))
        {
            enQueue(ch);
            ch=getc(fp);
            counter++;
        }
        pthread_mutex_unlock(&mutex1);  
    }
}
void consumerA()
{
    pthread_mutex_lock( &mutex1 );
    con1[k++]=deQueue();
    con1[k++]=deQueue();
    pthread_mutex_unlock( &mutex1 );
}
void consumerB()
{
    pthread_mutex_lock( &mutex1 );
    con2[j++]=deQueue();
    pthread_mutex_unlock( &mutex1 );
}
void *consume(){
    while(front!=-1){
        consumerA();
        consumerB();
    }
}
int main()
{
   pthread_t producer,consumerA,consumerB;
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
    return EXIT_SUCCESS;
}