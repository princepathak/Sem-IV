#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int *Q1; /* The min-heap of indices */
   int *Q2; /* The max-heap of indices */
   int *I1; /* Indices in min-heap */
   int *I2; /* Indices in max-heap */
} MMQ;

int *genarray ( int n )
{
   int *A, i;

   A = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) {
      if (i % 19 == 0) printf("    ");
      A[i] = rand() % 1000;
      printf("%3d ", A[i]);
      if (i % 19 == 18) printf("\n");
   }
   if (i % 19) printf("\n");

   return A;
}

void printarray ( int A[], int n )
{
   int i;

   printf("\n+++ Array after sorting\n");
   for (i=0; i<n; ++i) {
      if (i % 19 == 0) printf("    ");
      printf("%3d ", A[i]);
      if (i % 19 == 18) printf("\n");
   }
   if (i % 19) printf("\n");
}

MMQ initmmq ( int s )
{
   MMQ Q;
   int i;

   Q.Q1 = (int *)malloc(s * sizeof(int));
   Q.Q2 = (int *)malloc(s * sizeof(int));
   Q.I1 = (int *)malloc(s * sizeof(int));
   Q.I2 = (int *)malloc(s * sizeof(int));
   for (i=0; i<s; ++i) Q.Q1[i] = Q.Q2[i] = Q.I1[i] = Q.I2[i] = i;
   return Q;
}

void minheapify ( int A[], int Q1[], int I1[], int s, int i )
{
   int l, r, m, t;

   while (1) {
      l = 2*i + 1; r = 2*i + 2;
      if (l >= s) return;
      m = ((r == s) || (A[Q1[l]] <= A[Q1[r]])) ? l : r;
      if (A[Q1[m]] > A[Q1[i]]) return;
      t = Q1[i]; Q1[i] = Q1[m]; Q1[m] = t;
      I1[Q1[i]] = i; I1[Q1[m]] = m;
      i = m;
   }
}

void maxheapify ( int A[], int Q2[], int I2[], int s, int i )
{
   int l, r, m, t;

   while (1) {
      l = 2*i + 1; r = 2*i + 2;
      if (l >= s) return;
      m = ((r == s) || (A[Q2[l]] >= A[Q2[r]])) ? l : r;
      if (A[Q2[m]] < A[Q2[i]]) return;
      t = Q2[i]; Q2[i] = Q2[m]; Q2[m] = t;
      I2[Q2[i]] = i; I2[Q2[m]] = m;
      i = m;
   }
}

void makeminheap ( int A[], int Q1[], int I1[], int s )
{
   int i;

   for (i=s/2-1; i>=0; --i) minheapify(A,Q1,I1,s,i);
}

void makemaxheap ( int A[], int Q2[], int I2[], int s )
{
   int i;

   for (i=s/2-1; i>=0; --i) maxheapify(A,Q2,I2,s,i);
}

void makeheap ( int A[], MMQ Q, int s )
{
   makeminheap(A,Q.Q1,Q.I1,s);
   makemaxheap(A,Q.Q2,Q.I2,s);
}

void minreplace ( int A[], MMQ Q, int s, int i )
{
   int p, t;

   minheapify(A,Q.Q1,Q.I1,s,0);
   while (1) {
      if (i == 0) return;
      p = (i - 1) / 2;
      if (A[Q.Q2[p]] > A[Q.Q2[i]]) return;
      t = Q.Q2[i]; Q.Q2[i] = Q.Q2[p]; Q.Q2[p] = t;
      Q.I2[Q.Q2[i]] = i; Q.I2[Q.Q2[p]] = p;
      i = p;
   }
}

void maxreplace ( int A[], MMQ Q, int s, int i )
{
   int p, t;

   maxheapify(A,Q.Q2,Q.I2,s,0);
   while (1) {
      if (i == 0) return;
      p = (i - 1) / 2;
      if (A[Q.Q1[p]] < A[Q.Q1[i]]) return;
      t = Q.Q1[i]; Q.Q1[i] = Q.Q1[p]; Q.Q1[p] = t;
      Q.I1[Q.Q1[i]] = i; Q.I1[Q.Q1[p]] = p;
      i = p;
   }
}

