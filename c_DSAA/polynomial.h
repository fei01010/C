#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node{
    double coef;
    int exp;
    struct node* link;
} Term, *Polynomial;