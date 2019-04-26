#include<iostream>
using namespace std;
class PriorityQueue{
    int heapSize;
    int *Heap;
    public:
    PriorityQueue(int size){
        heapSize=size;
        Heap=new int[100];
    }
    void insertValue();
    int extractMin();
    void insertNewValue(int value);
    void heapifyUp(int index);
    void heapifyDown(int index);
    int minIndex(int i,int j);
    int swapValue(int i,int j);
    void printHeap();
};
int PriorityQueue::minIndex(int i,int j){
    if(Heap[j]>=Heap[i])
        return i;
    else
        return j;
}
int PriorityQueue::swapValue(int i,int j){
    int temp=Heap[j];
    Heap[j]=Heap[i];
    Heap[i]=temp;
}
int PriorityQueue::extractMin(){
    int value=Heap[1];
    Heap[1]=1000000;
    heapifyDown(1);
    heapSize--;
    return value;
}
void PriorityQueue::insertNewValue(int value){
    Heap[heapSize+1]=value;
    heapifyUp(heapSize++);
}
void PriorityQueue::heapifyUp(int index){
    if(index>1){
        int parentIndex=index/2;
        if(Heap[parentIndex]>Heap[index]){
            swapValue(parentIndex,index);
            heapifyUp(parentIndex);
        }
    }
}
void PriorityQueue::heapifyDown(int index){
    int minValueIndex;
    int newIndex=index*2;
    if( newIndex >heapSize)
        return;
    else if(newIndex<heapSize)
        minValueIndex=minIndex(newIndex,newIndex+1);
    else
        minValueIndex=newIndex; 
  
    if(Heap[index]>Heap[minValueIndex]){
        swapValue(minValueIndex,index);
        heapifyDown(minValueIndex);
    }  
}
void PriorityQueue::printHeap(){
    for(int i=1;i<=heapSize;i++){
        cout<<Heap[i]<<" ";
    }
}
void PriorityQueue::insertValue(){
    for(int i=1;i<=heapSize;i++){
        cin>>Heap[i];
        heapifyUp(i);
    }
}
int main(){
    int size;
    cout<<"Enter the size of List\n";
    cin>>size;
    PriorityQueue object(size);
    int *List;
    List=new int[size];
    object.insertValue();
    object.printHeap();
    cout<<"\n";
    for(int i=1;i<size;i++){
        List[i]=object.extractMin();
        cout<<List[i]<<" ";
    }
}