#include<stdio.h>
#define INFINITY 99999

void merge(int A[ ],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1],R[n2+1],i,j;
    for(i=1; i<=n1; i++)
        L[i]=A[p+i-1];
    for(j=1; j<=n2; j++)
        R[j]=A[q+j];
    L[n1+1]=INFINITY;
    R[n2+1]=INFINITY;
    i=1;
    j=1;
    int k;
    for(k=p; k<=r; k++)
    {
        if(L[i]<=R[j])
        {
            A[k]=L[i];
            i++;
        }
        else
        {
            A[k]=R[j];
            j++;
        }
    }
}

void mergesort(int A[ ],int p,int r)
{
    int q;
    if(p<r)
    {
        q=(p+r)/2;
        mergesort(A,p,q);
        mergesort(A,q+1,r);
        merge(A,p,q,r);
    }
}


main()
{
    int n,count=1;
    scanf("%d",&n);
    int A[n+1][2];
    for(int i=1; i<=n; i++)
        for(int j=0; j<2; j++)
            scanf("%d",&A[i][j]);
    int temp[n+1];
    for(int i=1; i<=n; i++)
    {
        temp[i]=A[i][1];
    }
    int map[100];
    int result[n+1][2];
    for(int i=1; i<=n; i++)
    {
        map[A[i][1]]=A[i][0];
    }
    mergesort(temp,1,n);
    int z=1;
    for(int i=2; i<=n; i++)
    {
        if(map[temp[i]]>=temp[z])
        {
            count++;
            result[count-1][0]=map[temp[i]];
            result[count-1][1]=temp[i];
            z=i;
        }
    }
    printf("%d\n",count);
    if(count>0)
        printf("%d %d\n",map[temp[1]],temp[1]);
    for(int i=1; i<count; i++)
    {
        for(int j=0; j<2; j++)
        {
            printf("%d  ",result[i][j]);
        }
        printf("\n");
    }
}
