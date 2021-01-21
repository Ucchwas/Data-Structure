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

void initializeList()
{
    list = 0;  //initially set to NULL
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


int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
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

int insertLast(int item)
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    struct listNode *previous=list;
    while(previous->next!=NULL)
        previous=previous->next;
    previous->next=newNode;
    newNode->next=NULL;
    return SUCCESS_VALUE;
}

int insertBefore(int olditem, int newitem)
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newitem ;
    struct listNode *temp,*previous;
    previous=list;
    if(list->item==olditem)
    {
        newNode->next=NULL;
        newNode->next=list;
        list=newNode;
        return SUCCESS_VALUE;
    }
    else
    {
        while(previous->item!=olditem)
        {
            temp=previous;
            previous=previous->next;
        }
        temp->next=newNode;
        newNode->next=previous;
        return SUCCESS_VALUE;
    }
}

int deleteAfter(int item)
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    struct listNode *temp,*cur;
    temp=list;
    if(temp->item!=item)
    {
        temp=temp->next;
        cur=temp;
    }
    temp=temp->next;
    newNode=temp;
    cur->next=temp->next;
    free(newNode);
    return SUCCESS_VALUE;
}

int deleteLast()
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    struct listNode *temp,*cur;
    temp=list;
    if(list==NULL)
        return NULL_VALUE;
    while(temp->next!=NULL)
    {
        cur=temp;
        temp=temp->next;
    }
    if(cur!=NULL)
        cur->next=NULL;
    free(temp);
    return SUCCESS_VALUE;
}



int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert last. 5. Print. 6.Insert before. 7.Delete after 8.Delete Last 9.Break.\n");

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
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            int old,item;
            scanf("%d %d",&old, &item);
            insertBefore(old,item);
        }
        else if(ch==7)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==8)
        {
            deleteLast();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
