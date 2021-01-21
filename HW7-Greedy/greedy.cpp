#include<stdio.h>
#define INFINITY 99999;

using namespace std;

struct Greedy{
    int start;
    int finish;
};

void merge(Greedy A[ ],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    Greedy L[n1+1],R[n2+1];
    int i,j;
    for(i=1; i<=n1; i++)
        L[i]=A[p+i-1];
    for(j=1; j<=n2; j++)
        R[j]=A[q+j];
//    L[n1+1]=INFINITY;
 //   R[n2+1]=INFINITY;
    i=1;
    j=1;
    int k;
    for(k=p; k<=r; k++)
    {
        if(L[i].finish<=R[j].finish)
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

void mergesort(Greedy A[ ],int p,int r){
    int q;
    if(p<r){
        q=(p+r)/2;
        mergesort(A,p,q);
        mergesort(A,q+1,r);
        merge(A,p,q,r);
    }
}

main(){
    int n,count=1;
    scanf("%d",&n);
    Greedy A[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d %d",&A[i].start,&A[i].finish);
    mergesort(A,1,n);
    int z=1;
    for(int i=2;i<=n;i++){
        if(A[i].start>=A[z].finish){
            count++;
            z=i;
        }
    }
    printf("%d\n",count);
    printf("%d %d\n",A[1].start,A[1].finish);
    z=1;
    for(int i=2;i<=n;i++){
        if(A[i].start>=A[z].finish){
            printf("%d %d\n",A[i].start,A[i].finish);
            z=i;
        }
    }
}
