#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 20
struct Node
{
    int data;
    struct Node *next;
};

struct set
{
    struct Node * a[MAX];
};

int hashfunc(int value){
    int index =value%20;
    return index;
    
}
int is_empty(struct Node *Head[]){
    for(int i=0;i<MAX;i++){
        if(Head[i]!=NULL){
        return 1;
        }
    }
    return 0;
}
int is_element_of(int x,struct Node *Head[]){
    int index=hashfunc(x);
    struct Node *current=Head[index];
    while(current!=NULL){
        if(current->data==x){
        return 1;
        }
    current=current->next;
    }
    return 0;
}
void print(struct Node *Head[]){
    
    for(int i=0;i<MAX;i++){
        if(Head[i]==NULL){
            continue;
        }
        else{
            struct Node *current=Head[i];
            while(current!=NULL){
            printf("%d ",current->data);
            current=current->next;
    }
        }
    }
    
    
}
int size(struct Node *Head[]){
    int count=0;
    for(int i=0;i<MAX;i++){
        if(Head[i]==NULL){
            continue;
        }
        else{
            struct Node *current=Head[i];
            while(current!=NULL){
                count++;
                current=current->next;
            }
        }
    }
    return count;
}

void add(int value,struct Node* head[]){
    if(is_element_of(value,head))
        return;
    struct Node* newnode=(struct Node *)malloc(sizeof(struct Node));
    newnode->data=value;
    newnode->next=NULL;
    struct Node *temp;
    int index=hashfunc(value);
    temp=head[index];
    if(head[index]!=NULL){
        while(temp->next!=NULL){
        temp=temp->next;
        }
        temp->next=newnode;
    }
    else{
        head[index]=newnode;
    }
}
void build(int a[],int n,struct Node *Head[]){
    int i=0;
    while(n--){
            add(a[i],Head);
        i++; 
    }
}
void Union(struct Node *Set1[],struct Node *Set2[],struct Node *Head[]){
    int size_SET1=size(Set1);
    int size_SET2=size(Set2);
    for(int i=0;i<MAX;i++){
        if(Set1[i]==NULL){
            continue;
        }
        else{
            struct Node *current=Set1[i];
            while(current!=NULL){
                add(current->data,Head);
                current=current->next;
            }
        }
    }
     for(int i=0;i<MAX;i++){
        if(Set2[i]==NULL){
            continue;
        }
        else{
            struct Node *current=Set2[i];
            while(current!=NULL){
                add(current->data,Head);
                current=current->next;
            }
        }
    }
}
void intersection(struct Node* S[],struct Node * T[],struct Node *Head[]){
    for(int i=0;i<MAX;i++){
        if(S[i]==NULL){
            continue;
        }
        else{
            struct Node * current=S[i];
            while(current!=NULL){
                if(is_element_of(current->data,T)){
                    add(current->data,Head);
                }
               current=current->next;
            }     
        }
    }
}

void difference(struct Node *S[],struct Node *T[],struct Node *Head[]){
    for(int i=0;i<MAX;i++){
        if(S[i]==NULL){
            continue;
        }
        else{
            struct Node * current=S[i];
            while(current!=NULL){
                if(!is_element_of(current->data,T)){
                    add(current->data,Head);
                }
                current=current->next;
            }
        }
    }
}
int subset(struct Node *S[],struct Node *T[]){
    for(int i=0;i<MAX;i++){
        if(S[i]==NULL){
            continue;
        }
        else{
            struct Node *current=S[i];
            while(current!=NULL){
               if(!is_element_of(current->data,T)){
                return 0;
                }
                current=current->next;
            }
        }
    }
    return 1;
}
int main(){
int a[10];
srand(time(0));
for(int i=0;i<10;i++){
    a[i]=rand()%100+1;
}
struct set S,P,S_Union_P,S_Intersection_P,P_difference_S;
for(int i=0;i<MAX;i++){
    S.a[i]=NULL;
    P.a[i]=NULL;
    S_Union_P.a[i]=NULL;
    S_Intersection_P.a[i]=NULL;
    P_difference_S.a[i]=NULL;
}
build(a,10,S.a);
printf("S:- ");
print(S.a);
printf("\n");

int b[15]; 
srand(time(NULL));
for(int i=0;i<15;i++){
    b[i]=rand()%100+1;
}
build(b,15,P.a);
printf("P:- ");
print(P.a);
printf("\n");

Union(S.a,P.a,S_Union_P.a);
printf("Union:- ");
print(S_Union_P.a);
printf("\n");

intersection(S.a,P.a,S_Intersection_P.a);
printf("Intersection:- ");
print(S_Intersection_P.a);
printf("\n");

difference(P.a,S.a,P_difference_S.a);
printf("Difference:- ");
print(P_difference_S.a);
printf("\n");

printf("S is subset of P %d",subset(S.a,P.a));
}
