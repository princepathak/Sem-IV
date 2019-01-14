 
    #include <stdio.h>
    #include <stdlib.h>
	#include<time.h>
     
	void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
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
      int size=ftell(ptr1)/4.899;
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
		selectionSort(ptr,size);
		clock_t end = clock();
		int  time_elapsed_in_milliseconds = (end - start)/(CLOCKS_PER_SEC/1000);
		printf("%d",time_elapsed_in_milliseconds);
		for(int i=0;i<size;i++)
        {               
            fprintf(ptr2,"%d ",*(ptr+i));              
        } 
		fclose(ptr2);
      return 0;
      }
