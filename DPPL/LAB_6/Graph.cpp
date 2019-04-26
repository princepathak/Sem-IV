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
bool pexist(graph *s,int e,int f,int h1,int n,int varr[])
{
  graph *temp;
  int i;
  if(h1>0 && varr[h1]==e)
    return false;
  for(i=0;i<n;i++)
  {
       if((s[i].next)!=NULL)
      {
      if((s[i].next)->v==e)
      {
        temp=s[i].next;
        while(temp!=NULL)
        {
            temp=temp->next;
            if(temp!=NULL)
            {
             varr[h1]=temp->v;
             h1++;
            if(temp->v==f)
                return true;
            else if(pexist(s,temp->v,f,h1,n,varr))
            {
               return true;
            }
            }
        }
        break;
      }
      }
  }
    return false;
}
void mvertex(graph *s,int arr[],int n)
{
    int h,i;
    for(i=n-1;i>=0;i--)
    {
         for(h=0;h<n;h++)
        {
        if(h!=i)
        {
            int varr[n],h1=0;
        if(!pexist(s,arr[i],arr[h],h1,n,varr))
             break;
        }
        }
        if(h==n)
        {
            cout<<"Mother vertex is"<<arr[i];
            break;
        }
    }
    if(i<0)
        cout<<"No mother vertex exist";
}
int path(graph *s,int sv,int ev,int varr[],int h1,int n,int f)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        if(s[i].next!=NULL && s[i].next->v==sv)
        {
            graph * t=s[i].next;
            varr[h1]=t->next->v;
            h1++;
            if(varr[h1-1]==ev)
            {
                f=1;
                cout<<"The path is:-";
                for(j=0;j<h1;j++)
                    cout<<varr[j]<<"\t";
                cout<<"\nThe length of path is:-"<<h1;
                return f;
            }
             for(j=0;j<h1-1;j++)
                if(varr[j]==varr[h1-1])
                    return f;
                f=path(s,t->next->v,ev,varr,h1,n,f);
                t=t->next;
                while(t->next!=NULL && f==0)
                {
                        h1--;
                        varr[h1]=t->next->v;
                        h1++;
                        if(varr[h1-1]==ev)
                        {
                        f=1;
                        cout<<"The path is:-";
                        for(j=0;j<h1;j++)
                            cout<<varr[j]<<"\t";
                        cout<<"\nThe length of path is\n"<<h1;
                        return f;
                        }
                        f=path(s,t->next->v,ev,varr,h1,n,f);
                  t=t->next;
                }
        }
    }
    return f;
}
void tsort(graph *s,int n,int arr[])
{
    int i,k=0,j,fi,si;
    graph *t;
    for (i=0;i<n;i++)
    {
        if(s[i].next!=NULL)
        {
          arr[k]=s[i].next->v;
          k++;
        }
    }
    for(int h=0;h<n;h++)
    {
    for(i=0;i<n;i++)
    {
        if(s[i].next!=NULL)
        {
          t=s[i].next->next;
          while(t!=NULL)
          {
              si=fi=-1;
           for(j=0;j<k;j++)
           {
               if(arr[j]==s[i].next->v)
                fi=j;
               if(arr[j]==t->v)
                si=j;
           }
           if(si==-1)
           {
               arr[k]=t->v;
               k++;
           }
           else if(si<fi)
           {
               int t1=arr[fi];
               for(int g=fi-1;g>=si;g--)
               {
                   arr[g+1]=arr[g];
               }
               arr[si]=t1;
           }
           t=t->next;
          }
        }
    }
    }
}
void dag(graph *s,int n)
{
    int as[n],i,j,maxedge=0;
    int c;
    tsort(s,n,as);
    for(i=0;i<n-1;i++)
    {
        c=0;
        for(j=0;j<n;j++)
        {
            if(s[j].next!=NULL &&s[j].next->v==as[i])
            {
                graph *temp=s[j].next->next;
                while(temp!=NULL)
                {
                     c++;
                    temp=temp->next;

                }
                if(c!=0)
                maxedge+=(n-c-1-i);
            }
        }
        if(c==0)
             maxedge+=(n-1-i);
    }
    cout<<maxedge;
}
int main()
{
//cout<<"Enter number of vertices";
int n=7,i;
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
s1=addedge(s1,3,4,arr,n);
//random graph
s1=addedge(s1,0,2,arr,n);
s1=addedge(s1,0,5,arr,n);
s1=addedge(s1,3,1,arr,n);
s1=addedge(s1,2,3,arr,n);
s1=addedge(s1,5,4,arr,n);
s1=addedge(s1,1,4,arr,n);
//s1=addedge(s1,6,-1,arr,n);
//input graph of mam
s1=addedge(s1,4,2,arr,n);
s1=addedge(s1,7,1,arr,n);
s1=addedge(s1,7,3,arr,n);
s1=addedge(s1,5,3,arr,n);
s1=addedge(s1,5,6,arr,n);
s1=addedge(s1,6,8,arr,n);
s1=addedge(s1,9,-1,arr,n);
s1=addedge(s1,4,8,arr,n);
s1=addedge(s1,2,10,arr,n);
s1=addedge(s1,7,6,arr,n);*/
printgraph(s1,n);
mvertex(s1,arr,n);
cout<<"\n";
int varr[n],h1=0,sv,ev;
cout<<"Enter starting vertex";
cin>>sv;
cout<<"Enter ending vertex";
cin>>ev;
varr[h1]=sv;
h1++;
path(s1,sv,ev,varr,h1,n,0);
cout<<"\n";
cout<<"Topological Sort is:-";
int as[n];
tsort(s1,n,as);
for(i=0;i<n;i++)
   {
        cout<<as[i]<<"\t";
   }
cout<<"\nThe no. of edges that can be added are: ";
dag(s1,n);
}
