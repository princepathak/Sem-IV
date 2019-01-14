    #include <stdio.h>
    #include <stdlib.h>
	#include<time.h>
     
	 void swap(int *xp, int *yp) 
	{ 
		int temp = *xp; 
		*xp = *yp; 
		*yp = temp; 
	} 
	void bubbleSort(int *a , int n) 
	{ 
	int i, j; 
	for (i = 0; i < n-1; i++)          
       for (j = 0; j < n-i-1; j++)  
           if (*(a+j) > *(a+j+1)) 
              swap(a+j, a+j+1); 
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
      int size=ftell(ptr1)/4;
	  printf("%d",size);
      rewind(ptr1);
      int *ptr=(int *)malloc(sizeof(int)*size); 
        for(int i=0;i<size;i++)
        {               
            fscanf(ptr1,"%d ",&x);
            *(ptr+i)=x; 
        }        
        fclose(ptr1) ;
		clock_t start = clock();
		bubbleSort(ptr,size);
		clock_t end = clock();
		int  time_elapsed_in_milliseconds = (end - start)/(CLOCKS_PER_SEC/1000);
		printf("%2d",time_elapsed_in_milliseconds);
		for(int i=0;i<size;i++)
        {               
            fprintf(ptr2,"%d ",*(ptr+i));              
        } 
		fclose(ptr2);
      return 0;
      }
