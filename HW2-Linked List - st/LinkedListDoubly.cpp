#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
    struct listNode *last;
	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
}


int deleteAfter(int item)
{
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	struct listNode *temp,*cur,*last;
	temp=list;
	if(temp->item!=item){
        temp=temp->next;
        cur=temp;
	}
	temp=temp->next;
	newNode=temp;
	last=temp->next;
	cur->next=last;
	last->prev=cur;
	free(newNode);
	return SUCCESS_VALUE;
}
int deleteLast()
{
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	struct listNode *temp,*last;
	temp=tail;
	if(temp->prev!=NULL){
        last=temp;
	}
    temp=temp->prev;
    temp->next=NULL;
    free(last);
    return NULL_VALUE;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printListForward()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListBackward()
{
	struct listNode *temp;
	temp=list;
	while(temp->next!=NULL)
        temp=temp->next;
    while(temp!=list){
        printf("%d->",temp->item);
        temp=temp->prev;
    }
    printf("%d->\n",temp->item);
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2.Delete Last 3. Delete After. 4. Search item. \n");
        printf("5. Print forward. 6. Print backward. 7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2){
            deleteLast();
        }
        else if(ch==3)
        {
            int it;
            scanf("%d",&it);
            deleteAfter(it);
            //if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==5)
        {
            printListForward();
        }
        else if(ch==6)
        {
            printListBackward();
        }
        else if(ch==7)
        {
            break;
        }
    }

}
