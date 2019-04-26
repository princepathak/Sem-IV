#include<iostream>
#include<vector>
#include<cstring>
#define Threshold 5
#define max 100000
#define MEM_SIZE 100
using namespace std;

class Node{ //the node of alloc and free list
    public:
    int blockNumber;
    int startAddress;
    int size;
    Node(){
        startAddress=0;
        size=0;
        blockNumber=0;
    }
};
void swap(Node *xp, Node *yp) 
	{ 
		Node temp = *xp; 
		*xp = *yp; 
		*yp = temp; 
	}
//Initilization of Alloc list and free list
vector<Node> freeList;
vector<vector<Node>> allocList;
void sortList(vector<Node> List){
    int size=List.size();
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if (List[j].startAddress > List[j+1].startAddress){
                swap(&List[j], &List[j+1]);
           }
        }
    }
};
bool malloc_bestfit(int mem[],int block_size,int block_number){
    int index,count=0,diff;
    Node temp;
    int min=max;
    for (auto i = freeList.begin(); i != freeList.end(); ++i){
        temp=*i;
        diff=temp.size-block_size;
        if(temp.size>=block_size){
            if(diff<min){
                min=diff;
                index=count;
            }
        }
        count++;
    }
    if(min!=max){
        int rem=block_size%Threshold;
        temp.blockNumber=block_number;
        if(temp.size-block_size>=Threshold){
            Node temp1=temp;          
            temp1.startAddress=temp.startAddress+block_size+Threshold-rem;
            temp1.size=temp.size-block_size-Threshold+rem;
            freeList[index]=temp1;
            if(rem<Threshold){
                temp.size=block_size+Threshold-rem;
                for(int i=temp.startAddress;i<block_size;i++){
                *(mem+i)=1;
            }
                //memset(mem+temp.startAddress,1,block_size*sizeof(int));
                memset(mem+temp.startAddress+block_size,-1,(temp.size-block_size)*sizeof(int)); 
            }           
        }
        else{
            freeList.erase(freeList.begin()+index);
            for(int i=temp.startAddress;i<block_size;i++){
                *(mem+i)=1;
            }
            //memset(mem+temp.startAddress,1,block_size);
            memset(mem+temp.startAddress+block_size,-1,(temp.size-block_size)*sizeof(int));
        }
        allocList.push_back(temp);
        sortList(allocList);
        return true;
    }
    else{
        return false;
    }
}

bool freeBlock(int blockNumber,int mem[]){
    int index,count=0;
    vector<Node> temp,current;
    Node previous,next;
    for (auto i = allocList.begin(); i != allocList.end(); ++i){
        temp=*i;
        if(temp.front().blockNumber == blockNumber){
            allocList.erase(allocList.begin()+count);
            break;
        }
        if(i==allocList.end() && temp.front().blockNumber!=(*allocList.end()).front().blockNumber){
            return false;
        }
        count++;
    }
    count=0;
    current=temp;
    if((*freeList.begin()).startAddress==MEM_SIZE){
        freeList.erase(freeList.begin());
        current.front().blockNumber=0;
        freeList.push_back(current.front());
        sortList(freeList);
        memset(mem+current.front().startAddress,0,current.front().size*sizeof(int));
    }
    else{
        for (auto i = freeList.begin(); i != freeList.end(); ++i){
            temp.front()=*i;
            if(temp.front().startAddress> current.front().startAddress){
                break;
            }
            count++;
        }
        previous=freeList[count-1];
        next=temp;
    }
    if(current.startAddress==MEM_SIZE-current.size){
        if(temp.startAddress+temp.size==current.startAddress){
            temp.size+=current.size;
            freeList[count]=temp;
        }
        else{
            current.blockNumber=0;
            freeList.push_back(current);
        }
    }
    else{
        if(previous.startAddress+previous.size==current.startAddress){
            if(current.startAddress+current.size==next.startAddress){
                temp.startAddress=previous.startAddress;
                temp.size=previous.size+current.size+next.size;
                freeList[count-1]=temp;
                freeList.erase(freeList.begin()+count);
            }
            else{
                temp.startAddress=previous.startAddress;
                temp.size=previous.size+current.size;
                freeList[count-1]=temp;
            }
        memset(mem+temp.startAddress,0,temp.size*sizeof(int));
        }
    }  
    return true;
}
void printAllocList(vector<Node> List){
    cout<<"Alloc List is printed\n";
    Node temp;
    for (auto i = List.begin(); i != List.end(); ++i){
        temp=*i;
        cout<<temp.blockNumber<<"\t"<<temp.startAddress<<"\t"<<temp.size<<"\n";
    }
}
void printFreeList(vector<Node> List){
    cout<<"Free List is printed\n";
    Node temp;
    for (auto i = List.begin(); i != List.end(); ++i){
        temp=*i;
        cout<<temp.startAddress<<"\t"<<temp.size<<"\n";
    }
}
int main(){
    int memory[100]={0};
    int input[10][2]={{7,1},{12,2},{28,3},{4,4},{9,5},
                     {25,6},{19,7},{45,8},{15,9},{26,10}};
    Node temp;
    temp.blockNumber=0;
    temp.size=100;
    temp.startAddress=0;
    freeList.push_back(temp);
    bool result;
    for(int i=0;i<10;i++){
        result=malloc_bestfit(memory,input[i][0],input[i][1]);
        if(result==true){
            cout<<"allocated successfully\n";
        }
        else{
            cout<<"Memory not allocated\n";
        }
    }
    printAllocList(allocList);
    printFreeList(freeList);
    bool res;
    res=freeBlock(2,memory);
    if(res==false)
        cout<<"Block not freed\n";
    res=freeBlock(6,memory);
    if(res==false)
        cout<<"Block not freed\n";
    res=freeBlock(3,memory);
    if(res==false)
        cout<<"Block not freed\n";
    printAllocList(allocList);
    printFreeList(freeList);
    for(int i=0;i<100;i++){
        cout<<memory[i]<<"\t";
        if((i+1)%10==0)
            cout<<"\n";
    }
    return 0;
}