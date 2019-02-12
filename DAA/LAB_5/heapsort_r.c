
/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
#include<time.h>
  
/* Iterative C program for merge sort */

void swap(int *a ,int  *b){
	int c = *a;
	*a = *b;
	*b = c; 
}  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        swap(&arr[i], &arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
// main function to do heap sort 
void heapSort(int arr[], int n) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        swap(&arr[0], &arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
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

