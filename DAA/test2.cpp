#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n;
    cout<<"Enter the value of n\n";
    cin>>n;
    char *temp,*orig;
    temp=new char[n];
    //orig=new char[n];
    //int count=0;
    for(int i=0;i<n;i++){
        cin>>temp[i];
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            //orig[count]=temp[i];
            cout<<temp[i];
            break;
        }
        if(temp[i]!=temp[i+1]){
            //orig[count]=temp[i];
            //count++;
            cout<<temp[i];
        }
    }
    return 0;
}