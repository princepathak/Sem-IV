#include<iostream>
#include<stdlib.h>
#include<queue>
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
void swap(int *xp, int *yp) 
	{ 
		int temp = *xp; 
		*xp = *yp; 
		*yp = temp; 
	} 
void bubbleSort(int a[] , int n,int b[]) { 
	int i, j; 
	for (i = 0; i < n; i++)          
       for (j = 0; j < n-i-1; j++)  
           if (a[j] > a[j+1]){
                swap(&a[j], &a[j+1]);
                swap(&b[j], &b[j+1]); 
           } 
              
}
void Print(Process a){
        cout<<"\n";
        cout<<'P'<<a.processNumber<<"\t";
        cout<<a.arrivalTime<<"\t";
        cout<<a.cpuBurst<<"\n";
}
void calculateTime(int rT[],int tT[],int wT[],int cT[],Process Proc[],int size){
    Process temp,temp1;
    int totalCpuBurst=0;
    for(int j=0;j<size;j++){
        int responseTime=0;
        for(unsigned int i=0;i<size;i++){
            temp=Proc[i]; 
            if(temp.processNumber==j && temp.cpuBurst!=0){
                *(rT+j)=responseTime;
                    for(int i=0;i<size;i++){
                        if(Proc[i].processNumber==j)
                        *(rT+j)-=Proc[i].arrivalTime;
                    }
                break;
            }
            responseTime+=temp.cpuBurst;
        }
    }
    for(int i=0;i<size;i++){
        int temp=Proc[i].processNumber;
        tT[temp]=cT[temp]-Proc[i].arrivalTime;
        wT[temp]=tT[temp]-Proc[i].cpuBurst;
    }
    
} 
void printGanttChart(queue<Process> gant_chart){
    int time_incurred=0;
    Process temp;
    cout<<"Process No.\tCPU cycle\tCPU burst\n";
    while(!gant_chart.empty()){
        temp=gant_chart.front();
        cout<<"\n";
        cout<<'P'<<temp.processNumber<<"\t";
        cout<<time_incurred<<"\t";
        cout<<temp.cpuBurst<<"\n";
        gant_chart.pop();
        time_incurred+=temp.cpuBurst;
    }
}
int main(){
    int *processNumber,*arrivalTime,*cpuBurst,*responseTime,*TAT,*waitingTime,*completeTime;
    int n;
    cout<<"Enter the no. of process\n";
    cin>>n;
    processNumber= new int[n];
    arrivalTime=new int[n];
    cpuBurst=new int[n];
    Process *proc,*tempProcess;
    proc =(Process *)malloc(n*sizeof(Process));
    tempProcess=(Process *)malloc(n*sizeof(Process));
    responseTime= new int[n];
    TAT= new int[n];
    waitingTime= new int[n];
    completeTime=new int[n];
    FILE *file;
    file=fopen("Q1.txt","r");
    char dummy;
    for(int i=0;i<n;i++){
        cin>>arrivalTime[i]>>cpuBurst[i];
        // fscanf(file,"%d",&processNumber[i]);
        // fscanf(file,"%c",&dummy);
        // fscanf(file,"%d",&arrivalTime[i]);
        // fscanf(file,"%c",&dummy);
        // fscanf(file,"%d",&cpuBurst[i]);
        // fscanf(file,"%c",&dummy);
        proc[i].arrivalTime=arrivalTime[i];
        proc[i].cpuBurst=cpuBurst[i];
        proc[i].processNumber=processNumber[i]=i;
    }
    fclose(file);
    bubbleSort(arrivalTime,n,processNumber);
    int sum=0;
    for(int i=0;i<n;i++){
        tempProcess[i]=proc[processNumber[i]];
    }
    int total_cpu_burst=0;
    queue<Process> RR,gantt_chart;
    for(int i=0;i<n;i++){
        proc[i]=tempProcess[i];
        total_cpu_burst+=tempProcess[i].cpuBurst;
        gantt_chart.push(tempProcess[i]);
        sum+=tempProcess[i].cpuBurst;
        completeTime[i]=sum;
    }
    for(int i=0;i<n;i++){
        Print(tempProcess[i]);
    }
    printGanttChart(gantt_chart);
    calculateTime(responseTime,TAT,waitingTime,completeTime,proc,n);
    for(int i=0;i<n;i++){
        cout<<"rT "<<responseTime[i]<<" tT "<<TAT[i]<<" wT "<<waitingTime[i]<<" cT "<<completeTime[i]<<endl;
    }
return 0;
}