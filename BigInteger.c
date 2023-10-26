#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"


int length(struct node *head)  //calculating length of ll
{
    int count=0;
    while(head)
    {
        count++;
        head=head->next;
    }
    return count;
}

void insert(int data,struct node **head,struct node **tail)  ///inserng data at start so that number is formed
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->prev=NULL;
    newnode->next=NULL;
    if (*head == NULL)
    {
        // If the list is empty, set both head and tail to the new node
        *head = newnode;
        *tail = newnode;
    }
    else
    {
        // Update the links for the new node and the current head
        newnode->next = *head;
        (*head)->prev = newnode;
        *head = newnode;
    }
}

void insertAtEnd(int data,struct node **head,struct node** tail)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->prev=NULL;
    newnode->next=NULL;
    if (*head == NULL)
    {
        // If the list is empty, set both head and tail to the new node
        *head = newnode;
        *tail = newnode;
        // return;
    }

    newnode->prev=*tail;
    (*tail)->next=newnode;
    *tail=newnode;
}

void deletefromstart(struct node ** head)
{
    if(*head==NULL) //no node present
    {return;}

    struct node* temp=*head;
    if((*head)->next==NULL)
    {

        *head=NULL;
        free(temp);
        return ;
    }

    *head=(*head)->next;
    (*head)->prev=NULL;
    free(temp);

}

SBI initialize(char *str)
{
    SBI num;
    num.head=NULL;
    num.tail=NULL;
    int l=strlen(str);
    //num.len=0;
    //num.sign='+';
    for (size_t i = 0; i<l; i++) { // Exclude the newline character
        if (str[i] >= '0' && str[i] <= '9' || str[i]=='-' || str[i]=='+')
        {
            if( str[i]=='-' ||str[i]=='+')
            {
                num.sign=str[i];
            }
            else
            {int digit = str[i] - '0';
            insertAtEnd(digit, &num.head, &num.tail);}
        }
    }
    num.head->prev=NULL;
    
    num.len=length(num.head);
    return num;
    
}



void display(SBI num)
{
    struct node*head=num.head;
    if(head==NULL)
    {
        printf("list is empty");
        return;
    }
   else
    {
        if(num.sign=='-')
            printf("-");
        while(head!=NULL)
        {
            
            printf("%d",head->data);
            head=head->next;
        }
    }
}

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); // Terminate the program if memory allocation fails
    }
    
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void removeLeadingZeros(struct node** head) {
    while (*head != NULL && (*head)->data == 0) {
        struct node* temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
    }
}

SBI add(SBI num1,SBI num2)
{
    SBI temp1,temp2;
    temp1.tail=num1.tail,temp2.tail=num2.tail;
    temp1.head=num1.head,temp2.head=num2.head;
    
    int sum=0,l1,l2;
    l1=length(temp1.head);
    l2=length(temp2.head);
    SBI numadd;
    
    if(l1!=l2) 
    {
        if(l1>l2)
        {
            int n=l1-l2;
            for(int i=0;i<n;i++)
            {
                insert(0,&temp2.head,&temp2.tail);
            }
            
        }

        else if(l1<l2)
        {
            int m=l2-l1;
            for(int i=0;i<m;i++)
            {
                insert(0,&temp1.head,&temp1.tail);
            }
        }
    }
    
    
    while(temp1.tail !=NULL && temp2.tail!=NULL)
    {
        if(!temp1.tail->data){temp1.tail->data=0;}
        sum+=temp1.tail->data+temp2.tail->data;
        int a=sum%10;           ///if number less than 10 it will insert the number itself
        insert(a,&numadd.head,&numadd.tail);
        sum=sum/10;            ///it will overwrite the sum by 0,1,2...
        temp1.tail=temp1.tail->prev;
        temp2.tail=temp2.tail->prev;
    }
   // display(numadd);
    return numadd;
}

SBI sub(SBI num1,SBI num2)
{
    struct node *temptail1=num1.tail,*temptail2=num2.tail;
    struct node*temphead1=num1.head,*temphead2=num2.head;
    SBI numsub;
    int diff=0,l1,l2,borrow=0;
    l1=num1.len;
    l2=num2.len;
    if(l1!=l2)  
    {
        if(l1>l2)
        {
            int n=l1-l2;
            for(int i=0;i<n;i++)
            {
                insert(0,&temphead2,&temptail2);
            }
        }

        else if(l2>l1)
        {
            int m=l2-l1;
            for(int i=0;i<m;i++)
            {
                insert(0,&temphead1,&temptail1);
            }
        }
    }

    while(temptail1 !=NULL && temptail2!=NULL)
    {
        diff=temptail1->data - temptail2->data-borrow;
        if(diff >=0)
        {
            borrow=0;
        }

        else if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        insert(diff,&numsub.head,&numsub.tail);
        temptail1=temptail1->prev;
        temptail2=temptail2->prev;
    }
    
    while (numsub.head->next != NULL && numsub.head->data == 0)
    {
        struct node *temp = numsub.head;
        numsub.head = numsub.head->next;
        numsub.head->prev = NULL;
        free(temp);
    }
    
    return numsub;
}



