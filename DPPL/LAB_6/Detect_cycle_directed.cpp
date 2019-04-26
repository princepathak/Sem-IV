#include<iostream>
#include<stdlib.h>
using namespace std;
struct graph
{
    int v;
    struct graph *next;
};
graph* create(int ver)
{
    graph *s1=(graph *)malloc(ver*sizeof(graph));
    for(int i=0;i<ver;i++)
    {
        s1[i].next=NULL;
    }
    return s1;
}
graph* addedge(graph *s1,int s,int d,int arr[],int n)
{
    graph *a=new graph;
    a->v=s;
    a->next=NULL;
    graph *a1=new graph;
    a1->v=d;
    a1->next=NULL;
    int i;
    for(i=0;i<n;i++)
    {
        if(arr[i]==s)
            break;
    }
    if((s1[i].next)==NULL)
    {
        if(d!=-1)
            a->next=a1;
        s1[i].next=a;
    }
    else
    {
        graph *temp;
        temp=s1[i].next;
        while(temp->next!=NULL)
        {
              temp=temp->next;
        }
        temp->next=a1;
    }
    return s1;
}
void printgraph(graph *s1,int n)
{
    graph *temp;
    int i,f=0;
    for(i=0;i<n;i++)
        {
         temp=(s1[i].next);
         if(temp!=NULL)
         {
        while(temp!=NULL)
        {
            cout<<temp->v<<"->";
              temp=temp->next;
              f=1;
        }
        cout<<"\n";
        }
        }
        if(f==0)
             cout<<"No element exist"<<endl;
}
int cycle(graph *s,int n)
{
    int varr[n],h;
    for(int i=0;i<n;i++)
    {
        h=0;
        if(s[i].next!=NULL)
        {
            graph *temp=s[i].next;
            varr[h]=temp->v;
            temp=temp->next;
            while(temp!=NULL)
            {
                h=1;
            varr[h]=temp->v;
            h++;
            for(int j=0;j<n;j++)
            {
                if(s[j].next!=NULL && s[j].next->v==varr[h-1])
                {
                     graph *temp1=s[j].next;
                        if(varr[0]==temp1->next->v)
                            return 1;
                varr[h]=temp1->next->v;
                h++;
                j=-1;
                }
            }
            temp=temp->next;
            }
        }
    }
    return 0;
}
int main()
{
int n=7;
int arr[n]={0,1,2,3,4,5,6};
graph *s1=(graph *)malloc(n*sizeof(graph));
s1=create(n);
//question 1 graph
s1=addedge(s1,0,1,arr,n);
s1=addedge(s1,0,2,arr,n);
s1=addedge(s1,6,0,arr,n);
s1=addedge(s1,4,1,arr,n);
s1=addedge(s1,5,2,arr,n);
s1=addedge(s1,5,6,arr,n);
s1=addedge(s1,6,4,arr,n);
s1=addedge(s1,1,3,arr,n);
//cyclic graph
/*s1=addedge(s1,0,2,arr,n);
s1=addedge(s1,1,0,arr,n);
s1=addedge(s1,2,1,arr,n);
s1=addedge(s1,0,3,arr,n);
s1=addedge(s1,3,4,arr,n);*/
//random graph
/*s1=addedge(s1,0,2,arr,n);
s1=addedge(s1,0,5,arr,n);
s1=addedge(s1,3,1,arr,n);
s1=addedge(s1,2,3,arr,n);
s1=addedge(s1,5,4,arr,n);
s1=addedge(s1,1,4,arr,n);*/
printgraph(s1,n);
if(cycle(s1,n))
    cout<<"Cycle exist";
else
    cout<<"Cycle does not exist";
}
