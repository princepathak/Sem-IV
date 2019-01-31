#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct Node
{
    int data;
    struct Node *next;
};
int is_empty(struct Node *Head){
    if(Head==NULL){
        return 0;
    }
    return 1;
}
int is_element_of(int x,struct Node *Head){
    struct Node *current=Head;
    while(current!=NULL){
        if(current->data==x){
            return 0;
        }
        current=current->next;
    }
    return 1;
}
void print(struct Node *Head){
    struct Node *current=Head;
    while(current!=NULL){
        printf("%d ",current->data);
        current=current->next;
    }
}
int size(struct Node *Head){
    struct Node *current=Head;
    int count=0;
    while(current!=NULL){
        count++;
        current=current->next;
    }
    return count;
}
struct Node * add(int value,struct Node* head){
    struct Node* newnode=(struct Node *)malloc(sizeof(struct Node));
    newnode->data=value;
    newnode->next=NULL;
    struct Node *temp;
    temp=head;
    if(head!=NULL){
        while(temp->next!=NULL){
        temp=temp->next;
        }
        temp->next=newnode;
    }
    else{
        head=newnode;
    }
    return head;
}
struct Node* build(int a[],int n){
    struct Node *Head=NULL;
    int i=0;
    while(n--){
        if(is_element_of(a[i],Head)){
            Head=add(a[i],Head);
        }
        i++; 
    }
    return Head;
}
struct Node* Union(struct Node *Set1,struct Node *Set2){
    int size_SET1=size(Set1);
    int size_SET2=size(Set2);
    struct Node* Head;
    while(Set1!=NULL){
        Head=add(Set1->data,Head);
        Set1=Set1->next;
    }
    while(Set2!=NULL){
        if(is_element_of(Set2->data,Head)){
            Head=add(Set2->data,Head);
        }
        Set2=Set2->next;
    }
    return Head;
}
struct Node* intersection(struct Node* S,struct Node * T){
    int size_SET1=size(S);
    int size_SET2=size(T);
    struct Node* Head;
    if(size_SET1<=size_SET2){
        while(S!=NULL){
            if(!is_element_of(S->data,T)){
                Head=add(S->data,Head);
            }
            S=S->next;
        }
    }
    return Head;
}

struct Node* difference(struct Node *S,struct Node *T){
    struct Node* Head=NULL;
        while(S!=NULL){
            if(is_element_of(S->data,T)){
                Head=add(S->data,Head);
            }
            S=S->next;
        }
    return Head;
}
int subset(struct Node *S,struct Node*T){
    while(S!=NULL){
        if(is_element_of(S->data,T)){
            return 0;
        }
        S=S->next;
    }
    return 1;
}
int main(){
int a[10];
srand(time(0));
for(int i=0;i<10;i++){
    a[i]=rand()%100+1;
}
struct Node *S,*P,*S_union_P,*S_intersection_P,*S_difference_P;
S=build(a,10);
print(S);
printf("\n");

int b[15]; 
srand(time(NULL));
for(int i=0;i<15;i++){
    b[i]=rand()%100+1;
}
P=build(b,15);
print(P);
printf("\n");

S_union_P=Union(S,P);
print(S_union_P);
printf("\n");

S_intersection_P=intersection(S,P);
print(S_intersection_P);
printf("\n");
S_difference_P=difference(P,S);
print(S_difference_P);
printf("\n");

printf("S is subset of T %d",subset(S,P));
}
