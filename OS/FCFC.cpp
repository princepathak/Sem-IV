#include<iostream>
#include<bits/stdc++.h>
#include<queue>
#include<list>
#define N 3
using namespace std;
class Node{
    public:
    int processNumber ;
    int arrival_time;
    int CPU_burst;    
    Node(){     
    }
    void getValues(int processNum,int x,int y){
        arrival_time=x;
        CPU_burst=y;
        processNumber=processNum;
    }
    
};
list<Node> sort(list<Node> x){
    int length=x.size();
    list<Node> sort;
    while(true){
        Node a=x.front();
        for(auto i:x){
            if(a.arrival_time>=i.arrival_time){
                a=i;
            }
        }
        x.remove(a);
        sort.push_front(a);
        if(sort.size()==length)
            break;       
    }
    return sort;
}
// queue<Node> FCFS(list<Node> x){

// }
void Print(Node a){
        cout<<"\n";
        cout<<a.processNumber<<"\t";
        cout<<a.arrival_time<<"\t";
        cout<<a.CPU_burst<<"\n";
    }

int main(){
    list<Node> Proc;
    Node a[N];
    int arrivalTime,cpuBurst;
    for(int i=0;i<N;i++){
        cout<<"Enter the arrival time and CPU burst respectively separated by space"; 
        cin>>arrivalTime>>cpuBurst;
        a[i].getValues(i,arrivalTime,cpuBurst);
        Proc.push_back(a[i]);
    }
    list<Node> sortedArrivalTime=sort(Proc);
    for (auto it:Proc){
        Node b=it;
        Print(b);
    }
    for (auto it:sortedArrivalTime){
        Node b=it;
        Print(b);
    }
    return 0; 
}