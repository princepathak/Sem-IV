    #include <stdio.h>
    #include <stdlib.h>
	#include<time.h>
     void swap ( int* a, int* b ) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* This function is same in both iterative and recursive*/
int partition (int arr[], int l, int h) 
{ 
    int x = arr[h]; 
    int i = (l - 1); 
  
    for (int j = l; j <= h- 1; j++) 
    { 
        if (arr[j] <= x) 
        { 
            i++; 
            swap (&arr[i], &arr[j]); 
        } 
    } 
    swap (&arr[i + 1], &arr[h]); 
    return (i + 1); 
} 
  
/* A[] --> Array to be sorted,  
   l  --> Starting index,  
   h  --> Ending index */
void quickSortIterative (int arr[], int l, int h) 
{ 
    // Create an auxiliary stack 
    int stack[ h - l + 1 ]; 
  
    // initialize top of stack 
    int top = -1; 
  
    // push initial values of l and h to stack 
    stack[ ++top ] = l; 
    stack[ ++top ] = h; 
  
    // Keep popping from stack while is not empty 
    while ( top >= 0 ) 
    { 
        // Pop h and l 
        h = stack[ top-- ]; 
        l = stack[ top-- ]; 
  
        // Set pivot element at its correct position 
        // in sorted array 
        int p = partition( arr, l, h ); 
  
        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if ( p-1 > l ) 
        { 
            stack[ ++top ] = l; 
            stack[ ++top ] = p - 1; 
        } 
  
        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if ( p+1 < h ) 
        { 
            stack[ ++top ] = p + 1; 
            stack[ ++top ] = h; 
        } 
    } 
} 
	
	
    int main(int arg,char *argv[]) {
    if(arg !=3){
    printf("Incorrect no. parameters passed");
    return 0;
    }
	
      int x;
      FILE *ptr1; 
      FILE *ptr2;    
      ptr1 = fopen(argv[1], "r") ;
      ptr2=fopen(argv[2],"w");  
      fseek(ptr1,0L,SEEK_END);
      int size=ftell(ptr1)/5.8;
	  printf("%d\n",size);
      rewind(ptr1);
	  int i=0;
      int *ptr=(int *)malloc(sizeof(int)*size); 
        for(int i=0;i<size;i++)
        {               
            fscanf(ptr1,"%d ",&x);
            *(ptr+i)=x; 
        }        
        fclose(ptr1) ;
		clock_t start = clock();
		quickSortIterative(ptr,0,size);
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
