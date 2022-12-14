#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int bin(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n % 2 + 10 * bin(n / 2);
}

int oct(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n % 8 + 10 * oct(n / 8);
}

void hex(int n)
{
    int remainder = n % 16;
    if (n == 0)
        return;
    if (remainder < 10)
    {
        hex(n / 16);
        printf("%d", remainder);
        return;
    }
    else
    {
        hex(n / 16);
        printf("%c", remainder + 55);
        return;
    }
}

void hanoi(int n, int t1, int t2, int t3)
{
    if (n == 1)
    {
        printf("Shifting the top disk from tower %d to tower %d\n", t1, t2);
        return;
    }
    hanoi(n - 1, t1, t3, t2);
    printf("Shifting the top disk from tower %d to tower %d\n", t1, t2);
    hanoi(n - 1, t3, t2, t1);
}

int GCD(int a, int b)
{
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

void strreversal(char *str)
{
    if (*str == '\0')
        return;
    strreversal(str + 1);
    printf("%c", *str);
    return;
}

struct node
{
    int info;
    struct node *link;
};

struct node *create_list(struct node *start, int n)
{
    start = NULL;
    int i, data;
    if (n == 0)
    {
        printf("Empty list");
        return start;
    }
    for (i = 1; i <= n; i++)
    {
        printf("Enter the data to be added:\n");
        scanf("%d", &data);
        struct node *tmp, *p;
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->info = data;
        if (start == NULL)
        {
            tmp->link = start;
            start = tmp;
        }
        else
        {
            p = start;
            while (p->link != NULL)
                p = p->link;
            tmp->link = p->link;
            p->link = tmp;
        }
    }
    return start;
}
void display(struct node *start)
{
    struct node *p;
    p = start;
    if (start == NULL)
    {
        printf("The list is Empty\n");
        return;
    }
    while (p != NULL)
    {
        printf("%d ", p->info);
        p = p->link;
    }
    printf("\n");
}

int search_ele(struct node *start, int pos, int num)
{
    if (start == NULL)
        return 0;
    if (start->info == num)
        return pos;
    if (start->link != NULL)
        search_ele(start->link, pos + 1, num);
}
int main()
{
    int c, x, num;
    int a, b;
    char hexa[50], str[50];
    struct node *start = NULL;
    do
    {
        printf("\nEnter\n");
        printf("1:Base conversion\n");
        printf("2:Tower of Hanoi\n");
        printf("3:Greatest common divisor\n");
        printf("4:Reverse a string\n");
        printf("5:Search an element in a linked list\n");
        printf("6:Exit\n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            printf("\nEnter\n");
            printf("1.Decimal to Binary\n");
            printf("2.Decimal to Octal\n");
            printf("3.Decimal to Hexadecimal\n");
            scanf("%d", &x);
            switch (x)
            {
            case 1:
                printf("Enter the decimal number to be converted into Binary: ");
                scanf("%d", &num);
                printf("%d in Binary is: %d\n", num, bin(num));
                break;

            case 2:
                printf("Enter the decimal number to be converted into Octal: ");
                scanf("%d", &num);
                printf("%d in Octal is: %d\n", num, oct(num));
                break;

            case 3:
                printf("Enter the decimal number to be converted into Hexadecimal: ");
                scanf("%d", &num);
                printf("%d in Hexadecimal is: ", num);
                hex(num);
                break;

            default:
                printf("Invalid Input\n");
                break;
            }
            break;
        case 2:
            printf("Enter the number of disks: ");
            scanf("%d", &num);
            if (num < 1)
            {
                printf("There are no disks to shift\n");
                break;
            }
            else
                printf("There are %d disks in tower 1\n", num);
            hanoi(num, 1, 2, 3);
            printf("\n%d disks are shifted from tower 1 to tower 2\n", num);
            break;
        case 3:
            printf("Enter the numbers whose GCD is to be found:\n");
            scanf("%d %d", &a, &b);
            printf("GCD of %d and %d is: %d", a, b, GCD(a, b));
            break;

        case 4:
            printf("Enter the string to be reversed:\n");
            fflush(stdin);
            fgets(str,50,stdin);
            fflush(stdin);
            strreversal(str);
            break;

        case 5:
            printf("Enter the number of elements in linked list:\n");
            scanf("%d", &num);
            start = create_list(start, num);
            printf("The List is: ");
            display(start);
            printf("Enter the element to be searched: ");
            scanf("%d", &num);
            a = search_ele(start, 1, num);
            if (a > 0)
                printf("Element %d was found at pos %d\n", num, a);
            else
                printf("Element not found in linked list\n", num);
            break;
        case 6:
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (c != 6);
    return 0;
}