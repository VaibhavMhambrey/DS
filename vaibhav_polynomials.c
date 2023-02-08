#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct node
{
    int coef,expo;
    struct node*  next;
};

void display_poly(struct node* p)
{
	if(p==NULL)
	{
		printf("0\n");
		return;
	}
	struct node*q=p;
	while(p!=NULL)
	{
		printf("%s%dx^%d ",(p->coef>-1?(p==q?"":"+"):""),p->coef,p->expo);
		p=p->next;
	}
	printf("\n");
}

struct node * push_a_term(struct node * poly,struct node *term)
{
    struct node *temp,*pre;
    if(poly==NULL)
    poly=term;
    else
    {
        temp=pre=poly;
        while(temp!=NULL&&temp->expo>term->expo)
        {
            pre=temp;
            temp=temp->next;

        }
        if(temp!=NULL&&temp->expo==term->expo)
        {
            temp->coef=temp->coef+term->coef;

        }
        else if(temp==poly)
        {
            term->next=poly;
            poly=term;
        }
        else
        {
            pre->next=term;
            term->next=temp;
        }
    }
    return poly;
}

struct node * get_poly(char p[100])
{
	
    struct node *poly=NULL,*temp;
    int i=0,isnegative=0;
    int number;
    temp=(struct node *)malloc(sizeof(struct node ));
    for(i=0,number=0;i<strlen(p);i++)
    {
        if(p[i]=='-')
        	isnegative=1;
        else if(p[i]=='+')
            isnegative=0;
        else if(isdigit(p[i]))
            number = number*10+(p[i]-'0');
        else if(p[i]=='x')
        {
            temp->coef=isnegative?-number:number;
            number=0;
        }
        else if(p[i]=='^')
        {
            temp->expo=0;
            for(i++;isdigit(p[i]);i++)
            temp->expo=temp->expo*10+(p[i]-'0');
            temp->next=NULL;
            poly=push_a_term(poly,temp);
            temp=(struct node *)malloc(sizeof(struct node));
        }
        if(number!=0&&(p[i+1]=='\0'||p[i+1]==' '))
        {
            temp->coef=isnegative?-number:number;
            temp->expo=0;
            temp->next=NULL;
            poly=push_a_term(poly,temp);
            temp=(struct node *)malloc(sizeof(struct node));
            number=0;
        }
    }
    return poly;
}

void modify_poly(struct node *p)
{
	int len,i,n=-1;
	struct node *temp,*pre;
	while(1)
	{
		for(len=0,temp=p;temp!=NULL;temp=temp->next,len++)
			printf("Term %d = %dx^%d\n",len,temp->coef,temp->expo);
		a:printf("Enter the term number you want to modify (0 to exit or %d for new terms) - ",len+1);
		scanf("%d",&n);
		if(n<0||n>len+1)
		{
			printf("Invalid Input.\nRe-");
			goto a;
		}
		if(!n)
		return;
		for(temp=pre=p,i=1;i<n&&i<len;i++,temp=temp->next)
			pre=temp;
		if(n==len+1)
		{
			char str[100];
			printf("Enter new terms:\n");
			b:gets(str);
			if(strlen(str)==0)
			goto b;
			p=get_poly(str);
			display_poly(p);
		}
		else
		{
			printf("Term to modify = %dx^%d\n",temp->coef,temp->expo);
			pre->next=temp->next;
			free(temp);
			temp=(struct node*)malloc(sizeof(struct node));
			temp->next=NULL;
			printf("Enter the new values of :\n");
			printf("Co-efficient :\n");
			scanf("%d",&temp->coef);
			printf("Exponent :\n");
			scanf("%d",&temp->expo);
			p=push_a_term(p,temp);
		}
	}
}

void add_poly(struct node* p1,struct node* p2)
{
	struct node *temp,*result=NULL;
	while(p1!=NULL)
	{
		temp=(struct node*)malloc(sizeof(struct node));
		temp->coef=p1->coef;
		temp->expo=p1->expo;
		temp->next=NULL;
		result=push_a_term(result,temp);
		p1=p1->next;
	}
	while(p2!=NULL)
	{
		temp=(struct node*)malloc(sizeof(struct node));
		temp->coef=p2->coef;
		temp->expo=p2->expo;
		temp->next=NULL;
		result=push_a_term(result,temp);
		p2=p2->next;
	}
	printf("Result:\n");display_poly(result);
}

void mul_poly(struct node* p1,struct node* p2)
{
	struct node*result=NULL,*temp,*t2;
	
	for(;p1!=NULL;p1=p1->next)
	{
		for(t2=p2;t2!=NULL;t2=t2->next)
		{
			temp=(struct node*)malloc(sizeof(struct node));
			temp->coef=p1->coef*t2->coef;
			temp->expo=p1->expo+t2->expo;
			temp->next=NULL;
			result=push_a_term(result,temp);
		}
	}
	printf("Result:\n");
	display_poly(result);
}

int main()
{
	int i=0,j;
	char str[100];
	char poly1[]="2x^5 -3x^1 +8x^3 -9x^2",poly2[]="-5x^4 +26x^1 -7x^3";
	struct node *p1,*p2;
	
	printf("Enter polynomial 1:\n");
	gets(str);
	p1=get_poly(str);
	
	printf("Enter polynomial 2:\n");
	gets(str);
	p2=get_poly(str);
	
	display_poly(p1);
	display_poly(p2);
	
	while(i!=5)
	{
		printf("1 - Modify Polynomial\n");
		printf("2 - Add the two polynomials\n");
		printf("3 - Multiply two polynomials\n");
		printf("4 - Take polynomial from the file\n");
		printf("Enter your choice - ");
		scanf("%d",&i);
		switch(i)
		{
			case 1 :printf("The polynomial that you want to modify is -\n");
					printf("Polynomial 1:\n");
					display_poly(p1);
					printf("Polynomial 2:\n");
					display_poly(p2);
					a:printf("Your choice (1 or 2:\n");
					scanf("%d",&j);
					if(j==1)
					{
						modify_poly(p1);
					}
					else if(j==2)
					{
						modify_poly(p2);
					}
					else
					{
						printf("Invalid Input\nRe-Enter ");
						goto a;
					}
					break;
			case 2 :printf("Polynomial 1:\n");
					display_poly(p1);
					printf("Polynomial 2:\n");
					display_poly(p2);
					add_poly(p1,p2);
					break;
			case 3 :printf("Polynomial 1:\n");
					display_poly(p1);
					printf("Polynomial 2:\n");
					display_poly(p2);
					mul_poly(p1,p2);
					break;
			case 4 :printf("Write your polynomial in the text file named : \"Poly_input.txt\"\n\n");
					printf("Press Enter After you are done writing on the file...\n");
					;
					FILE *f=fopen("Poly_input.txt","r");
					if(f==NULL)
					{
						printf("File was not found\n");
					}
					else
					{
						char z;
						for(j=0,z=1;z!=EOF;j++)
						{
							z=getc(f);
							str[j]=z;
						}
						str[j]='\0';
						p1=get_poly(str);
						printf("Polynomial Fetched from the file = ");
						display_poly(p1);
					}
					break;
			case 5 :printf("Program Ended Succesfully\n");
					break;
					
			default:printf("Invalid Input\n");
				
		}
	}
}
