#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    void dfsvisit(int u);
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

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
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
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.Remove Edge 3.Is Edge 4.Get Degree 5.Has Common Adjacent 6.Get Distance \n");
        printf("7.DFS 8. Print Graph  9. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            bool t;
            int u, v;
            scanf("%d%d", &u, &v);
            t=g.isEdge(u,v);
            if(t==true)
                printf("True\n");
            else
                printf("False\n");
        }
        else if(ch==4)
        {
            int u,t;
            scanf("%d",&u);
            t=g.getDegree(u);
            printf("%d\n",t);
        }
        else if(ch==5)
        {
            bool t;
            int u, v;
            scanf("%d%d", &u, &v);
            t=g.hasCommonAdjacent(u,v);
            if(t==true)
                printf("True\n");
            else
                printf("False\n");
        }
        else if(ch==6)
        {
            int u,v,t;
            scanf("%d %d",&u,&v);
            t=g.getDist(u,v);
            printf("%d\n",t);
        }
        if(ch==7)
        {
            g.dfs();
        }
        else if(ch==8)
        {
            g.printGraph();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
