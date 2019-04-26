#include<iostream>
#include<stdlib.h>
using namespace std;
class Process{
    public:
        int processNumber;
        int arrivalTime;
        int cpuBurst;
        Process(){
            processNumber=0;
            arrivalTime=0;
            cpuBurst=0;
        }
};
void Print(Process a){
        cout<<"\n";
        cout<<'P'<<a.processNumber<<"\t";
        cout<<a.arrivalTime<<"\t";
        cout<<a.cpuBurst<<"\n";
}
int main(){
    int n;
    cout<<"Enter the no. of process\n";
    cin>>n;
    int *processNumber,*arrivalTime,*cpuBurst;
    processNumber= new int[n];
    arrivalTime=new int[n];
    cpuBurst=new int[n];
    Process *proc,*tempProcess;
    proc =(Process *)malloc(n*sizeof(Process));
    tempProcess=(Process *)malloc(n*sizeof(Process));
    FILE *file;
    file=fopen("Q1.txt","r");
    char dummy;
    for(int i=0;i<n;i++){
        //cin>>arrivalTime[i]>>cpuBurst[i];
        fscanf(file,"%d",&processNumber[i]);
        cout<<" "<<processNumber[i];
        fscanf(file,"%c",&dummy);
        fscanf(file,"%d",&arrivalTime[i]);
        cout<<" "<<arrivalTime[i];
        fscanf(file,"%c",&dummy);
        fscanf(file,"%d",&cpuBurst[i]);
        cout<<" "<<cpuBurst[i];
        fscanf(file,"%c",&dummy);
        proc[i].arrivalTime=arrivalTime[i];
        proc[i].cpuBurst=cpuBurst[i];
        proc[i].processNumber=processNumber[i]=i;
    }
    fclose(file);
    int sum=0;
    for(int i=0;i<n;i++){
        Print(proc[i]);
    }
}