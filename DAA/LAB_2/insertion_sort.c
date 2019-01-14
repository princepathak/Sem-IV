 
    #include <stdio.h>
    #include <stdlib.h>
	#include<time.h>
     
	void insertionSort(int arr[], int n) 
{ 
   int i, key, j; 
   for (i = 1; i < n; i++) 
   { 
       key = arr[i]; 
       j = i-1; 
  
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
       } 
       arr[j+1] = key; 
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
		insertionSort(ptr,size);
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