int getmin ( MMQ Q )
{
   return Q.Q1[0];
}

int getmax ( MMQ Q )
{
   return Q.Q2[0];
}

void printheap ( int A[], MMQ Q, int s )
{
   int i;

   printf("+++ Heap on %d elements\n", s);
   printf("i  :"); for (i=0; i<s; ++i) printf(" %3d", i); printf("\n");
   printf("A  :"); for (i=0; i<s; ++i) printf(" %3d", A[i]); printf("\n");
   printf("Q1 :"); for (i=0; i<s; ++i) printf(" %3d", Q.Q1[i]); printf("\n");
   printf("AQ1:"); for (i=0; i<s; ++i) printf(" %3d", A[Q.Q1[i]]); printf("\n");
   printf("I1 :"); for (i=0; i<s; ++i) printf(" %3d", Q.I1[i]); printf("\n");
   printf("Q2 :"); for (i=0; i<s; ++i) printf(" %3d", Q.Q2[i]); printf("\n");
   printf("AQ2:"); for (i=0; i<s; ++i) printf(" %3d", A[Q.Q2[i]]); printf("\n");
   printf("I2 :"); for (i=0; i<s; ++i) printf(" %3d", Q.I2[i]); printf("\n");
}

void cqsort ( int M[], int n, int s )
{
   MMQ Q;
   int *A, *L, *R, lsize, rsize, i, idx1, idx2, minval, maxval, which, S;

   if (n <= 1) return;

   if (n < s) s = n;

   A = (int *)malloc(s * sizeof(int));
   L = (int *)malloc(n * sizeof(int));
   R = (int *)malloc(n * sizeof(int));
   Q = initmmq(s);
   for (i=0; i<s; ++i) A[i] = M[i];
   makeheap(A,Q,s);
   printheap(A,Q,s);
   lsize = rsize = which = 0;
   for (i=s; i<n; ++i) {
      minval = A[getmin(Q)];
      maxval = A[getmax(Q)];
      if (M[i] <= minval) {
         L[lsize++] = M[i];
      } else if (M[i] >= maxval) {
         R[rsize++] = M[i];
      } else {
         if (which == 0) {
            idx1 = getmin(Q);
            idx2 = Q.I2[idx1];
            L[lsize++] = A[idx1];
            A[idx1] = M[i];
            minreplace(A,Q,s,idx2);
         } else {
            idx2 = getmax(Q);
            idx1 = Q.I1[idx2];
            R[rsize++] = A[idx2];
            A[idx2] = M[i];
            maxreplace(A,Q,s,idx1);
         }
         which = 1 - which;
      }
   }

   S = s;
   while (S > 0) {
      idx2 = getmax(Q);
      --S;
      M[lsize+S] = A[idx2];
      Q.Q2[0] = Q.Q2[S];
      if (S) maxheapify(A,Q.Q2,Q.I2,S,0);
   }
   free(Q.Q1); free(Q.Q2); free(Q.I1); free(Q.I2);

   for (i=0; i<lsize; ++i) M[i] = L[i];
   for (i=0; i<rsize; ++i) M[lsize+s+i] = R[i];

   free(A); free(L); free(R);

   cqsort(M,lsize,s);
   cqsort(M+lsize+s,rsize,s);
}

int main ( int argc, char *argv[] )
{
   int n, s, *HD;

   srand((unsigned int)time(NULL));
   if (argc == 1) scanf("%d", &n); else n = atoi(argv[1]);
   if (argc == 2) scanf("%d", &s); else s = atoi(argv[2]);
   printf("    %d %d\n", n, s);
   HD = genarray(n);
   cqsort(HD,n,s);
   printarray(HD,n);

   free(HD);
   exit(0);
}