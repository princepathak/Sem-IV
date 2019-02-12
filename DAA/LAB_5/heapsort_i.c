
/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
#include<time.h>

void swap(int *a ,int  *b){
	int c = *a;
	*a = *b;
	*b = c; 
}  
/* Iterative C program for merge sort */
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */

void buildMaxHeap(int arr[], int n)  
{  
    for (int i = 1; i < n; i++)  
    { 
        // if child is bigger than parent 
        if (arr[i] > arr[(i - 1) / 2])  
        { 
            int j = i; 
      
            // swap child and parent until 
            // parent is smaller 
            while (arr[j] > arr[(j - 1) / 2])  
            { 
                swap(&arr[j], &arr[(j - 1) / 2]); 
                j = (j - 1) / 2; 
            } 
        } 
    } 
} 
  
void heapSort(int arr[], int n)  
{ 
    buildMaxHeap(arr, n); 
  
    for (int i = n - 1; i > 0; i--) 
    { 
        // swap value of first indexed  
        // with last indexed  
        swap(&arr[0], &arr[i]); 
      
        // maintaining heap property 
        // after each swapping 
        int j = 0, index; 
          
        do
        { 
            index = (2 * j + 1); 
              
            // if left child is smaller than  
            // right child point index variable  
            // to right child 
            if (arr[index] < arr[index + 1] && 
                                index < (i - 1)) 
                index++; 
          
            // if parent is smaller than child  
            // then swapping parent with child  
            // having higher value 
            if (arr[j] < arr[index] && index < i) 
                swap(&arr[j], &arr[index]); 
          
            j = index; 
          
        } while (index < i); 
    } 
} 

  
/* Function to print an array */
int main(int arg,char *argv[]) {
    if(arg !=4){
    printf("Incorrect no. parameters passed");
    return 0;
    }
	
      int x;
      int size=atoi(argv[3]);
      FILE *ptr1; 
      FILE *ptr2;    
      ptr1 = fopen(argv[1], "r") ;
      ptr2=fopen(argv[2],"w");  
      //fseek(ptr1,0L,SEEK_END);
      //int size=ftell(ptr1)/5.8;
	printf("%d\n",size);
      //rewind(ptr1);
	  int i=0;
      int *ptr=(int *)malloc(sizeof(int)*size); 
        for(int i=0;i<size;i++)
        {               
            fscanf(ptr1,"%d ",&x);
            *(ptr+i)=x; 
        }        
        fclose(ptr1) ;
	clock_t start = clock();
	heapSort(ptr, size);
	clock_t end = clock();
	float  time_elapsed_in_milliseconds = (end - start)/(CLOCKS_PER_SEC/1000);
	printf("%f",time_elapsed_in_milliseconds);
	for(int i=0;i<size;i++)
        {               
            fprintf(ptr2,"%d ",*(ptr+i));              
        } 
		fclose(ptr2);
      return 0;
}   

