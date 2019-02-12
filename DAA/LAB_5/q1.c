   #include <stdio.h>
    #include <stdlib.h>
     
    int main(int arg,char *argv[]) {
    if(arg !=3){
    printf("Incorrect no. parameters passed");
    return 0;
    }
    int b=atoi(argv[1]);

      FILE *filePointer;     
      filePointer = fopen(argv[2], "w") ;                        
        for(int i=0;i<b;i++)
        {               
            fprintf(filePointer,"%d ",rand()%b+1) ;
        }        
        fclose(filePointer) ;          
      return 0;
}
