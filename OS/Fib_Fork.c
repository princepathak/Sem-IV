#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main(){
int a=0;
int b=1,next=0;
int n;
printf("Enter the value\n");
scanf("%d",&n);
while(b<n){
    printf("%d",next);
    a=b;
    b=next;
    next=a+b;
    if(!fork()){
        continue;
    }
    else{
        exit(0);
    }

}
}