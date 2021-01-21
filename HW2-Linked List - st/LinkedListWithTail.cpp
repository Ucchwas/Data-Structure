#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
	tail = 0;
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

void printList()
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

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem(int oldItem, int newItem)
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem;
	struct listNode *temp;
	temp=list;
	while(temp->item!=oldItem){
        temp=temp->next;
	}
	newNode->next=temp->next;
	temp->next=newNode;
	return SUCCESS_VALUE;
}
int insertItem(int item) //insert at the beginning of the linked list
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}
//add required codes to delete item, remember to properly set the tail pointer!
int deleteAfter(int item)
{
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	struct listNode *temp,*cur;
	temp=list;
	while(temp->item!=item){
        temp=temp->next;
        cur=temp;
	}
	temp=temp->next;
	newNode=temp;
	cur->next=temp->next;
	if(newNode!=NULL){
        free(newNode);
	}
}

int insertLast(int item)
{
    struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
    struct listNode *temp=list;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
    newNode->next=NULL;
    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1.Insert. 2.Insert new item. 3. Delete item. 4. Search item. \n");
        printf("5. (Add from homework). 6. Print. 7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int old,item;
            scanf("%d %d",&old, &item);
            insertItem(old,item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==6)
        {
            printList();
        }
        else if(ch==7)
        {
            break;
        }
    }

}
