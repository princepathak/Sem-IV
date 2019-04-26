#include <stdio.h>

#define QUEUE_SIZE 20
#define MAX 4

//queue
int queue[QUEUE_SIZE];
int queue_front, queue_end;
void enqueue(int v);
int dequeue();

void bfs(int Adj[][MAX], int n, int source);

int main(void) {
  //Adj matrix
  int a = 4;
  int Adj[4][4];
  for (int i = 0; i < 4; i++)
  {
      for (int j = 0; j < 4; j++)
      {
          scanf("%d", &Adj[i][j]);
      }
  }  
  for (int i = 0; i < 4; i++)
  {
      for (int j = 0; j < 4; j++)
      {
          printf("%d", Adj[i][j]);
      }
      printf("%s", "\n");
  }
//   int Adj[][4] = {
//     {0,1,0,0},
//     {0,1,1,1},
//     {1,0,0,1},
//     {0,0,1,0}
//   };
  
  int n = 4;  //no. of vertex
  int starting_vertex = 2;
  
  bfs(Adj, n, starting_vertex);
  
  return 0;
}

void bfs(int Adj[][MAX], int n, int source) {
  //variables
  int i, j;
  
  //visited array to flag the vertex that
  //were visited
  int visited[MAX];

  //queue
  queue_front = 0;
  queue_end = 0;
  
  //set visited for all vertex to 0 (means unvisited)
  for(i = 0; i < MAX; i++) {
    visited[i] = 0;
  }
  
  //mark the visited source
  visited[source] = 1;
  
  //enqueue visited vertex
  enqueue(source);
  
  //print the vertex as result
  printf("%d ", source);
  
  //continue till queue is not empty
  while(queue_front <= queue_end) {
    //dequeue first element from the queue
    i = dequeue();
    
    for(j = 0; j < n; j++) {
      if(visited[j] == 0 && Adj[i][j] == 1) {
        //mark vertex as visited
        visited[j] = 1;
        
        //push vertex into stack
        enqueue(j);
        
        //print the vertex as result
        printf("%d ", j);
      }
    }
  }
  printf("\n");
}

void enqueue(int v) {
  queue[queue_end] = v;
  queue_end++;
}

int dequeue() {
  int index = queue_front;
  queue_front++;
  return queue[index];
}