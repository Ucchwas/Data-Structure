#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 99999
#define MAXREAL 99999
class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}

class HeapItem
{
public:
    int data; //actual data that is stored
    int key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
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
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, int key)
    {
        heapLength++;
        A[heapLength].key=key;
        A[heapLength].data=data;
        map[data]=heapLength;
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem i;
        if(heapLength==0)
        {
            printf("Heap is empty");
        }
        else
        {
            i=A[1];
            A[1]=A[heapLength];
            int d=A[1].data;
            //A[0].data=A[heapLength-1].data;
            heapLength--;
            int l=1;
            while(l<=(heapLength/2))
            {
                heapify(l);
                l=map[d];
            }
        }
        return i;
    }


    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, int key)
    {
        int i=map[data];
        if(i<=heapLength && i>0)
        {
            if(key<A[i].key)
            {
                A[i].key=key;
                buHeapify(i);
            }
            if(key>A[i].key)
            {
                A[i].key=key;
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


    //This function returns the key value of a data stored in heap
    int getKey(int data)
    {
        int i = map[data];
        return A[i].key;
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
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {
        while(i>1)
        {
            heapify(i/2);
            i=i/2;
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************

class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *color;
    int *parent;
    int *dist;
    int *first;
    int *last;
    int *clr;
    int *par;
    int time;
    int weight[100][100];
    MinHeap heap;
    int *temp;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);

    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    void dfsvisit(int u);
    void prims();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    color=0;
    parent=0;
    dist=0;
    first=0;
    last=0;
    clr=0;
    par=0;
    time=0;

     //set direction of the graph
    //define other variables to be initialized
}

void Graph::prims()
{
     temp=new int[nVertices+1] ;
    for(int i=1;i<=nVertices;i++)
    {
    temp[i]=1;
    heap.insertItem(i,INFINITY);
    }
    heap.updateKey(0,0);
    parent[0]=0;
    while(!heap.Empty())
    {
        HeapItem h=heap.removeMin();
        temp[h.key]=0 ;
        for(int i=1;i<=adjList[h.data].getLength();i++){
                int idx=adjList[h.data].getItem(i);
                if(temp[idx] &&  weight[h.data][idx]<heap.getKey(idx)){
                parent[idx]=h.data;
                heap.updateKey(idx,weight[h.data][adjList[h.data].getItem(i)]);
            }
        }
    }
    int s=0;
    for(int i=2;i<=nVertices;i++){
        printf("%d %d\n",i,parent[i]);
        s+=weight[i][parent[i]];
    }
    printf("%d",s);
}
void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices+1] ;
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    weight[u][v]=w;
    weight[v][u]=w;
    if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    adjList[u].removeItem(v);
    adjList[v].removeItem(u);
    this->nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;
    if(adjList[u].searchItem(v)!=NULL_VALUE || adjList[v].searchItem(u)!=NULL_VALUE)
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices)
        return 0;
    else
        return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||v<0||u>=nVertices||v>=nVertices)
        return false;
    for(int i=0;i<adjList[u].getLength();i++){
        for(int j=0;j<adjList[v].getLength();j++){
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
                return true;
        }
    }
    return false;
}

void Graph::bfs(int source)
{
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();
        for(int i=0;i<adjList[u].getLength();i++){
            int v=adjList[u].getItem(i);
            if(color[v]==WHITE){
                parent[v]=u;
                dist[v]=dist[u]+1;
                color[v]=GREY;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }
}

void Graph::dfs()
{
    clr=new int[nVertices];
    par=new int[nVertices];
    first=new int[nVertices];
    last=new int[nVertices];
    for(int i=0;i<nVertices;i++){
        clr[i]=WHITE;
        par[i]=-1;
        first[i]=INFINITY;
        last[i]=INFINITY;
    }
    time=0;
    for(int i=0;i<nVertices;i++){
        if(clr[i]==WHITE)
            dfsvisit(i);
    }
}

void Graph::dfsvisit(int u)
{
        if(u>=nVertices)
        return;
        time=time+1;
        first[u]=time;
        clr[u]=GREY;
        for(int i=0;i<adjList[u].getLength();i++){
            if(clr[i]==WHITE){
                par[i]=u;
                dfsvisit(i);
            }
        }
        clr[u]=BLACK;
        time=time+1;
        last[u]=time;
        printf("Order:%d",u);
        printf(" First :%d ",first[u]);
        printf(" Last :%d\n",last[u]);
}

int Graph::getDist(int u, int v)
{
    if(u>=nVertices || v>=nVertices)
        return -1;
    bfs(u);
    return dist[v];
    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList)
        delete[] adjList;
    adjList=0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,m;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    scanf("%d ",&m);
    int u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%d %d %d",&u,&v,&w);
        g.addEdge(u,v,w);
    }
    g.prims();
}
