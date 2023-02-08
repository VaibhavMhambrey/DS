#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define BLANK ' '
#define TAB '\t'
#define MAX 50
int isEmpty();
void push(float symbol);
float pop();
void infix_to_postfix();
float eval_post();
void infix_to_prefix();
float eval_pre();
int instack_priority(char symbol);
int symbol_priority(char symbol);
int instack_priority1(char symbol);
int symbol_priority1(char symbol);
int white_space(char symbol);
char infix[MAX], postfix[MAX],prefix[MAX];;
float stack[MAX];
int top =-1;
main()
{
	int n;
	float value;
	printf("Enter infix:\n");
	gets(infix);
	while(1)
	{
		printf("1. To convert infix to postfix\n");
		printf("2. To convert infix to prefix\n");
		printf("3. To evaluate postfix\n");
		printf("4. To evaluate prefix\n");
		printf("5.EXIT\n");
		printf("Enter your choice");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				infix_to_postfix();	
				printf("Postfix :%s\n",postfix);
				break;
			case 2:
				infix_to_prefix();
				printf("Prefix :%s\n",prefix);
				break;
			case 3:
				value=eval_post();
				printf("Value of postfix expression : %f\n",value);	
				break;
			case 4:
				value=eval_pre();
				printf("Value of prefix expression : %f\n",value);	
				break;
			case 5:
				exit(1);
			default:
				printf("Invalid Choice\n");
		}
	}	
}

int isEmpty()
{
	if(top==-1)
	return 1;
	else
	return 0;
}

void push(float symbol)
{
	if(top==MAX-1)
	{	
		printf("Stack Overflow\n");
		exit(1);
	}
	stack[++top]=symbol;
}
float pop()
{
	if(top==-1)
	{
		printf("Stack Underflow\n");
		exit(1);
	}
	return (stack[top--]);
}

void infix_to_postfix()
{
	int i,p=0;
	char next;
	char symbol;
	for(i=0;i<strlen(infix);i++)
	{
		symbol=infix[i];
		if(!white_space(symbol))
		{
			switch(symbol)
			{
				case '(':
					push(symbol);
					break;
				case ')':
					while((next=pop())!='(')
					postfix[p++] =next;
					break ;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':	
					while((top !=-1) && instack_priority1(stack[top])>= symbol_priority1(symbol))
					postfix[p++]=pop();
					push(symbol) ;
					break ;
				default:
					postfix[p++]=symbol ;
			}
		}
	}
	while(!isEmpty())
	postfix[p++]=pop() ;
	postfix[p ]='\0';
}

int white_space(char symbol)
{
	if(symbol==BLANK||symbol==TAB)
		return 1;
	else
		return 0;
}

int instack_priority1(char symbol)
{
	switch(symbol)
	{
		case '(': 
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;	
	}
}

int symbol_priority1(char symbol)
{
	switch(symbol)
	{
		case '(': 
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 4;
	}
}

float eval_post()
{
	float a,b,temp,result;
	int i;
	for(i=0;i<strlen(postfix);i++)
	{
		if(postfix[i]<='9' && postfix[i]>='0')
		{
			push(postfix[i]-'0');
		}
		else
		{
			a=pop();
			b=pop();
			switch(postfix[i])
			{
				case '+':
					temp=b+a; 
					break;
				case '-':
					temp=b-a; 
					break;
				case '*':
					temp=b*a; 
					break;
				case '/':
					temp=b/a; 
					break;
				case '%':
					temp=(int)b%(int)a; 
					break;
				case '^':
					temp=pow(b,a);
					break;
			}
			push(temp);	
		}
	}
	result=pop();
	return result;
}

void infix_to_prefix()
{
	int i,j,p=0;
	char next;
	char symbol;
	char temp;
	for(i=strlen(infix)-1;i>=0;i--)
	{
		symbol=infix[i];
		if(!white_space(symbol))
		{
			switch(symbol)
			{
				case ')':
					push(symbol);
					break;
				case '(':
					while((next=pop())!=')')
					prefix[p++] =next;
					break ;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':
					while((top !=-1) && instack_priority(stack[top])>symbol_priority(symbol) )
					prefix[p++]=pop();
					push(symbol) ;
					break ;
				default:
					prefix[p++]=symbol ;
			}
		}
	}
	while( top !=-1)
	prefix[p++]=pop() ;
	prefix[p ]='\0';
	for(i=0,j=p-1;i<j;i++,j--)
	{
		temp=prefix[i];prefix[i]=prefix[j];prefix[j]=temp;
	}
}

int instack_priority(char symbol)
{
	switch(symbol)
	{
		case ')': 
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 4;
	}
}

int symbol_priority(char symbol)
{
	switch(symbol)
	{
	case ')': 
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '^':	
		return 3;	
	}
}

float eval_pre()
{
	float a,b,temp,result;
	int i;
	for(i=strlen(prefix)-1;i>=0;i--)
	{
		if(prefix[i]<='9' && prefix[i]>='0')
		push(prefix[i]-48);
		else
		{
			a=pop();
			b=pop();
			switch(prefix[i])
			{
				case '+':
					temp=a+b; 
					break;
				case '-':
					temp=a-b; 
					break;
				case '*':
					temp=a*b; 
					break;
				case '/':
					temp=a/b; 
					break;
				case '%':
					temp=(int)a%(int)b; 
					break;
				case '^':
					temp=pow(a,b);	
					break;
			}
			push(temp);	
		}
	}
	result=pop();
	return result;
}