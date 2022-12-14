#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
struct treenode
{
  struct treenode *lchild;
  int ch;
  struct treenode *rchild;
};
struct listnode
{
  int ch;
  struct listorder *link;
};
struct listnode *insatbeg(struct listnode *ptr,int data)
 {
    struct listnode *temp;
    temp=(struct listnode*)malloc(sizeof(struct listnode));
    temp->ch=data;
    temp->link=NULL;
    ptr=temp;
    return ptr;
 }
 struct listnode *insatend(struct listnode *ptr,int data)
 {
    struct listnode *temp,*p;
    p=ptr;
    temp=(struct listnode*)malloc(sizeof(struct listnode));
    temp->ch=data;
    while(p->link!=NULL)
    {
        p=p->link;
    }
    p->link=temp;
    temp->link=NULL;
    return ptr;
 }
struct listnode *create(struct listnode *ptr,int n)
{   int i,d;
    if(n==0)
    {
        printf("List is Empty\n");
        return ptr;
    }
    printf("Enter Element:\n");
    scanf("%d",&d);
    ptr=insatbeg(ptr,d);
    for(i=2;i<=n;i++)
    {
        scanf("%d",&d);
        ptr=insatend(ptr,d);
    }
    return ptr;
}
struct treenode *construct(struct listnode *inorder,struct listnode *postorder,int n)
{ int i,j;
  struct treenode *temp;
  struct listnode *q,*p;
  if(n==0)
    return NULL;
  p=postorder;
  for(i=1;i<n;i++)
      p=p->link;
  temp=(struct treenode*)malloc(sizeof(struct treenode));
  temp->ch=p->ch;
  temp->lchild=NULL;
  temp->rchild=NULL;
  if(n==1)
     return temp;
  q=inorder;
  for(i=0;q->ch!=p->ch;i++)
          q=q->link;
  temp->lchild=construct(inorder,postorder,i);
  for(j=1;j<=i;j++)
       postorder=postorder->link;
  temp->rchild=construct(q->link,postorder,n-i-1);
  return temp;
}
int height( struct treenode *ptr)
{ int lh,rh;
  if(ptr==NULL)
    return 0;
  lh=height(ptr->lchild);
  rh=height(ptr->rchild);
  if(lh>rh)
  return 1+lh;
  else
  return 1+rh;
}
void displaylevel(struct treenode *ptr, int level,int ltr)
  {
  if (ptr == NULL)
  return;
  if (level == 1)
  {
  printf("%d ", ptr->ch);
  }
  else if (level > 1)
  {
    if (ltr){
    displaylevel(ptr->lchild, level-1,ltr);
    displaylevel(ptr->rchild, level-1,ltr);
    }
    else
    {
      displaylevel(ptr->rchild, level-1,ltr);
    displaylevel(ptr->lchild, level-1,ltr);
    }
  }
  return;
}
void leveltrav(struct treenode *ptr)
{
  int h = height(ptr);
  int i;
  bool ltr = true;
  for (i=1; i<=h; i++)
     displaylevel(ptr, i,ltr);
  printf("\n");
}
void printSpiral(struct node* root)
{
    int h = height(root);
    int i;
    bool ltr = false;
    for (i = 1; i <= h; i++) {
        displaylevel(root, i, ltr);
        ltr = !ltr;
    }
}
int depth( struct treenode *ptr,int info)
{ int lh,rh;
  if(ptr->ch==info)
    return 0;
  lh=height(ptr->lchild);
  rh=height(ptr->rchild);
  if(lh>rh)
  return lh;
  else
  return rh;
}
int main()
{ int n,c,h,d;
  struct treenode *root=NULL;
  struct listnode *inorder=NULL,*postorder=NULL;
  printf("Enter the No. of Elements in tree\n");
  scanf("%d",&n);
  printf("Enter Inorder List\n");
  inorder=create(inorder,n);
  printf("Enter Postorder List\n");
  postorder=create(postorder,n);
  root=construct(inorder,postorder,n);
  while(1)
   {
     printf("1 Display height of the tree\n");
     printf("2 Return the depth of a given node in the tree\n");
     printf("3 Perform level order traversal \n");
     printf("4 Perform Spiral order traversal\n");
     printf("5 Exit\n");
     printf("Enter Number:\n");
     scanf("%d",&c);
     switch(c)
     {
     case 1:
     h=height(root);
     printf("The Height of Tree is %d\n\n",h);
     break;
     case 2:
     printf("Enter The Node \n");
     scanf("%d",&d);
     h=depth(root,d);
     printf("The depth node of Tree is %d\n\n",h);
     break;
     case 3:
     leveltrav(root);
     break;
     case 4:
     printSpiral(root);
     printf("\n");
     break;
     case 5:
     exit(0);
     default:
     printf("Wrong Choice\n");
     }
   }
}