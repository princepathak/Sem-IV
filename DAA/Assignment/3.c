#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _tnode {
   int key;
   struct _tnode *L, *R;
} tnode;
typedef tnode *bintree;

bintree buildtree ( int n )
{
   bintree T;
   int n1, n2;

   if (n <= 0) return NULL;
   T = (bintree)malloc(sizeof(tnode));
   T -> key = 100 + rand() % 900;
   printf("    %d", T -> key);
   if (n == 1) {
      T -> L = T -> R = NULL;
      printf("\n");
   } else {
      n1 = rand() % n; n2 = (n - 1) - n1;
      printf(" %d\n", n1);
      T -> L = buildtree(n1);
      T -> R = buildtree(n2);
   }
   return T;
}

void printtree ( bintree T, int level )
{
   int i;

   printf("    ");
   if (level > 0) {
      for (i=0; i<level-1; ++i) printf("     ");
      printf(" +-- ");
   }
   if (T) {
      printf("%2d\n", T -> key);
      printtree(T->L, level+1);
      printtree(T->R, level+1);
   } else {
      printf("NULL\n");
   }
}

int lefttilt ( bintree T )
{
   int lht, rht, h;
   tnode *p;

   if (T == NULL) return -1;
   lht = lefttilt(T -> L);
   rht = lefttilt(T -> R);
   if (lht < rht) {
      p = T -> L; T -> L = T -> R; T -> R = p;  /* Swap child pointers */
      h = 1 + rht;                              /* Right subtree is taller */
   } else {
      h = 1 + lht;                              /* Left subtree is taller */
   }
   return h;
}

/* We store the unique path from root to the current node in the array S. */
void updatekeys ( bintree T, int h, bintree *S, int level )
{
   int i;

   if (T == NULL) return;

   /* Append current node to the path */
   S[level] = T;

   /* First update the keys of the two subtrees */
   updatekeys(T->L,h,S,level+1);
   updatekeys(T->R,h,S,level+1);

   /* Now calculate the level of the ancestor */
   i = level - ((T -> key) % h);

   /* parent of root is root, so a negative level indicates the root */
   if (i < 0) i = 0;

   /* Copy the key from the ancestor */
   T -> key = S[i] -> key;
}

int main ( int argc, char *argv[] )
{
   int n, h;
   bintree T, *S;

   srand((unsigned int)time(NULL));
   if (argc == 1) scanf("%d", &n); else n = atoi(argv[1]);
   printf("    %d\n", n);

   /* Part 1 */
   T = buildtree(n);

   /* Part 2 */
   printf("\n+++ Initial tree\n");
   printtree(T,0);

   /* Part 3 */
   h = lefttilt(T);
   printf("\n+++ Tree after left-tilting\n");
   printtree(T,0);
   printf("+++ The height of the tree is %d\n", h);

   /* Part 4 */
   /* Maximum number of nodes in a root-to-node path is h+1 */
   S = (bintree *)malloc((h + 1) * sizeof(bintree));
   updatekeys(T,h,S,0);
   printf("\n+++ Tree after key update\n");
   printtree(T,0);

   exit(0);
}
