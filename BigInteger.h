#ifndef BigInteger_H
#define BigInteger_H
struct node
{
    struct node*prev;
    int data;
    struct node *next;
};

typedef struct BigInteger{
    struct node * head,* tail;
    int len;
    int sign;
} SBI;


SBI add(SBI,SBI);
SBI sub(SBI,SBI);
SBI mul(SBI,SBI);
SBI div1(SBI,SBI);
SBI mod(SBI,SBI);
SBI initialize(char *);
void display(SBI);

#endif 