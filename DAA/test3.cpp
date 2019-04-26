#include<iostream>
#include<cstring>
using namespace std;
bool isPalindrome(string a){
    int len=a.length();
    for(int i=0;i<len/2;i++){
        if(a[i]!=a[len-i]){
            return false;
        }
    }
    return true;
}
string createString(char temp[],int i,int j){
    string a;
    for(int k=i;k<=j;k++){
        a[i]=temp[k];
    }
    return a;
}
int findLargest(string temp[],int index1,int index2){
    int min=10000000;
    int index;
    for(int i=index1;i<=index2;i++){
        if(temp[i].length()<min){
            index=i;
            min=temp[i].length();
        }
    }
    return index;
}
int main(){
    int n;
    cout<<"Enter the value of n\n";
    cin>>n;
    char *temp,*orig;
    temp=new char[n];
    //orig=new char[n];
    //int count=0;
    string *ans;
    ans = new string[n*n];
    for(int i=0;i<n;i++){
        cin>>temp[i];
    }
    int *count_index;
    count_index=new int[n*n];
    int count=0;
    for(int i = 0;i<n;i++){
        for(int j=i;j<n;j++){
            string dummy=createString(temp,i,j);
            bool res=isPalindrome(dummy);
            if(res==true){
                ans[count]=dummy;
                count++;
            }
        }
        count_index[i]=count-1;
    }
    int l=0,finalcount=0;

    for(int i=0;i<count;i++){
        int index=findLargest(ans,l,count_index[l]);
        l=l+index;
        finalcount++;
    }
    cout<<finalcount;
    return 0;
}