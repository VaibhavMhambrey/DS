#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
struct node
{
    struct node *lchild;
    int info;
    struct node *rchild;
    int balance;
};
struct node *insert_left_check(struct node *pptr, int *ptaller);
struct node *del_right_check(struct node *pptr, int *pshorter);
struct node *del_left_check(struct node *pptr, int *pshorter);
struct node *insert_LeftBalance(struct node *pptr);
struct node *insert_right_check(struct node *pptr, int *ptaller);
struct node *insert_RightBalance(struct node *pptr);
struct node *del_left_check(struct node *pptr, int *pshorter);
struct node *del_rifht_check(struct node *pptr, int *pshorter);
struct node *del_RightBalance(struct node * pptr, int *pshorter);
struct node *del_LeftBalance(struct node * pptr, int *pshorter);
struct node *RotateRight(struct node *pptr)
{
    struct node *aptr;
    aptr=pptr->lchild;
    pptr->lchild=aptr->rchild;
    aptr->rchild=pptr;
    return aptr;
}
struct node *RotateLeft(struct node *pptr)
{
    struct node *aptr;
    aptr=pptr->rchild;
    pptr->rchild=aptr->lchild;
    aptr->lchild=pptr;
    return aptr;
}
struct node *insert(struct node *pptr, int ikey)
{
    static int taller;
    if (pptr== NULL) 
    {
        pptr=(struct node*)malloc(sizeof(struct node));
        pptr->info =ikey;
        pptr->lchild=NULL;
        pptr->rchild=NULL;
        pptr->balance =0;
        taller= TRUE;
    }
    else if (ikey < pptr->info)
    {
        pptr->lchild=insert(pptr->lchild, ikey);
        if (taller== TRUE)
        pptr=insert_left_check(pptr, &taller);
    }
    else if (ikey > pptr->info) 
    {
        pptr->rchild=insert(pptr->rchild, ikey);
        if (taller== TRUE)
        pptr=insert_right_check(pptr, &taller);
    }
    else 
    {
        printf("Duplicate key\n");
        taller=FALSE;
    }
    return pptr;
}
struct node *insert_left_check(struct node *pptr, int *ptaller)
{
     switch( pptr->balance) {
        case 0:
            pptr->balance =1;
            break;
        case -1:
            pptr->balance=0;
            *ptaller=FALSE;
            break;
        case 1:
            pptr=insert_LeftBalance(pptr);
            *ptaller=FALSE;
        }
        return pptr;
}
struct node *insert_LeftBalance(struct node *pptr)
{
    struct node *aptr , *bptr;
    aptr=pptr->lchild;
    if (aptr->balance==1) {
    pptr->balance =0;
    aptr->balance =0;
    pptr=RotateRight (pptr);
    }
    else {
    bptr=aptr->rchild;
    switch( bptr->balance) {
    case -1:
    pptr->balance =0;
    aptr->balance =1;
    break;
    case 1:
    pptr->balance =-1;
    aptr->balance =0;
    break;
    case 0:
    pptr->balance =0;
    aptr->balance =0;
    }
    bptr->balance =0;
    pptr->lchild = RotateLeft(aptr);
    pptr=RotateRight (pptr);
    }
    return pptr;
}
struct node *insert_right_check(struct node *pptr, int *ptaller)
{
    switch( pptr->balance) {
    case 0:
    pptr->balance =-1;
    break;
    case 1:
    pptr->balance=0;
   *ptaller=FALSE;
    break;
    case -1:
    pptr=insert_RightBalance(pptr);
   *ptaller=FALSE;
    }
    return pptr;
}
struct node *insert_RightBalance(struct node *pptr)
{
    struct node *aptr , *bptr;
    aptr=pptr->rchild;
    if (aptr->balance==-1) {
    pptr->balance =0;
    aptr->balance =0;
    pptr=RotateLeft (pptr);
 }
 else {
   bptr=aptr->lchild;
   switch( bptr->balance) {
   case -1:
   pptr->balance =1;
   aptr->balance =0;
   break;
   case 1:
   pptr->balance =0;
   aptr->balance =-1;
   break;
   case 0:
   pptr->balance =0;
   aptr->balance =0;
   }
   bptr->balance =0;
   pptr->rchild = RotateRight(aptr);
   pptr=RotateLeft(pptr);
}
return pptr;
}
struct node *del(struct node *pptr, int dkey)
{
    static int shorter;
    struct node *tmp,*succ;
    if (pptr== NULL) {
        printf("Duplicate key\n");
        shorter=FALSE;
       return pptr;
    }
    else if (dkey < pptr->info) 
    {
        pptr->lchild=del(pptr->lchild, dkey);
        if (shorter == TRUE)
        pptr=del_left_check(pptr, &shorter);
    }
    else if (dkey > pptr->info) 
    {
        pptr->rchild=del(pptr->rchild, dkey);
        if (shorter == TRUE)
        pptr=del_right_check(pptr, &shorter);
    }
    else 
    {
        if (pptr->lchild != NULL && pptr->rchild != NULL ){
        succ = pptr->rchild ;
        while (succ->lchild !=NULL )
        succ = succ->lchild ;
        pptr->info = succ->info ;
        pptr->rchild = del(pptr->rchild ,succ->info);
        if (shorter == TRUE)
        pptr= del_right_check(pptr , &shorter);
    }
    else {
        tmp=pptr;
        if (pptr->lchild != NULL)
        pptr = pptr->lchild ;
        else if (pptr->rchild != NULL)
            pptr= pptr->rchild ;
            else
            pptr= NULL;
        free(tmp);
        shorter=TRUE;
       }
    }
    return pptr;
}
struct node *del_left_check(struct node *pptr, int *pshorter)
{
    switch( pptr->balance) 
    {
        case 0:
            pptr->balance =-1;
            *pshorter=FALSE;
            break;
        case 1:
            pptr->balance=0;
            break;
        case -1:
            pptr=del_RightBalance(pptr,pshorter);
    }
    return pptr;
}
struct node *del_RightBalance(struct node * pptr, int *pshorter)
{
    struct node *aptr , *bptr;
    aptr=pptr->rchild;
    if (aptr->balance==0) 
    {
        pptr->balance =-1;
        aptr->balance =1;
        *pshorter=FALSE;
        pptr=RotateLeft (pptr);
    }
    else if (aptr->balance==-1) 
    {
        pptr->balance =0;
        aptr->balance =0;
        pptr=RotateLeft (pptr);
   }
   else {
        bptr=aptr->lchild;
        switch( bptr->balance) {
        case 0:
            pptr->balance =0;
            aptr->balance =0;
            break;
        case 1:
            pptr->balance =0;
            aptr->balance =-1;
            break;
        case -1:
            pptr->balance =1;
            aptr->balance =0;
        } 
        bptr->balance =0;
        pptr->rchild = RotateRight(aptr);
        pptr=RotateLeft (pptr);
    }
    return pptr;
}
struct node *del_right_check(struct node *pptr, int *pshorter)
{
    switch( pptr->balance) {
    case 0:
        pptr->balance =1;
        *pshorter=FALSE;
        break;
    case -1:
        pptr->balance=0;
    break;
    case 1:
        pptr=del_LeftBalance(pptr,pshorter);
    }
    return pptr;
}
struct node *del_LeftBalance(struct node * pptr, int *pshorter)
{
    struct node *aptr , *bptr;
    aptr=pptr->lchild;
    if (aptr->balance==0) 
    {
        pptr->balance =1;
        aptr->balance =-1;
        *pshorter=FALSE;
        pptr=RotateRight(pptr);
    }
    else if (aptr->balance==1) 
    {
        pptr->balance =0;
        aptr->balance =0;
        pptr=RotateRight (pptr);
    }
    else {
        bptr=aptr->rchild;
        switch( bptr->balance) {
        case 0:
            pptr->balance =0;
            aptr->balance =0;
            break;
        case 1:
            pptr->balance =-1;
            aptr->balance =0;
            break;
        case -1:
            pptr->balance =0;
            aptr->balance =1;
        }
        bptr->balance =0;
        pptr->lchild = RotateLeft (aptr);
        pptr=RotateRight(pptr);
        }
        return pptr;
}
struct node *search(struct node *ptr,int s)
{
    if(ptr==NULL)
    {
        printf("Not Found \n");
        return NULL;
    }
    else if(s<ptr->info)
    return search(ptr->lchild,s);
    else if(s>ptr->info)
    return search(ptr->rchild,s);
    else
    return ptr;
}
void max(struct node *ptr)
{
    if(ptr->rchild==NULL)
    {
        printf("The Greatest No. is %d\n",ptr->info);
        return;
    }
    else
    return max(ptr->rchild);
}
void min(struct node *ptr)
{
    if(ptr->lchild==NULL)
    {
        printf("The Lowest No. is %d\n",ptr->info);
        return;
    }
    else
    return min(ptr->lchild);
}
void decorder(struct node *ptr)
{
    if(ptr==NULL)
    {
        return;
    }
    decorder(ptr->rchild);
    printf("%d  ",ptr->info);
    decorder(ptr->lchild);
}
int height(struct node *ptr)
{   if(ptr==NULL)
     return 0;
    int lh=height(ptr->lchild);
    int rh=height(ptr->rchild);
    if(lh>rh)
    return 1+lh;
    else 
    return 1+rh;
}
int getwidth(struct node *root,int level)
{
    if(root==NULL)
    return 0;
    if(level==1)
    return 1;
    else if(level>1)
    return getwidth(root->lchild,level-1)+getwidth(root->rchild,level-1);
}
int maxwideth(struct node *root)
{
    int maxw=0,width,h,i;
    h=height(root);
    for(i=1;i<=h;i++)
    {   width=getwidth(root,i);
        if(width>maxw)
            maxw=width;
    }
    return maxw;
}
int main()
{   struct node *root=NULL,*p;
    int ch,key,w;
     while(1)
    {
    printf("1] Insert a new element\n");
	printf("2] Delete a element\n");
    printf("3] Searching for a given element\n");
	printf("4] To Find the element with Max Value\n");
	printf("5] To Find the element with Min value\n");
    printf("6] List elements in tree in decending order\n");
    printf("7] Find width of tree\n");
    printf("8] Exit\n");    
	printf("what do you want to do\n");
	scanf("%d",&ch);
	switch(ch)
    {
        case 1:
        printf("Enter New Node: \n");
        scanf("%d",&key);
        root=insert(root,key);
        break;
        case 2:
        printf("Enter Node to be deleted: \n");
        scanf("%d",&key);
        root=del(root,key);
        printf("Node Delelted\n");
        break;
        case 3:
        printf("Enter the Node to be Search:\n");
        scanf("%d",&key);
        p=search(root,key);
        if(p!=NULL){
           printf("Search is Successful\n");
           printf("Element found at %d \n",p);
        }
        break;
        case 4:
        max(root);        
        break;
        case 5:
        min(root);
        break;
        case 6:
        printf("Nodes in Desencding order:\n");
        decorder(root);
        printf("\n");
        break;
        case 7:
        w=maxwideth(root);
        printf("The max width of Tree = %d\n",w);
        break;
        case 8:
        exit(0);
        break;
        default:
        printf("Wrong choice\n");
    }
    }
}