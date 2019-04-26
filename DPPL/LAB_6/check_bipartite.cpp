#include<iostream>
#include<stdlib.h>
using namespace std;
#define N 4
struct node
{
   int data;
   struct node *next;
};
struct node* front = NULL;
struct node* rear = NULL;
void Insert(int val)
{
   struct node* temp;
   if (rear == NULL) {
      rear = (struct node *)malloc(sizeof(struct node));
      rear->next = NULL;
      rear->data = val;
      front = rear;
   } else {
      temp=(struct node *)malloc(sizeof(struct node));
      rear->next = temp;
      temp->data = val;
      temp->next = NULL;
      rear = temp;
   }
}
int Delete()
{
    struct node* temp;
   temp = front;
   if (front == NULL)
    {
      cout<<"Underflow"<<endl;
      return -1;
   }
   else if (temp->next != NULL)
    {
      front = temp->next;
      return temp->data;
   }
    else
    {
      front =rear= NULL;
      return temp->data;
   }
}
struct node* top = NULL;
void push(int val) {
   struct node* newnode = (struct node*) malloc(sizeof(struct node));
   newnode->data = val;
   newnode->next = top;
   top = newnode;
}
int pop() {
   if(top==NULL)
      {
          cout<<"Stack Underflow"<<endl;
          return -1;
      }
   else {
        int d=top->data;
      top = top->next;
   return d;
   }
}
void adjacency_matrix(int *a,int arr[])
{
    int i,j,c;
do
{
    cout<<"Enter 1 to create connection,2 to delete connection 3 to exit";
    cin>>c;
    if(c==1)
    {
        char ch;
         for (i=0; i < N; i++)
      {
          for (j=i+1; j < N; j++)
          {

              cout<<"Enter Y if connection exist between "<<arr[i]<<" and "<<arr[j]<<" and N if it doesn't";
              cin>>ch;
              if(ch=='Y')
                {
                    *((a+(i*N))+j)=1;
                    *((a+(j*N))+i)=1;
                }
              else if(ch=='N');
                else
              {
                  cout<<"Enter correct choice\n";
                  j--;
              }
          }
      }
    }
    else if(c==2)
    {
        cout<<"Enter the 2 vertices where u want to delete connection";
        int d,f;
        cin>>d>>f;
        for(i=0;i<N;i++)
        {
            if(arr[i]==d)
                break;
        }
        for(j=0;j<N;j++)
        {
            if(arr[j]==f)
                break;
        }
        *((a+(i*N))+j)=0;
        *((a+(j*N))+i)=0;
    }
    else if(c!=3)
        cout<<"Enter correct choice";
}while(c!=3);
}
bool _bigraph(int arr[][N],int start_point, int *color,int c = 0)
{
    color[start_point] = c%2;
    for(int i = 0 ; i <N ; i++)
    {
        if(arr[start_point][i] || arr[i][start_point] && i != start_point)
            {
            if(color[i]==color[start_point]){
                return false;
            }
            if(color[i]==-1)
            {
                if(!_bigraph(arr,i,color,c+1))
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool is_bipartite(int arr[][N])
{
    int *color = new int[N];
    for(int i = 0 ; i <N ; i++)
    {
        color[i] = -1;
    }
    for(int i = 0 ; i <N; i++)
    {
        if(color[i] == -1)
        {
            if(!_bigraph(arr,i,color))
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
int i,j,t1;
int a[N][N],B[N][N],arr[N];
for(i=0;i<N;i++)
{
    for(j=0;j<N;j++)
    {
           a[i][j]=0;
    }
}

cout<<"Enter"<<N<<" vertices:-";
for(i=0;i<N;i++)
{
    cin>>arr[i];
}
adjacency_matrix((int *)a,arr);
cout<<"Adjacency Matrix is:\n";
for(i=0;i<N;i++)
{
    for(j=0;j<N;j++)
    {
           cout<<a[i][j]<<"\t";
    }
    cout<<"\n";
}
for(i=0;i<N;i++)
{
    for(j=0;j<N;j++)
    {
           B[i][j]=a[i][j];
    }
}
if(is_bipartite(B))
    cout<<"It is a bipartite graph";
else
    cout<<"Not a bipartite graph";
}
