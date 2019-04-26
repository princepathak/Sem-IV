#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 5 
char arr[size],con1[100],con2[100];  
int front=-1,rear=-1,counter=0,k=0,j=0,consumeCounter=1,data=0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataProduced = PTHREAD_COND_INITIALIZER;
pthread_cond_t dataConsumed = PTHREAD_COND_INITIALIZER;
void enQueue(char value) 
{ 
    if ((front == 0 && rear == size-1) || (rear == (front-1)%(size-1))){ 
        printf("\nQueue is Full"); 
        return; 
    } 
    else if (front == -1){ 
        front = rear = 0; 
        arr[rear] = value; 
    } 
    else if (rear == size-1 && front != 0) { 
        rear = 0; 
        arr[rear] = value; 
    } 
    else{ 
        rear++; 
        arr[rear] = value; 
    } 
} 

char deQueue() 
{ 
    if (front == -1) { 
        printf("\nQueue is Empty"); 
        return '\0'; 
    }  
    int data1 = arr[front]; 
    arr[front] = -1; 
    if (front == rear) { 
        front = -1; 
        rear = -1; 
    } 
    else if (front == size-1) 
        front = 0; 
    else
        front++; 
    return data1; 
} 
  
void* produce(){
    FILE *fp;
    fp=fopen("string.txt","r");
    char ch=getc(fp);
    while(ch!=EOF){
        pthread_mutex_lock( &mutex1 );
        while(data==5)
            pthread_cond_wait(&dataConsumed,&mutex1);
        while(!((front == 0 && rear == size-1) || (rear == (front-1)%(size-1)))){
            enQueue(ch);
            ch=getc(fp);
            if(ch==EOF){
                data++;
                break;
            } 
            counter++;
            data++;
            pthread_cond_broadcast(&dataProduced);  
        }
        if(ch==EOF){
            pthread_cond_broadcast(&dataProduced);
            pthread_mutex_unlock( &mutex1 );
            return NULL;
        }
        pthread_mutex_unlock( &mutex1 );         
    }
    fclose(fp);
    return NULL;
}

void *consumerA(){  
   while(1){
        pthread_mutex_lock( &mutex1 );
        while(data<=0)
            pthread_cond_wait(&dataProduced,&mutex1);
        if(consumeCounter%3!=0){
        con1[k++]=deQueue();
        consumeCounter+=1;
        data-=1;
        pthread_cond_signal(&dataConsumed);
        }
        else if(k+j>=counter){
            pthread_mutex_unlock( &mutex1 );
            return NULL;
        }
        pthread_mutex_unlock( &mutex1 );
   }
   return NULL;
}

void *consumerB(){
    while(1){
        pthread_mutex_lock( &mutex1 );
        while(data<=0)
            pthread_cond_wait(&dataProduced,&mutex1);
        if(consumeCounter%3==0){
        con2[j++]=deQueue();
        consumeCounter+=1;
        data--;
        pthread_cond_signal(&dataConsumed);
        }  
        else if(k+j>=counter){
            pthread_mutex_unlock( &mutex1 );
            return NULL;
        }
        pthread_mutex_unlock( &mutex1 );       
    }
    return NULL; 
}

int main(){
    pthread_t producer,consumer_A,consumer_B;
    int rc1,rc2,rc3;
    rc1 = pthread_create(&producer, NULL,&produce,NULL);
    rc2 = pthread_create(&consumer_A, NULL,&consumerA,NULL);
    rc3 = pthread_create(&consumer_B, NULL,&consumerB,NULL);
    for(int temp=0;temp<k;temp++){
        printf("%c ",con1[temp]);
    }
    printf("\n");
    for(int temp=0;temp<j;temp++){
        printf("%c ",con2[temp]);
    }  
    return EXIT_SUCCESS;
}