#include<iostream>
#include<cstring>
#include<cstdlib>
#define digit 9
using namespace std;
void tokenize(string temp,int A[]){
    int count=1,index=0;
    int lenA;
    lenA=temp.length();
    char temp1[9];
    for(int i=0;i<lenA;i++){
        if(i%9==0 && i!=0){
            A[count]=atoi(temp1);
            count++;
            index=0;
            temp1[index]=temp[i];
            index++;
        }
        else{
            temp1[index]=temp[i];
            index++;
        }
    }
}
void sum_(string a,string b,string c){
    int sum,quo=0,a1,b1;
    char temp[1];
    char temp1[15];
    for(int i=0;i<a.length()<b.length()?a.length():b.length();i++){
        temp[0]=a[i];
        a1=atoi(temp);
        temp[0]=b[i];
        b1=atoi(temp);
        sum=(a1+b1+quo)%10;
        quo=(a1+b1+quo)/10;
        itoa(sum,temp,10);
        temp1[i]=temp[0];
    }
    cout<<temp1;
}

int main(){
    string a,b,c;
    cout<<"Enter the number to be added \n";
    getline(cin,a);
    getline(cin,b);
    int lenA,lenB;
    lenA=a.length();
    lenB=a.length();
    int lenC=lenA>lenB?lenA:lenB;
    int *A,*B,*C;
    A=new int[lenA/digit];
    B=new int[lenB/digit];
    C=new int[lenC/digit];
    tokenize(a,A);
    tokenize(b,B);
}