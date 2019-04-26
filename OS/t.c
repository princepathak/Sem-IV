#include<stdio.h> 
#define size 5  
int front,rear,arr[size];
front= -1;
rear= -1;
void enQueue(int value) 
{ 
    if ((front == 0 && rear == size-1) || 
            (rear == (front-1)%(size-1))) 
    { 
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
int deQueue() 
{ 
    if (front == -1) 
    { 
        printf("\nQueue is Empty"); 
        return -10000; 
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
  
/* Driver of the program */
int main() 
{ 
    
  
    // Inserting elements in Circular Queue 
    enQueue(14); 
    enQueue(22); 
    enQueue(13); 
    enQueue(-6); 
  
    // Display elements present in Circular Queue 
    displayQueue(); 
  
    // Deleting elements from Circular Queue 
    printf("\nDeleted value = %d", deQueue()); 
    printf("\nDeleted value = %d", deQueue()); 
  
    displayQueue(); 
  
    enQueue(9); 
    enQueue(20); 
    enQueue(5); 
  
    displayQueue(); 
  
    enQueue(20); 
    return 0; 
} 