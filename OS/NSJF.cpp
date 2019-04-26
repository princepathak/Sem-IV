#include<iostream>
#include<stdlib.h>
#include<queue>
#include<vector>
#define max 10000
using namespace std; 
class Process{
    public:
        int processNumber;
        int arrivalTime;
        int cpuBurst;
        int timeStart;
        Process(){
            processNumber=0;
            arrivalTime=0;
            cpuBurst=0;
            timeStart=0;
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
int find(vector<Process> temp,int time){
    int min=max,index=0,count=0;
    Process Proc;
    vector<Process>::iterator Iterator;
    for(Iterator=temp.begin();Iterator!=temp.end();Iterator++){
        Proc=*Iterator;
        if(Proc.cpuBurst<=min && Proc.arrivalTime<=time){
            min=Proc.cpuBurst;
            index=count;
        }
        count++;
    }
    return index;
}
void Print(Process a){
    cout<<"\n";
    cout<<'P'<<a.processNumber<<"\t";
    cout<<a.arrivalTime<<"\t";
    cout<<a.cpuBurst<<"\n";
}
queue<Process> NonPremptiveShortestJobFirst(queue<Process> SJF,int cT[]){
    Process temp1;
    queue<Process> gantt_chart,temp;
    temp=SJF;
    vector<Process> SJF1;
    vector<Process>::iterator Iterator;
    int index;
    for(int i=0;i<SJF.size();i++){
        temp1=temp.front();
        SJF1.push_back(temp1);
        temp.pop();
    }
    int time_=0;
    temp1=SJF1.front();
    time_+=temp1.arrivalTime;
    while(!SJF1.empty()){
        index=find(SJF1,time_);
        temp1=SJF1[index];
        time_+=temp1.cpuBurst;
        temp1.timeStart=time_;
        cT[temp1.processNumber]=time_;
        gantt_chart.push(temp1);
        SJF1.erase(SJF1.begin()+index);
    }
    return gantt_chart;
}
queue<Process> PremptiveShortestJobFirst(queue<Process> SJF){
    Process temp1,temporary;
    queue<Process> gantt_chart,temp;
    temp=SJF;
    vector<Process> SJF1;
    vector<Process>::iterator Iterator;
    int index,totalCpuBurst=0,prevIndex;
    for(int i=0;i<SJF.size();i++){
        temp1=temp.front();
        totalCpuBurst+=temp1.cpuBurst;
        SJF1.push_back(temp1);
        temp.pop();
    }
    int totaltime=totalCpuBurst;
    int time_=0,cycleCounter=0,prevCpuBurst;;
    temp1=SJF1.front();
    time_+=temp1.arrivalTime;
    prevIndex=0,prevCpuBurst=temp1.cpuBurst;
    while(totalCpuBurst--){
        index=find(SJF1,time_);
        //Print(SJF1[index]);
        if(prevIndex==index){
            if(prevCpuBurst==SJF1[index].cpuBurst){
                time_--;
                totalCpuBurst++;
            }
            SJF1[index].cpuBurst--;
            time_++;
            if(SJF1[index].cpuBurst==0){
                SJF1[index].cpuBurst=10000000;
                time_--;
                totalCpuBurst++;
                //SJF1.erase(SJF1.begin()+index);
            }
            cycleCounter++;
        }
        else{
            temporary.processNumber=SJF1[prevIndex].processNumber;
            temporary.cpuBurst=cycleCounter;
            temporary.arrivalTime=totaltime-totalCpuBurst-1;
            cycleCounter=0;
            prevIndex=index;
            gantt_chart.push(temporary);
        }
        
        
    }
    return gantt_chart;
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
void calculateTime(int rT[],int tT[],int wT[],int cT[],queue<Process> gantt,Process Proc[],int size){
    vector<Process> gant;
    Process temp,temp1;
    int totalCpuBurst=0;
    for(int i=0;i<gantt.size();i++){
        temp1=gantt.front();

        gant.push_back(temp1);
        totalCpuBurst+=temp1.cpuBurst;
        gantt.pop();
    }
    for(int j=0;j<size;j++){
        int responseTime=0;
        for(unsigned int i=0;i<gant.size();i++){
            temp=gant[i]; 
            if(temp.processNumber==j){
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
    for(int i=0;i<n;i++){
        tempProcess[i]=proc[processNumber[i]];
    }
    int total_cpu_burst=0;
    queue<Process> RR,gantt_chart1,gantt_chart2;
    for(int i=0;i<n;i++){
        proc[i]=tempProcess[i];
        total_cpu_burst+=tempProcess[i].cpuBurst;
        RR.push(tempProcess[i]);
    }
    gantt_chart1=NonPremptiveShortestJobFirst(RR,completeTime);
    gantt_chart2=PremptiveShortestJobFirst(RR);
    for(int i=0;i<n;i++){
        Print(tempProcess[i]);
    }
    calculateTime(responseTime,TAT,waitingTime,completeTime,gantt_chart1,proc,n);
    for(int i=0;i<n;i++){
        cout<<"rT "<<responseTime[i]<<" tT "<<TAT[i]<<" wT "<<waitingTime[i]<<" cT "<<completeTime[i]<<endl;
    }
    printGanttChart(gantt_chart1);
    printGanttChart(gantt_chart2);
return 0;
}