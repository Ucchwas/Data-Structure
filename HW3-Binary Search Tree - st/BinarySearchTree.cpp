#include<stdio.h>
#include <bits/stdc++.h>
#include<stdlib.h>
#include<iostream>
#define FALSE_VALUE 0
#define TRUE_VALUE 1
#define RED 0
#define BLACK 1

using namespace std;
int count=0;
struct treeNode
{
    int item;
    int color;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
    struct treeNode *parent;
};

struct treeNode * root;


void initializeTree()
{
    int count;
    count=0;
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    node->parent =0;
    node->color=RED;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, struct treeNode  *newNode)
{
    if(node==0) //insert as the root as the tree is empty
    {
       // struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==newNode->item) return 0; //already an item exists, so return NULL

    if(newNode->item<node->item && node->left==0) //insert as the left child
    {
        //struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        newNode->parent = node;
        return newNode;
    }

    if(newNode->item>node->item && node->right==0) //insert as the right child
    {
        //struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        newNode->parent = node;
        return newNode;
    }

    if(newNode->item<node->item)
        return insertItem(node->left,newNode); //insert at left sub-tree
    else
        return insertItem(node->right, newNode); //insert at right sub-tree
}
void rotateLeft(struct treeNode *root,struct treeNode *pt){
    struct treeNode *pt_right=pt->right;
    pt->right=pt_right->left;
    if(pt->right!=NULL)
        pt->right->parent=pt;
    pt_right->parent=pt->parent;
    if(pt->parent==NULL)
        root=pt_right;
    else if(pt==pt->parent->left)
        pt->parent->left=pt_right;
    else
        pt->parent->right=pt_right;
    pt_right->left=pt;
    pt->parent=pt_right;
}

void rotateRight(struct treeNode *root,struct treeNode *pt){
    struct treeNode *pt_left=pt->left;
    pt->left=pt_left->right;
    if(pt->left!=NULL)
        pt->left->parent=pt;
    pt_left->parent=pt->parent;
    if(pt->parent==NULL)
        root=pt_left;
    else if(pt==pt->parent->left)
        pt->parent->left=pt_left;
    else
        pt->parent->right=pt_left;
    pt_left->right=pt;
    pt->parent=pt_left;
}

void fixViolation(struct treeNode *root,struct treeNode *pt){
    struct treeNode *parent_pt=NULL;
    struct treeNode  *grandparent_pt=NUll;

    while((pt!=root) && (pt->color!=BLACK) && (pt->parent->color)==RED){
        parent_pt=pt->parent;
        grandparent_pt=pt->parent->parent;
        if(parent_pt==grandparent_pt->left){
            struct treeNode *uncle_pt=grandparent_pt->parent;
            if(uncle_pt!=NULL && uncle_pt->color==RED){
                grandparent_pt->color=RED;
                parent_pt->color=BLACK;
                uncle_pt->color=BLACK;
                pt=grandparent_pt;
            }
            else{
                if(pt== parent_pt->right){
                    rotateLeft(root,parent_pt);
                    pt=parent_pt;
                    parent_pt=pt->parent;
                }
                rotateRight(root,grandparent_pt);
                swap(parent_pt->color,grandparent_pt->color);
                pt=parent_pt;
            }
        }
        else{
            struct treeNode *uncle_pt=grandparent_pt->left;

            if((uncle_pt!=NULL) && (uncle_pt->color)==RED){
                grandparent_pt->color=RED;
                parent_pt->color=BLACK;
                uncle_pt->color=BLACK;
                pt=grandparent_pt;
            }
            else{
                if(pt==parent_pt->left){
                        rotateRight(root,parent_pt);
                        pt=parent_pt;
                        parent_pt=pt->parent;
                }
                rotateLeft(root,grandparent_pt);
                swap(parent_pt->color,grandparent_pt->color);
                pt=parent_pt;
            }
        }
    }
    root->color=BLACK;
}

void insert(int data){
    struct treeNode *pt=makeTreeNode(data);
    insertItem(root,pt);
    fixViolation(root,pt);
}

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==NULL)
        return 0;
    else
        return (1+getSize(node->left)+getSize(node->right));
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    int count=0;
    struct treeNode *temp;
    temp=root;
    if(temp->item==NULL)
        return 0;
    while(temp!=NULL){
        if(node->item<temp->item){
            count++;
            temp=temp->left;
        }
        else if(node->item>temp->item){
            count++;
            temp=temp->right;
        }
        if(temp->item==node->item)
            return count;
    }
    return count;
}


int calcDepth(int item)//return depth of an item in the tree
{
    int count=0;
    struct treeNode *temp;
    temp=root;
    if(temp->item==NULL)
        return 0;
    while(temp!=NULL){
        if(item<temp->item){
            count++;
            temp=temp->left;
        }
       else if(item>temp->item){
            count++;
            temp=temp->right;
        }
        if(temp->item==item)
            return count;
    }
    return count;
}


/*int deleteItem(struct treeNode * node, int item)
{
    if(node==NULL)
        return false;
    if(item<node->item)
        node->left=deleteItem(node->left,item);
    else if(item>node->item)
        node->right=deleteItem(node->right,item);
    else{
        if(node->left==NULL){
            struct treeNode *temp;
            temp=node->right;
            free(node);
            return true;
        }
        else if(node->right==NULL){
            struct treeNode *temp;
            temp=node->left;
            free(node);
            return true;
        }

        struct treeNode *temp;
        temp=minValueNode(node->right);
        node->item=temp->item;
        node->right=deleteItem(node->right,temp->item);
    }
    return true;
}
*/
/*int minValueNode(struct treeNode *node)
{
        struct treeNode *current;
        current=node;

        while(current->left!=NULL){
            current=current->left;
        }
        return current;
}
*/
int getMinItem() //returns the minimum item in the tree
{
        struct treeNode *current;
        current=root;

        while(current->left!=NULL){
            current=current->left;
        }
        return (current->item);
}

int getMaxItem() //returns the maximum item in the tree
{
     struct treeNode *current;
        current=root;

        while(current->right!=NULL){
            current=current->right;
        }
        return (current->item);
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{

    if(node->item>=leftBound && node->item<=rightBound)
        count++;

    if(node->left!=0 && node->item>leftBound)
        rangeSearch(node->left,leftBound,rightBound);
    else if(node->right!=0 && node->item<rightBound)
        rangeSearch(node->right,leftBound,rightBound);

    return count;
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d (%d)\n",node->item,node->color);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7.Get Size 8.Min Item 9.Max Item 10. Depth of Node 11.Depth of Item 12.Range Search 13.exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insert( item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
//            root=deleteItem(root, item);
//            printInOrder(root);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7){
            int t=getSize(root);
            printf("%d\n",t);
        }
        else if(ch==8)
        {
            int t;
            t=getMinItem();
            printf("%d\n",t);
        }
        else if(ch==9)
        {
            int t;
            t=getMaxItem();
            printf("%d\n",t);
        }
        else if(ch==10)
        {
            int item,t;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            t=calcNodeDepth(res);
            printf("%d\n",t);
        }
        else if(ch==11)
        {
            int item,t;
            scanf("%d",&item);
            t=calcDepth(item);
            printf("%d\n",t);
        }
        else if(ch==12)
        {
            count=0;
            int lb,rb,t;
            scanf("%d %d",&lb,&rb);
            t=rangeSearch(root,lb,rb);
            printf("%d\n",t);
        }
        else if(ch==13)
        {
            break;
        }
    }

}
