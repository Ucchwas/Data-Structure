#include<stdio.h>
#include<iostream>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#define INFINITY 99999
using namespace std;

class HeapItem
{
public:
    char data; //actual data that is stored
    float key;
    HeapItem *right;
    HeapItem *left;
    //key value of the data, heap is constructed based on key
};


//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem **A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;
    //struct HeapItem  *heapitem;
    MinHeap() //constructor
    {
        A = new HeapItem*[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int a[], char freq[],int n)
    {
        //heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the hea
        {
            A[i+1]=new HeapItem();
        }
    }
    void insertItemFirst(HeapItem* heapitem)
    {
        heapLength=heapLength+1;
        A[heapLength]->data=heapitem->data;
        A[heapLength]->key=heapitem->key;
        A[heapLength]->right=heapitem->right;
        A[heapLength]->left=heapitem->left;
        buHeapify(heapLength);
    }
    void insertItem(HeapItem *a,HeapItem *b)
    {
        //Write your codes here
        heapLength=heapLength+1;
        A[heapLength]=new HeapItem();
        A[heapLength]->key=a->key+b->key;
        A[heapLength]->right=b;
        A[heapLength]->left=a;
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem* removeMin()
    {
        //write your codes here
        HeapItem* t=A[1];
        if(heapLength>1)
        {
            t=A[1];
            A[1]=A[heapLength];
            A[heapLength]=t;
            heapLength--;
            heapify(1);
            return t;
        }
        else
        {
            heapLength=0;
            return t;
        }

    }
    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i]->key;
    }

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l]->key < A[r]->key )
                smallest = l;
            else
                smallest = r;

            if(A[i]->key <= A[smallest]->key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem *t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i]->data]=i;
                A[smallest]=t;
                map[A[smallest]->data]=smallest;
                i=smallest;
            }

        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int f)
    {
        if(f==0)
            return;

        int i=f/2;
        int l,r,smallest;
        l=2*i;
        r=2*i+1;
        if(l>heapLength && r>heapLength)
            return; //nothing to do, we are at bottom
        else if(r>heapLength)
            smallest = l;
        else if(l>heapLength)
            smallest = r;
        else if( A[l]->key < A[r]->key )
            smallest = l;
        else
            smallest = r;

        if(A[i]->key <= A[smallest]->key)
            return;
        else
        {
            //swap nodes with smallest child, adjust map array accordingly
            HeapItem *t;
            t=A[i];
            A[i]=A[smallest];
            map[A[i]->data]=i;
            A[smallest]=t;
            map[A[smallest]->data]=smallest;
            i=smallest;
        }
        buHeapify(f/2);
    }
    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, float key)
    {
        //Write your codes here.
        int i=map[data];
        if(i<=heapLength && i>0)
        {
            if(key<A[i]->key)
            {
                A[i]->key=key;
                buHeapify(i);
            }
            if(key>A[i]->key)
            {
                A[i]->key=key;
                int parent=i;
                int l,r;
                while(parent<=heapLength)
                {
                    heapify(parent);
                    l=2*parent;
                    r=2*parent+1;
                    if(l<r)
                        parent=l;
                    else
                        parent=r;
                }
            }
        }
        else
            return;
    }
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%f) ", A[i]->data, A[i]->key);
        }
        printf("\n");
    }


    HeapItem* BuildHuffmanTree(int a[],char data[],int n)
    {
        for(int i=0; i<n; i++)
        {
            HeapItem *heap=new HeapItem();
            heap->data=data[i];
            heap->key=a[i];
            heap->right=0;
            heap->left=0;
            insertItemFirst(heap);
        }
        while(heapLength!=1)
        {
            HeapItem* a=removeMin();
            HeapItem* b=removeMin();
            insertItem(a,b);
        }
        return removeMin();
    }
    void printH(int  arr[],int top)
    {
        for(int i=0; i<top; i++)
        {
            cout<<arr[i];
        }
        cout<<endl;
    }

    void printHp(HeapItem *root,int arr[],int top)
    {
        if (root->left!=0)
        {
            arr[top] = 0;
            printHp(root->left, arr, top + 1);
        }
        if (root->right!=0)
        {
            arr[top] = 1;
            printHp(root->right, arr, top + 1);
        }

        if (root->right==0&&root->left==0)
        {
            printf("%c    ",root->data);
            printH(arr, top);
        }
    }

    void Huffman(int a[],char data[],int n)
    {
        initialize(a,data,n);
        HeapItem* item=BuildHuffmanTree(a,data,n);
        int arr[30], top = 0;
        printHp(item,arr,top);

    }
};
int main()
{
    int data;
    float key;
    MinHeap heap;
    int num[INFINITY];
    char name[INFINITY];
    int  n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>name[i]>>num[i];
    heap.Huffman(num,name,n);
}
