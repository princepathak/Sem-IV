#include<iostream>
#include<ifstream>
#include<string>
using namespace std;
int main(int arg,char* argv[]){
    if(arg<2){
        cout<<"Incorrect no. of parameters\n";
        exit(0);
    }
    ifstream file(argv[1]);
    string str;
    while(getline(file,str)){
        int 
    }
}