#include<stdio.h>
#define INFINITY 99999;

int merge(int A[ ],int p,int q,int r)
{
    int count=0;
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1],R[n2+1],i,j;
    for(i=1; i<=n1; i++)
        L[i]=A[p+i-1];
    for(j=1; j<=n2; j++)
        R[j]=A[q+j];
    //L[n1+1]=INFINITY;
    //R[n2+1]=INFINITY;
    i=1;
    j=1;
    int k;
    while(i<=(q-1) && j<=r){
        if(L[i]<=R[j]){
            A[k++]=L[i++];
        }
        else{
            A[k++]=R[j++];
            count+=q-i;
        }
        while(i<=q-1)
            A[k++]=L[i++];
        while(j<=r)
            A[k++]=R[j++];
        for(i=p;i<=q;i++)
            L[i]=A[i];
        for(i=q+1;i<=r;i++)
            R[i]=A[i];
    }
    return count;
}

int mergesort(int A[ ],int p,int r){
    int q,count=0;
    if(p<r){
        q=(p+r)/2;
        count+=mergesort(A,p,q);
        count+=mergesort(A,q+1,r);
        count+=merge(A,p,q,r);
    }
    return count;
}

main(){
    int n,t;
    scanf("%d",&n);
    int A[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    t=mergesort(A,1,n);
    for(int i=1;i<=n;i++)
        printf("%d ",A[i]);
    printf("\n");
    printf("%d",t);

}

