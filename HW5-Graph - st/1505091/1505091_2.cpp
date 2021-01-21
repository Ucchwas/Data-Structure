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
    for(i=0;i<length;i++)
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
	int * color;
	int *parent;
	int *dist;
	int *final;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
    int time;
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
	void dfs();//will run dfs in the graph
	void DFS_visit(int u);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	color=0;
	dist=0;
	parent=0;
	final=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	color= new int[nVertices];
	parent=new int[nVertices];
	dist=new int[nVertices];
	final=new int[nVertices];
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
    //if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    if (adjList[u].searchItem(v)!=NULL_VALUE && adjList[v].searchItem(u)!=NULL_VALUE)
    {
        adjList[u].removeItem(v);
        adjList[v].removeItem(u);
        this->nEdges-- ;
    }
    else
    printf("not edge\n");

    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if (adjList[u].searchItem(v)!=NULL_VALUE && adjList[v].searchItem(u)!=NULL_VALUE)
    return true;
    else return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();

    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    int l=adjList[v].getLength();
    for(int i=0;i<l;i++)
    {

        if(adjList[u].searchItem(adjList[v].getItem(i))!=NULL_VALUE)
        return true;

    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
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
        printf("%d ", u);
        for(int i=0;i<adjList[u].getLength();i++)
        {
            if(color[adjList[u].getItem(i)]==WHITE)
            {
            color[adjList[u].getItem(i)]=GREY;
            //printf("( %d ) \n",dist[u] );
            dist[adjList[u].getItem(i)]=dist[u]+1;
            parent[adjList[u].getItem(i)]=u;
            //printf("%d ",adjList[u].getItem(i));
            q.enqueue(adjList[u].getItem(i));
            }
        }
        color[u]=BLACK;
    }
}

void Graph::dfs()
{
    //write this function
    for(int i=0;i<nVertices;i++)
    {
    color[i]=WHITE;
    parent[i]=-1;
    dist[i]=INFINITY;
    final[i]=-1;
    }
    time=0;
    for(int i=0;i<nVertices;i++)
    {
        if(color[i]==WHITE)
        DFS_visit(i);
    }
   /* printf(" \n dist: ");
    for(int i=0;i<nVertices;i++)
    printf("%d ",dist[i]);
    printf(" \n final: ");
    for(int i=0;i<nVertices;i++)
    printf("%d ",final[i]);
    printf(" \n parent: ");
    for(int i=0;i<nVertices;i++)
    printf("%d ",parent[i]);
    printf(" \n color: ");
    for(int i=0;i<nVertices;i++)
    printf("%d ",color[i]);
    */


}
void Graph::DFS_visit(int u)
{
    color[u]=GREY;
    printf("%d ",u);
    time=time+1;
    dist[u]=time;

    for(int v=0;v<adjList[u].getLength();v++)
    {
        if(color[adjList[u].getItem(v)]==WHITE)

        {
            parent[adjList[u].getItem(v)]=u;
            DFS_visit(adjList[u].getItem(v));
        }
    }
    color[u]=BLACK;
    time=time+1;
    final[u]=time;
}


int Graph::getDist(int u, int v)
{
    bfs(u);
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return dist[v]  ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList) delete [] adjList;
    if(parent) delete[] parent;
    if(color) delete[] color;
    if(dist) delete[] dist;
    if(final) delete [] final;
    adjList=0;
    parent=0;
    color=0;
    dist=0;
    final=0;
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
        printf("1. Add edge. 2.get degree 3.is edge\n");
        printf("4. remove edge. 5. Print Graph  6. exit.\n");
        printf("7. common adjacent. 8.bfs 9.shortest distance 10.dfs\n");

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
            int u;
            scanf("%d", &u);
            printf("%d\n",g.getDegree(u));
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u,v)==true)
            printf("is edge\n");
            else printf("isn't edge\n");

        }
        else if(ch==4)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g.removeEdge(u,v);
            g.printGraph();
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
         else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u,v)==true)
            printf("has common adjacent\n");
            else printf("doesnt have\n");
        }
            else if(ch==8)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==9)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int distance=g.getDist(u,v);
            printf("shortest distance is %d \n",distance);
        }
        else if(ch==10)
        {
            g.dfs();
        }

    }

}
