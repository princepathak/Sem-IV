
/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
#include<time.h>
  
/* Iterative C program for merge sort */
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r); 
  
/* l is for left index and r is right index of the sub-array 
  of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
   if (l < r) 
   { 
      int m = l+(r-l)/2; //Same as (l+r)/2 but avoids overflow for large l & h 
      mergeSort(arr, l, m); 
      mergeSort(arr, m+1, r); 
      merge(arr, l, m, r); 
   } 
} 
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
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
		mergeSort(ptr,0,size);
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