SBI mul(SBI num1,SBI num2)
{
   // printf("Entered mul func\n");
    struct node *temptail2=num2.tail;
    int n=0;
    SBI result,tempres;
    result.head=createNode(0);
    result.tail=result.head;
    while(temptail2!=NULL)
    {
        // Create a temporary result list for this iteration

        tempres.head=NULL,tempres.tail=NULL;
       

        //multiplying first integer ie first ll with one number from temptail2 one by onr from end
        int multiplier=temptail2->data;
        int carry=0, product=1,res;
        struct node *temptail1=num1.tail;

        while(temptail1!=NULL)
        {

            product=(temptail1->data * multiplier)+carry;

            res=product%10;
            carry =product/10;

            //inserting res in temporary ll
            insert(res,&tempres.head,&tempres.tail);// Insert the digit at the tail

            temptail1=temptail1->prev;

        }

        //if there is carry left at end after multiplying by single digit add it
        if(carry>0)
        {
            insert(carry,&tempres.head,&tempres.tail);
        }
        for(int i=0;i<n;i++)
        {
            insertAtEnd(0,&tempres.head,&tempres.tail);   //inserting zeroes at tail
        }

       result=add(tempres,result);
       
        //headresult=addlist(tempreshead,temprestail,headresult,tailresult);
        
        temptail2=temptail2->prev;
        n++;

    }
    
    removeLeadingZeros(&result.head);
    SBI numul;
    
    numul=result;
    return numul;
}



// Function to create a number from a linked list of digits
int createNumber(struct node* head, int numDigits) {
    int number = 0;
    struct node* current = head;

    while (numDigits > 0) {
        number = number * 10 + current->data;
        current = current->next;
        numDigits--;
    }

    return number;
}

// Function to perform floor division
SBI div1(SBI num1, SBI num2) 
{
    SBI result;
    result.head = NULL;
    result.tail = NULL;
    result.len = 0;
    result.sign = 1;

    int divisor = createNumber(num2.head, num2.len);
    struct node* temphead1 = num1.head;
    int n1 = num1.len;
    int n2 = num2.len;

    int tempno = 0;

    while (temphead1 != NULL) 
    {
        tempno = tempno * 10 + temphead1->data;
        
        if (tempno >= divisor)
        {
            int quotient_found = 0;
            int rem = 0;

            for (int i = 9; i >= 1; i--) 
            {
                int a = divisor * i;
                if (a <= tempno) {
                    int product = a;
                    rem = tempno - product;
                    insertAtEnd(i,&(result.head), &(result.tail));
                    result.len++;
                    quotient_found = 1;
                    break;
                }
            }

            if (!quotient_found) 
            {
                insertAtEnd(0,&(result.head), &(result.tail));
                result.len++;
            }

            tempno = rem;
        }
        else 
        {
            if (result.head != NULL || temphead1->next != NULL)
            {
                insertAtEnd(0,&(result.head), &(result.tail));
                result.len++;
            }
        }

        temphead1 = temphead1->next;
    }
    while(result.head!=NULL && result.head->data==0)
    {
        deletefromstart(&result.head);
    }

    return result;
}

//program only for mod function
SBI sublists(SBI num1, SBI num2) {
    SBI result;
    result.head = NULL;
    result.tail = NULL;
    result.len = 0;

    // Check if num1 is shorter than num2, if yes, swap them
    if (num1.len < num2.len) {
        SBI temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int borrow = 0;
    struct node* temp1 = num1.tail;
    struct node* temp2 = num2.tail;

    while (temp1 != NULL) {
        int val1 = temp1->data;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        int diff = val1 - val2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert(diff, &(result.head), &(result.tail));
        temp1 = temp1->prev;

        if (temp2 != NULL) {
            temp2 = temp2->prev;
        }
    }

    // Remove leading zeros in the result
    removeLeadingZeros(&(result.head));

    return result;
}


SBI mod(SBI num1, SBI num2) {
    SBI dividend = num1;
    SBI divisor = num2;
     SBI rem;
    
    SBI quotient = div1(dividend, divisor);  // Get the quotient
    
    SBI product = mul(quotient, divisor);  
   rem = sublists(dividend, product);  // Subtract the product from the dividend to get the remainder
    
    return rem;
}
