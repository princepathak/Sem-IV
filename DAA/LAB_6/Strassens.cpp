#include<iostream>
using namespace std;
int N;

int** create(int n){
  int** res = new int*[n];
  for(int i=0;i<n;i++) res[i] = new int[n];
  return res;
}

int** multiply(int** array1,int** array2,int n){
  int** res = create(n);
  int p1 = array1[0][0]*(array2[0][1]-array2[1][1]);
  int p2 = (array1[0][0]+array1[0][1])*array2[1][1];
  int p3 = array2[0][0]*(array1[1][1]+array1[1][0]);
  int p4 = array1[1][1]*(array2[1][0]-array2[0][0]);
  int p5 = (array1[0][0]+array1[1][1])*(array2[0][0]+array2[1][1]);
  int p6 = (array1[0][1]-array1[1][1])*(array2[1][0]+array2[1][1]);
  int p7 = (array1[0][0]-array1[1][0])*(array2[0][0]+array2[0][1]);
  res[0][0] = p5 + p4 - p2 + p6;
  res[0][1] = p1 + p2;
  res[1][0] = p3 + p4;
  res[1][1] = p1 + p5 - p3 - p7;
  return res;
}

int main(){
  N = 2;
  int** array1 = create(N); int** array2 = create(N);
  for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> array1[i][j];
  for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> array2[i][j];
  int** answer = multiply(array1,array2,N);
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++) cout << answer[i][j] << " ";
    cout << endl;
  }
}
