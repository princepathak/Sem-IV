#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void matmul(int *A, int *B, int *R, int n)

{

    if (n == 1)

    {
        (*R) += (*A) * (*B);
    }

    else

    {

        matmul(A, B, R, n / 4);

        matmul(A, B + (n / 4), R + (n / 4), n / 4);

        matmul(A + 2 * (n / 4), B, R + 2 * (n / 4), n / 4);

        matmul(A + 2 * (n / 4), B + (n / 4), R + 3 * (n / 4), n / 4);

        matmul(A + (n / 4), B + 2 * (n / 4), R, n / 4);

        matmul(A + (n / 4), B + 3 * (n / 4), R + (n / 4), n / 4);

        matmul(A + 3 * (n / 4), B + 2 * (n / 4), R + 2 * (n / 4), n / 4);

        matmul(A + 3 * (n / 4), B + 3 * (n / 4), R + 3 * (n / 4), n / 4);
    }
}

int main()

{

    int a[100][100], b[100][100], r[100][100], n, i, j, *a1, *b1, *r1;

    printf("Enter order of matrix:");

    scanf("%d", &n);

    for (i = 1; i <= n; i++)

        for (j = 1; j <= n; j++)

            a[i][j] = rand() / 10000;

    a1 = &a[1][1];

    for (i = 1; i <= n; i++)

        for (j = 1; j <= n; j++)

            b[i][j] = rand() / 10000;

    b1 = &b[1][1];

    //for(i=1;i<=n;i++)

    //for(j=1;j<=n;j++)

    //r[i][j]=0;

    r1 = &r[1][1];

    printf("Matrix A:\n");

    for (i = 1; i <= n; i++)

    {

        for (j = 1; j <= n; j++)

        {

            printf("%d\t", a[i][j]);
        }

        printf("\n");
    }

    printf("\nMatrix B:\n");

    for (i = 1; i <= n; i++)

    {

        for (j = 1; j <= n; j++)

        {

            printf("%d\t", b[i][j]);
        }

        printf("\n");
    }

    matmul(a1, b1, r1, n);

    printf("\nResultant:\n");

    for (i = 1; i <= n; i++)

    {

        for (j = 1; j <= n; j++)

        {

            printf("%d\t", r[i][j]);
        }

        printf("\n");
    }

    getch();
}