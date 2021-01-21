#include<stdio.h>
#include<stdlib.h>

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
    char data; //actual data that is stored
    int frequency;
    HeapItem *left,*right; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;


    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];

        heapLength=0;
    }

    ~MinHeap() //destructor
    {

        if(A) delete [] A;

        A = 0; //set to NULL after deletion
    }
    HeapItem newNode(char data,int frequency)
    {
        HeapItem temp;
        temp.data=data;
        temp.frequency=frequency;
        temp.left=NULL;
        temp.right=NULL;
        return temp;
    }

    void Build(char data[],int frequency[])
    {

     for(int i=0;i<heapLength;i++)
     {
        A[i]=newNode(data[i],frequency[i]);
     }
     buHeapify(heapLength-1);
    }
    void buHeapify(int i)
    {
        int value;
        int j=i;
        while(i>1)
        {
            heapify(i/2);
            i=i/2;
        }

        /*while(i!=1)
        {
            if(A[i/2].frequency>A[i].frequency)
            {
                HeapItem t;
                t=A[i];
                A[i]=A[i/2];

                A[i/2]=t;
                i=i/2;
            }
            else
            {
                break;
            }

        }*/

    }

    void insertItem(HeapItem z)
    {
        A[++heapLength]=z;
        buHeapify(heapLength);
    }
    HeapItem * removeMin()
    {
        HeapItem *t=A;
        HeapItem temp;
        if(Empty())
        {

            printf("Empty \n");
            return t;
        }
        if(!Empty())
        {


            A[1]=A[heapLength];
            heapify(1);
            heapLength--;
            return t;
        }
    }
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;
            r=2*i+1;
            smallest=i;

            if(l>heapLength && r>heapLength)
                break;
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].frequency < A[r].frequency )
                smallest = l;
            else
                smallest = r;

            if(A[i].frequency <= A[smallest].frequency)
                break;
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                A[smallest]=t;
                i=smallest;
            }

        }
    }

    void printarr(int arr[],int top)
    {
        for(int i=0;i<=top;i++)
        {
            printf("%d",arr[i]);
        }
        printf("\n");
    }

    void print(HeapItem *root,int arr[],int top)
    {
     if(root->left)
     {
      arr[top]=0 ;
      print(root->left,arr,top+1);
     }
     if(root->right)
     {
      arr[top]=1 ;
      print(root->right,arr,top+1);
     }
     if(!(root->left)&&!(root->right))
     {
         printf("%c :",root->data);
         printarr(arr,top);
     }

    }
    HeapItem *huffman(char data[],int frequency[])
    {
    HeapItem z,l,r;
    Build(data,frequency);
    for(int i=0;i<heapLength-1;i++)
    {
     z.frequency=z.left->frequency+z.right->frequency;
     insertItem(z);
    }

    return removeMin();
    }
    void HuffmanTree(char data[],int freq[])
    {
        HeapItem *root=huffman(data,freq);
        int arr[1000],top=0;
        print(root,arr,top);
    }
    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};


int main()
{
char arr[]={'a','b','c','d'};
int freq[]={20,67,10,19};
MinHeap m;
m.HuffmanTree(arr,freq);
return 0;
}
